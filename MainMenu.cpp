#include "global.h"
#include "sprites.h"
#include "font.h"
#include <cmath>

enum Key{upKey,downKey};
static bool keys[2];
static unsigned char cursorPos;

void drawSprite(const unsigned char sprite[],int x, int y,int spriteSize,int size,char rot) {
	int itt = 0;
	switch (rot) {
	case 0:
		for (int i = x; i < x + spriteSize * size; i += size) {
			for (int i2 = y; i2 < y + spriteSize * size; i2 += size) {
				if (!sprite[itt] && !sprite[itt + 1] && !sprite[itt + 2]) {
					itt += 3;
					continue;
				}
				for (int i3 = 0; i3 < size; i3++) {
					for (int i4 = 0; i4 < size; i4++) {
						texture[i + i3][i2 + i4][0] = sprite[itt + 2];
						texture[i + i3][i2 + i4][1] = sprite[itt + 1];
						texture[i + i3][i2 + i4][2] = sprite[itt];
					}
				}
				itt += 3;
			}
		}
		break;
	case 1:
		for (int i = x; i < x + spriteSize * size; i += size) {
			for (int i2 = y; i2 < y - spriteSize * size; i2 -= size) {
				if (!sprite[itt] && !sprite[itt + 1] && !sprite[itt + 2]) {
					itt += 3;
					continue;
				}
				for (int i3 = 0; i3 < size; i3++) {
					for (int i4 = 0; i4 < size; i4++) {
						texture[i + i3][i2 + i4][0] = sprite[itt + 2];
						texture[i + i3][i2 + i4][1] = sprite[itt + 1];
						texture[i + i3][i2 + i4][2] = sprite[itt];
					}
				}
				itt += 3;
			}
		}
		break;
	case 2:
		for (int i = x; i > x - spriteSize * size; i -= size) {
			for (int i2 = y; i2 < y + spriteSize * size; i2 += size) {
				if (!sprite[itt] && !sprite[itt + 1] && !sprite[itt + 2]) {
					itt += 3;
					continue;
				}
				for (int i3 = 0; i3 < size; i3++) {
					for (int i4 = 0; i4 < size; i4++) {
						texture[i + i3][i2 + i4][0] = sprite[itt + 2];
						texture[i + i3][i2 + i4][1] = sprite[itt + 1];
						texture[i + i3][i2 + i4][2] = sprite[itt];
					}
				}
				itt += 3;
			}
		}
		break;
	case 3:
		for (int i = x; i > x - spriteSize * size; i -= size) {
			for (int i2 = y; i2 > y - spriteSize * size; i2 -= size) {
				if (!sprite[itt] && !sprite[itt + 1] && !sprite[itt + 2]) {
					itt += 3;
					continue;
				}
				for (int i3 = 0; i3 < size; i3++) {
					for (int i4 = 0; i4 < size; i4++) {
						texture[i + i3][i2 + i4][0] = sprite[itt + 2];
						texture[i + i3][i2 + i4][1] = sprite[itt + 1];
						texture[i + i3][i2 + i4][2] = sprite[itt];
					}
				}
				itt += 3;
			}
		}
		break;
	}
	
}

static void input() {
	if (GetKeyState(VK_RETURN) < 0) {
		switch (cursorPos) {
		case 0:
			screen = levelMenu;
			break;
		case 1:
			screen = LevelEditor;
			break;
		case 2:
			exit(0);
			break;
		}
	}
	if (GetKeyState(VK_UP) < 0) {
		if (!keys[upKey]) {
			cursorPos--;
			keys[upKey] = true;
			if (cursorPos == 255) {
				cursorPos = 2;
			}
		}
	}
	else {
		keys[upKey] = false;
	}
	if (GetKeyState(VK_DOWN) < 0) {
		if (!keys[downKey]) {
			cursorPos++;
			keys[downKey] = true;
			if (cursorPos == 3) {
				cursorPos = 0;
			}
		}
	}
	else {
		keys[downKey] = false;
	}
}

static void getCursorLoc() {
	switch (cursorPos) {
	case 0:
		drawSprite(Arrow,760, 490,9,9,3);
		break;
	case 1:
		drawSprite(Arrow,660, 490,9,9,3);
		break;
	case 2:
		drawSprite(Arrow,560, 490, 9, 9, 3);
		break;
	}
}

void mainMenuFN() {
	input();
	drawWord("main menu", 9, 950, 515, 20);
	drawWord("play", 4, 750, 505, 12);
	drawWord("level editor", 12, 650, 505, 12);
	drawWord("quit", 4, 550, 505, 12);
	getCursorLoc();
}