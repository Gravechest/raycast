#include <Windows.h>
#include "glew.h"
#include <gl/GL.h>

#include <cmath>
#include <cstdio>

#include "global.h"
#include "Level.h"
#include "sprites.h"

unsigned int VBO;
unsigned int VTO;
unsigned int VZO;
unsigned int textures;


unsigned char texture[screenHeight][screenWidht][3];

float square[12] = { -1.0,-1.0,1.0,-1.0,-1.0,1.0,1.0,1.0,-1.0,1.0,1.0,-1.0 };
float textCoords[12] = { 0.0,0.0,1.0,0.0,0.0,1.0,1.0,1.0,0.0,1.0,1.0,0.0 };

unsigned char screen;

unsigned int init_game(HWND app) {
    unsigned int shaderprogram = glCreateProgram();
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(square),square, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glCreateBuffers(1, &VTO);
    glBindBuffer(GL_ARRAY_BUFFER, VTO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textCoords), textCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glGenTextures(1, &textures);
    glBindTexture(GL_TEXTURE_2D, textures);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidht, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexshader,1,&vertexshaderSource,NULL);
    glShaderSource(fragshader,1,&fragshaderSource,NULL);
    glCompileShader(vertexshader);  
    glCompileShader(fragshader);
    glAttachShader(shaderprogram, vertexshader);
    glAttachShader(shaderprogram, fragshader);
    glLinkProgram(shaderprogram);
    glUseProgram(shaderprogram);
    return shaderprogram;
}

void selectScreen() {
    switch (screen) {
    case LevelEditor:
        levelEditorFN();
        break;
    case Level:
        levelFN();
        break;
    case mainMenu:
        mainMenuFN();
        break;
    case levelMenu:
        levelMenuFN();
        break;
    }
}

void the_game(HDC pixel, unsigned int shaderprogram, HWND app) {
    selectScreen();
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, screenWidht, screenHeight, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(square) * 2);
    memset(texture, 0, screenWidht * screenHeight * 3);
}