#include <cstdio>
#include "global.h"
#include "Font.h"
#include "sprites.h"
#include "Level.h"

enum Keys{keyDown,keyUp,keyLeft,keyRight,keySpace,keyQ,keyE,keyBackspace};
static bool keys[8];
static bool typeKeys[26];
bool saveGame;
int warningTimer;
bool warning;
char lvlNamePos;
char lvlName[8];
char selectedItem;

int cursorPos[2] = {0,0}; 

void saveGameFN() {
	FILE* level = fopen("levels.txt", "rb+");
	fpos_t streamPos = 0;
	char readBuf[8] = { 0,0,0,0,0,0,0,0 };
	if (!level) {
		fclose(fopen("levels.txt", "wb"));
		level = fopen("levels.txt", "rb+");
	}
	fseek(level, 0, SEEK_END);
	long long amm = ftell(level);
	rewind(level);
	for (long long i = 0; i < amm; i += levelDataSize) {
		streamPos = i;
		fsetpos(level, &streamPos);
		fread(readBuf, 1, 8, level);
		if (memcmp(readBuf, lvlName, sizeof(lvlName)) == 0) {
			streamPos = i + 8;
			fsetpos(level, &streamPos);
			fwrite(map, 1089, 1, level);
			fputc(0, level);
			goto saved;
		}
	}
	streamPos = amm;
	fsetpos(level, &streamPos);
	fwrite(lvlName, 8, 1, level);
	fwrite(map, 1089, 1, level);
	fputc(0, level);
saved:
	screen = mainMenu;
	fclose(level);
}

bool verifyLevel() {
	bool flag = false;
	for (int i = 0; i < 33; i++) {
		for (int i2 = 0; i2 < 33; i2++) {
			if (map[i][i2] == flagBlock) {
				if (flag) {
					return false;
				}
				else {
					flag = true;
				}
			}
		}
	}
	if (flag) {
		return true;
	}
	else {
		return false;
	}
}

static void input() {
	if (saveGame) {
		if (GetKeyState(VK_INSERT) < 0) {
			if (verifyLevel()) {
				saveGameFN();
			}
			else {
				memset(lvlName, 0, 8);
				lvlNamePos = 0;
				saveGame = false;
				warning = true;
				warningTimer = 120;
			}
		}
		for (int i = 0x41; i < 0x5b; i++) {
			if (GetKeyState(i) < 0) {
				if (!typeKeys[i - 0x41] && lvlNamePos < 8) {
					lvlName[lvlNamePos] = i + 32;	
					lvlNamePos++;
					typeKeys[i - 0x41] = true;
				}
			}
			else {
				typeKeys[i - 0x41] = false;
			}
		}
		if (GetKeyState(VK_BACK) < 0) {
			if (!keys[keyBackspace]) {
				keys[keyBackspace] = true;
				if (lvlNamePos > 0) {
					lvlNamePos--;
					lvlName[lvlNamePos] = 0;
				}
			}
		}
		else {
			keys[keyBackspace] = false;
		}
	}
	if (GetKeyState(0x51) < 0) {
		if (!keys[keyQ]) {
			keys[keyQ] = true;
			selectedItem++;
			if (selectedItem == 7) {
				selectedItem = 0;
			}
		}
	}
	else {
		keys[keyQ] = false;
	}
	if (GetKeyState(0x45) < 0) {
		if (!keys[keyE]) {
			keys[keyE] = true;
			selectedItem--;
			if (selectedItem == -1) {
				selectedItem = 6;
			}
		}
	}
	else {
		keys[keyE] = false;
	}
	if (GetKeyState(0x53) < 0) {
		saveGame = true;
		typeKeys[0x12] = true;
	}
	if (GetKeyState(VK_ESCAPE) < 0) {
		memset(lvlName, 0, 8);
		lvlNamePos = 0;
		saveGame = false;
	}
	if (GetKeyState(VK_SPACE) < 0) {
		if (!keys[keySpace]) {
			keys[keySpace] = true;
			if (map[cursorPos[0]][cursorPos[1]]) {
				map[cursorPos[0]][cursorPos[1]] = 0;
			}
			else {
				map[cursorPos[0]][cursorPos[1]] = selectedItem + 1;
			}
		}
	}
	else {
		keys[keySpace] = false;
	}
	if (GetKeyState(VK_DOWN) < 0) {
		if (!keys[keyDown]) {
			cursorPos[0]--;
			if (cursorPos[0] < 0) {
				cursorPos[0] = 0;
			}
			keys[keyDown] = true;
		}
	}
	else {
		keys[keyDown] = false;
	}
	if (GetKeyState(VK_UP) < 0) {
		if (!keys[keyUp]) {
			cursorPos[0]++;
			if (cursorPos[0] > 32) {
				cursorPos[0] = 32;
			}
			keys[keyUp] = true;
		}
	}
	else {
		keys[keyUp] = false;
	}
	if (GetKeyState(VK_LEFT) < 0) {
		if (!keys[keyLeft]) {
			cursorPos[1]--;
			if (cursorPos[1] < 0) {
				cursorPos[1] = 0;
			}
			keys[keyLeft] = true;
		}
	}
	else {
		keys[keyLeft] = false;
	}
	if (GetKeyState(VK_RIGHT) < 0) {
		if (!keys[keyRight]) {
			cursorPos[1]++;
			if (cursorPos[1] > 32) {
				cursorPos[1] = 32;
			}
			keys[keyRight] = true;
		}
	}
	else {
		keys[keyRight] = false;
	}
}

void levelEditorFN() {
	input();
	drawMap();
	drawSprite(cursor, cursorPos[0] * 32, cursorPos[1] * 32, 8, 4);
	switch (selectedItem) {
	case 0:
		drawSprite(stone, 32, 1120, 32, 1,2);
		break;
	case 1:
		drawSprite(flag, 32, 1120, 32, 1,2);
		break;
	case 2:
		drawSprite(ladder, 32, 1120, 32, 1,2);
		break;
	case 3:
		drawSprite(basicTurret, 32, 1120, 32, 1, 2);
		break;
	case 4:
		drawSprite(coin, 32, 1120, 32, 1, 2);
		break;
	case 5:
		drawSprite(laserTurret, 32, 1120, 32, 1, 2);
		break;
	case 6:
		drawSprite(gravityTurret, 32, 1120, 32, 1, 2);
		break;
	}
	if (warning) {
		drawWord("level must", 10, 820, 1120, 5);
		drawWord("include a flag", 14, 780, 1120, 5);
		if (warningTimer) {
			warningTimer--;
		}
		else {
			warning = false;
		}
	}
	if (saveGame) {
		drawWord("save", 4, 960, 1120, 6);
		drawWord(lvlName, 8, 860, 1120, 5);
	}
}