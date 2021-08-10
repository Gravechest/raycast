#pragma once
#include <windows.h>

#define screenWidht 1920
#define screenHeight 1080

enum Screen { mainMenu, Pauze, Level, LevelEditor, levelMenu };
void the_game(HDC pixel, unsigned int shaderprogram, HWND app);
unsigned int init_game(HWND app);

void mainMenuFN();
void PauzeFN();
void levelFN();
void levelEditorFN();
void levelMenuFN();

extern enum Screen;

extern unsigned int Ptime;
extern unsigned char screen;
extern const char* fragshaderSource;
extern const char* vertexshaderSource;
extern unsigned char texture[screenHeight][screenWidht][3];

extern HWND app;