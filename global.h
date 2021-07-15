#pragma once
#include <windows.h>

void the_game(HDC pixel, unsigned int shaderprogram, HWND app);
unsigned int init_game(HWND app);

extern const char* fragshaderSource;
extern const char* vertexshaderSource;

extern const unsigned char duck[3][32][32];
extern const unsigned char naakte_molrat[3][32][32];

extern HWND app;