#include "global.h"
#include "Font.h"
#include "sprites.h"
#include "Level.h"
#include <cstdio>

int levelID;
static bool init;
int levelCount;
char levels[100][9];
static unsigned char cursorPos;
enum Keys{keyUp,keyDown};
static bool keys[2];

static void input() {
	if (GetKeyState(0x4c) < 0) {
		FILE * level = fopen("levels.txt", "rb");
		fpos_t streamPos = cursorPos * levelDataSize + 8;
		levelID = streamPos / levelDataSize;
		fsetpos(level, &streamPos);
		fread(map, 1, 1089, level);
		init = false;
		screen = Level;
	}
	if (GetKeyState(VK_UP) < 0) {
		if (!keys[keyUp] && levelCount) {
			cursorPos--;
			keys[keyUp] = true;
			if (cursorPos == 255) {
				cursorPos = levelCount - 1;
			}
		}
	}
	else {
		keys[keyUp] = false;
	}
	if (GetKeyState(VK_DOWN) < 0) {
		if (!keys[keyDown] && levelCount) {
			cursorPos++;
			keys[keyDown] = true;
			if (cursorPos == levelCount) {
				cursorPos = 0;
			}
		}
	}
	else {
		keys[keyDown] = false;
	}
	if (GetKeyState(VK_ESCAPE) < 0) {
		init = false;
		screen = mainMenu;
	}
}

static void initScreen() {
	char readBuf[8] = { 0,0,0,0,0,0,0,0 };
	FILE* level = fopen("levels.txt", "rb");
	if (!level) {
		fclose(fopen("levels.txt", "wb"));
		level = fopen("levels.txt", "rb");
	}
	fseek(level, 0, SEEK_END);
	int amm = ftell(level);
	rewind(level);
	levelCount = amm / levelDataSize;
	int vinkjesCount = levelCount + 1;
	for (int i = 0; i < amm; i += levelDataSize) {
		fpos_t streamPos = i;
		fsetpos(level, &streamPos);
		fread(readBuf, 8, 1, level);
		memcpy(levels[i / levelDataSize], readBuf, 8);
		streamPos += 1097;
		fsetpos(level, &streamPos);
		char vinkje = fgetc(level);
		levels[i / levelDataSize][8] = vinkje;
		if (!vinkje) {
			vinkjesCount--;
		}
	}
	if (vinkjesCount <= levelCount) {
		levelCount = vinkjesCount;
	}
	init = true;
	fclose(level);
}

static void getCursorLoc() {
	drawSprite(Arrow, 820 - cursorPos * 100, 410, 9,9,3);
}

void levelMenuFN() {
	if (!init) {
		initScreen();
	}
	input();
	drawWord("level select", 12, 950, 415, 20);
	for (int i = 0; i < levelCount; i++) {
		int offset = 0;
		if (levels[i][8]) {
			drawSprite(vinkje, 810 - i * 100, 428, 16, 3, 2);
			offset += 50; 
		}
		drawWord(levels[i], 8, 810 - i * 100, 428 + offset, 12);
	}
	getCursorLoc();
}