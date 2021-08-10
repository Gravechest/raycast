#include "global.h"
#include "sprites.h"
#include "Font.h"

void drawFont(int x, int y, const unsigned char sprite[], int size) {
    int itt = 72;
    for (int i = x; i > x - size * 5; i -= size) {
        for (int i2 = y; i2 < y + size * 5; i2 += size) {
            itt += 3;
            for (int i3 = 0; i3 < size; i3++) {
                for (int i4 = 0; i4 < size; i4++) {
                    texture[i + i3][i2 + i4][0] = sprite[itt % 75];
                    texture[i + i3][i2 + i4][1] = sprite[(itt + 1) % 75];
                    texture[i + i3][i2 + i4][2] = sprite[(itt + 2) % 75];
                }
            }
        }
    }
}

void drawWord(const char word[], int wordSize, int x, int y, int size) {
    int offset = 0;
    for (int i = 0; i < wordSize; i++) {
        switch (word[i]) {
        case 'b':
            drawFont(x, y + offset, letterB, size);
            offset += size * 5;
            break;
        case 'j':
            drawFont(x, y + offset, letterJ, size);
            offset += size * 4;
            break;
        case 'k':
            drawFont(x, y + offset, letterK, size);
            offset += size * 5;
            break;
        case 'w':
            offset += size;
            drawFont(x, y + offset, letterW, size);
            offset += size * 6;
            break;
        case 'x':
            drawFont(x, y + offset, letterX, size);
            offset += size * 5;
            break;
        case 'f':
            drawFont(x, y + offset, letterF, size);
            offset += size * 5;
            break;
        case 'g':
            drawFont(x, y + offset, letterG, size);
            offset += size * 5;
            break;
        case 'c':
            drawFont(x, y + offset, letterC, size);
            offset += size * 5;
            break;
        case 'y':
            drawFont(x, y + offset, letterY, size);
            offset += size * 5;
            break;
        case 'q':
            drawFont(x, y + offset, letterQ, size);
            offset += size * 6;
            break;
        case 'r':
            drawFont(x, y + offset, letterR, size);
            offset += size * 5;
            break;
        case 'l':
            drawFont(x, y + offset, letterL, size);
            offset += size * 5;
            break;
        case 'v':
            drawFont(x, y + offset, letterV, size);
            offset += size * 5;
            break;
        case 'd':
            drawFont(x, y + offset, letterD, size);
            offset += size * 5;
            break;
        case 'z':
            drawFont(x, y + offset, letterZ, size);
            offset += size * 5;
            break;
        case 'p':
            drawFont(x, y + offset, letterP, size);
            offset += size * 5;
            break;
        case 'i':
            offset -= size;
            drawFont(x, y + offset, letterI, size);
            offset += size * 4;
            break;
        case 'o':
            drawFont(x, y + offset, letterO, size);
            offset += size * 5;
            break;
        case 'h':
            drawFont(x, y + offset, letterH, size);
            offset += size * 5;
            break;
        case 't':
            drawFont(x, y + offset, letterT, size);
            offset += size * 5;
            break;
        case 'a':
            drawFont(x, y + offset, letterA, size);
            offset += size * 5;
            break;
        case 's':
            drawFont(x, y + offset, letterS, size);
            offset += size * 5;
            break;
        case 'm':
            offset += size;
            drawFont(x, y + offset, letterM, size);
            offset += size * 6;
            break;
        case 'e':
            drawFont(x, y + offset, letterE, size);
            offset += size * 5;
            break;
        case 'n':
            drawFont(x, y + offset, letterN, size);
            offset += size * 5;
            break;
        case 'u':
            drawFont(x, y + offset, letterU, size);
            offset += size * 5;
            break;
        default:
            offset += size * 5;
            break;
        }
    }
}