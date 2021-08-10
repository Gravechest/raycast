#include "global.h"
#include "sprites.h"
#include "Level.h"
#include "Font.h"
#include <cmath>
#include <cstdio>

bool beginGame;
float player[4];
unsigned char ammCoins;
unsigned char collCoins;
static bool init;
unsigned char mapSource[33][33];
unsigned char map[33][33];
unsigned short int mapData[33][33];
int entityCount[5];
float entityData[5000][4];
short int entityExtraData[5000][1];
int startingPos[2];

void resetLevel() {
    player[0] = startingPos[0];
    player[1] = startingPos[1];
    player[2] = 0;
    player[3] = 0;
    collCoins = 0;
    beginGame = false;
    memset(entityData, 0, sizeof(entityData));
    memset(entityCount, 0, sizeof(entityCount));
    memset(mapData, 0, sizeof(mapData));
    memcpy(map, mapSource, sizeof(map));
}

void drawPlayer() {
    for (int i = 1; i < 31; i++) {
        for (int i2 = 1; i2 < 31; i2++) {
            texture[(int)player[0] + 32 - i][(int)player[1] + i2][0] = duck[(i * 32 + i2) * 3 + 2];
            texture[(int)player[0] + 32 - i][(int)player[1] + i2][1] = duck[(i * 32 + i2) * 3 + 1];
            texture[(int)player[0] + 32 - i][(int)player[1] + i2][2] = duck[(i * 32 + i2) * 3];
        }
    }
}

void drawMap() {
    for (int i = 0; i < 33; i++) {
        for (int i2 = 0; i2 < 33; i2++) {
            switch (map[i][i2]) {
            case stoneBlock:
                drawSprite(stone, i * 32 + 32, i2 * 32, 32, 1, 2);
                break;
            case flagBlock:
                drawSprite(flag, i * 32 + 32, i2 * 32, 32, 1, 2);
                break;
            case ladderBlock:
                drawSprite(ladder, i * 32 + 32, i2 * 32, 32, 1, 2);
                break;
            case basicTurretBlock:
                drawSprite(basicTurret, i * 32 + 32, i2 * 32, 32, 1, 2);
                break;
            case coinBlock:
                drawSprite(coin, i * 32 + 32, i2 * 32, 32, 1, 2);
                break;
            case laserTurretBlock:
                drawSprite(laserTurret, i * 32 + 32, i2 * 32, 32, 1, 2);
                break;
            case gravityTurretBlock:
                drawSprite(gravityTurret, i * 32 + 32, i2 * 32, 32, 1, 2);
                break;
            }
        }
    }
}

void createEntity(unsigned char entity,float x,float y,float velX,float velY,short int additionalData = 0) {
    entityData[entityCount[entity] + entity * 1000][0] = x;
    entityData[entityCount[entity] + entity * 1000][1] = y;
    entityData[entityCount[entity] + entity * 1000][2] = velX;
    entityData[entityCount[entity] + entity * 1000][3] = velY;
    entityExtraData[entityCount[entity] + entity * 1000][0] = additionalData;
    entityCount[entity]++;
}

void destroyEntity(int entity) {
    unsigned char entityType = entity / 1000;
    for (int i = entity; i < entityType * 1000 + entityCount[entityType]; i++) {
        entityData[i][0] = entityData[i + 1][0];
        entityData[i][1] = entityData[i + 1][1];
        entityData[i][2] = entityData[i + 1][2];
        entityData[i][3] = entityData[i + 1][3];
        entityExtraData[i][0] = entityExtraData[i + 1][0];
    }
    entityCount[entityType]--;
}

void updateEntity() {
    for (int i = 0; i < entityCount[0]; i++) {
        float newPos[2] = { entityData[i][0] + entityData[i][2],entityData[i][1] + entityData[i][3] };
        if (map[(int)newPos[0] / 32][(int)newPos[1] / 32] != stoneBlock
            && newPos[0] > 0 && newPos[1] > 0
            && newPos[0] < 1060 && newPos[1] < 1060) {
            if (newPos[0] > player[0] && newPos[0] < player[0] + 32 && newPos[1] > player[1] && newPos[1] < player[1] + 32) {
                resetLevel();
                return;
            }
            entityData[i][0] = newPos[0];
            entityData[i][1] = newPos[1];
            for (int i3 = entityData[i][0]; i3 < entityData[i][0] + 5; i3++) {
                for (int i4 = entityData[i][1]; i4 < entityData[i][1] + 5; i4++) {
                    texture[i3][i4][0] = 255;
                    texture[i3][i4][1] = 0;
                    texture[i3][i4][2] = 0;
                }
            }
        }
        else {
            destroyEntity(i);
        }
    }
    for (int i = 1000; i < entityCount[1] + 1000; i++){
        float ray[2] = { entityData[i][0],entityData[i][1]};
        float goal[2] = { entityData[i][0] - entityData[i][2],entityData[i][1] - entityData[i][3] };
        float minus = { max(abs(goal[0]),abs(goal[1])) };
        goal[0] /= minus;
        goal[1] /= minus;
        for (int i = 0; i < minus; i++) {
            for (int i2 = ray[0] - 1; i2 < ray[0] + 1; i2++) {
                for (int i3 = ray[1] - 1; i3 < ray[1] + 1; i3++) {
                    texture[i2][i3][0] = 50;
                    texture[i2][i3][1] = 0;
                    texture[i2][i3][2] = 0;
                }
            }
            ray[0] -= goal[0];
            ray[1] -= goal[1];
        }
        entityExtraData[i][0]--;
        if (!entityExtraData[i][0]) {
            createEntity(2, entityData[i][0], entityData[i][1], entityData[i][2], entityData[i][3], 120);
            destroyEntity(i);
            i--;
        }
    }
    for (int i = 2000; i < entityCount[2] + 2000; i++) {
        float ray[2] = { entityData[i][0],entityData[i][1] };
        float goal[2] = { entityData[i][0] - entityData[i][2],entityData[i][1] - entityData[i][3] };
        float minus = max(abs(goal[0]),abs(goal[1]));
        goal[0] /= minus;
        goal[1] /= minus;
        for (int i2 = 0; i2 < minus; i2++) {
            unsigned char red = 0;
            if (entityExtraData[i][0] * 10 > 255) {
                red = 255;
            }
            else {
                red = entityExtraData[i][0] * 10;
            }
            for (int i3 = ray[0] - 1; i3 < ray[0] + 1; i3++) {
                for (int i4 = ray[1] - 1; i4 < ray[1] + 1; i4++) {
                    texture[i3][i4][0] = red;
                    texture[i3][i4][1] = 0;
                    texture[i3][i4][2] = 0;
                }
            }
            if (ray[0] > player[0] && ray[0] < player[0] + 32 && ray[1] > player[1] && ray[1] < player[1] + 32) {
                resetLevel();
            }
            ray[0] -= goal[0];
            ray[1] -= goal[1];
        }
        entityExtraData[i][0]--;
        if (!entityExtraData[i][0]) {
            destroyEntity(i);
            i--;
        }
    }
    for (int i = 3000; i < entityCount[3] + 3000; i++) {
        entityData[i][0] += entityData[i][2];
        entityData[i][1] += entityData[i][3];
        entityData[i][2] /= 1.0352;
        entityData[i][3] /= 1.0352;
        for (int i3 = entityData[i][0] - 1; i3 < entityData[i][0] + 1; i3++) {
            for (int i4 = entityData[i][1] - 1; i4 < entityData[i][1] + 1; i4++) {
                texture[i3][i4][0] = 255;
                texture[i3][i4][1] = 0;
                texture[i3][i4][2] = 255;
            }
        }
        if (entityData[i][2] + entityData[i][3] < 1) {
            createEntity(4,entityData[i][0], entityData[i][1], 0, 0, 300);
            destroyEntity(i);
            i--;
        }
    }
    for (int i = 4000; i < entityCount[4] + 4000; i++) {
        float dist[2] = { player[0] + 16 - entityData[i][0],player[1] + 16 - entityData[i][1]};
        float power = 15 / sqrtf(abs(dist[0]) * abs(dist[0]) + abs(dist[1]) * abs(dist[1]));
        if (power > 1) {
            power = 1;
        }
        float minus = max(abs(dist[0]), abs(dist[1]));
        dist[0] /= minus;
        dist[1] /= minus;
        dist[0] *= power;
        dist[1] *= power;
        player[2] -= dist[0];
        player[3] -= dist[1];
        for (int i3 = entityData[i][0] - 1; i3 < entityData[i][0] + 1; i3++) {
            for (int i4 = entityData[i][1] - 1; i4 < entityData[i][1] + 1; i4++) {
                texture[i3][i4][0] = 255;
                texture[i3][i4][1] = 0;
                texture[i3][i4][2] = 255;
            }
        }
        float ray[2] = { entityData[i][0],entityData[i][1] };
        float goal[2] = { entityData[i][0] - player[0] - 16,entityData[i][1] - player[1] - 16};
        minus = max(abs(goal[0]), abs(goal[1]));
        goal[0] /= minus;
        goal[1] /= minus;
        for (int i2 = 0; i2 < minus; i2++) {
            for (int i2 = ray[0] - 1; i2 < ray[0] + 1; i2++) {
                for (int i3 = ray[1] - 1; i3 < ray[1] + 1; i3++) {
                    texture[i2][i3][0] = power * 255;
                    texture[i2][i3][1] = 0;
                    texture[i2][i3][2] = power * 255;
                }
            }
            ray[0] -= goal[0];
            ray[1] -= goal[1];
        }
        entityExtraData[i][0]--;
        if (!entityExtraData[i][0]) {
            destroyEntity(i);
            i--;
        }
    }
}

static void input() {
    bool key[4] = { 0,0,0,0 };
    if (GetKeyState(0x52) < 0) {
        resetLevel();
        init = false;
        screen = levelMenu;
    }
    if (GetKeyState(VK_SPACE) < 0) {
        beginGame = true;
    }
    if (beginGame) {
        if (GetKeyState(0x57) < 0) {
            key[0] = true;
        }
        if (GetKeyState(0x53) < 0) {
            key[1] = true;
        }
        if (GetKeyState(0x44) < 0) {
            key[2] = true;
        }
        if (GetKeyState(0x41) < 0) {
            key[3] = true;
        }
    }
    if (key[0]) {
        if (key[2]) {
            player[2] += 0.25;
            player[3] += 0.25;
        }
        else if (key[3]) {
            player[2] += 0.25;
            player[3] -= 0.25;
        }
        else {
            player[2] += 0.36;
        }
    }
    else if (key[1]) {
        if (key[3]) {
            player[2] -= 0.25;
            player[3] -= 0.25;
        }
        else if (key[2]) {
            player[2] -= 0.25;
            player[3] += 0.25;
        }
        else {
            player[2] -= 0.36;
        }
    }
    else if (key[2]) {
        player[3] += 0.36;
    }
    else if (key[3]) {
        player[3] -= 0.36;
    }
}

void initFN() {
    for (int i = 0; i < 33; i++) {
        for (int i2 = 0; i2 < 33; i2++) {
            switch (map[i][i2]) {
            case coinBlock:
                ammCoins++;
                break;
            case flagBlock:
                map[i][i2] = 0;
                player[0] = i * 32;
                player[1] = i2 * 32;
                startingPos[0] = i * 32;
                startingPos[1] = i2 * 32;
            }
        }
    }
    memcpy(mapSource, map, sizeof(map));
}

void playerCollision() {
    for (int i = 0; i <= 29; i += 29) {
        for (int i2 = 0; i2 <= 29; i2 += 29) {
            switch (map[(int)(player[0] + player[2] + i) / 32][(int)(player[1] + player[3] + i2) / 32]) {
            case coinBlock:
                collCoins++;
                map[(int)(player[0] + player[2] + i) / 32][(int)(player[1] + player[3] + i2) / 32] = 0;
                break;
            case stoneBlock:
                if (map[(int)(player[0] + player[2] + i) / 32][(int)(player[1] + i2) / 32] == stoneBlock) {
                    player[2] = 0;
                }
                if (map[(int)(player[0] + i) / 32][(int)(player[1] + player[3] + i2) / 32] == stoneBlock) {
                    player[3] = 0;
                }
            case basicTurretBlock:
                break;
            case ladderBlock:
                if (ammCoins == collCoins) {
                    FILE* file = fopen("levels.txt", "rb+");
                    fpos_t location = (long long)levelID * levelDataSize + 1097;
                    fsetpos(file, &location);
                    fputc(1, file);
                    fclose(file);
                    init = false;
                    screen = levelMenu;
                    memset(player, 0, sizeof(player));
                    memset(entityCount, 0, sizeof(entityCount));
                    memset(entityData, 0, sizeof(entityData));
                    memset(entityExtraData, 0, sizeof(entityExtraData));
                }
                break;
            }
        }
    }
    player[0] += player[2];
    player[1] += player[3];
}

bool playerLoS(int x,int y,bool sprite = false) {
    float ray[2] = { x * 32 + 16,y * 32 + 16 };
    float goal[2] = { player[0] + 16 - ray[0],player[1] + 16 - ray[1] };
    float minus = { max(abs(goal[0]),abs(goal[1])) };
    int count = (int)minus + 1;
    goal[0] /= minus;
    goal[1] /= minus;
    while (count >= 0) {
        ray[0] += goal[0];
        ray[1] += goal[1];
        if (map[(int)ray[0] / 32][(int)ray[1] / 32] && map[(int)ray[0] / 32][(int)ray[1] / 32] != map[x][y] &&
            map[(int)ray[0] / 32][(int)ray[1] / 32] != coinBlock && map[(int)ray[0] / 32][(int)ray[1] / 32] != ladderBlock) {
            if (sprite) {
                drawSprite(laserBall, ray[0] - goal[0], ray[1] - goal[1], 5, 1);
            }
            return false;
        }
        count--;
    }
    return true;
}

void updateBlocks() {
    for (int i = 0; i < 33; i++) {
        for (int i2 = 0; i2 < 33; i2++) {
            switch (map[i][i2]) {
            case gravityTurretBlock:
                if (mapData[i][i2]) {
                    mapData[i][i2]--;
                }
                if (!mapData[i][i2] && playerLoS(i, i2)) {
                    float ray[2] = { i * 32 + 16,i2 * 32 + 16 };
                    createEntity(3, i * 32 + 16, i2 * 32 + 16, (player[0] + 16 - ray[0]) / 30, (player[1] + 16 - ray[1]) / 30);
                    mapData[i][i2] = 450;
                }
                break;
            case laserTurretBlock:
                if (mapData[i][i2]) {
                    mapData[i][i2]--;
                }
                if (!mapData[i][i2] && playerLoS(i,i2,true)) {   
                    mapData[i][i2] = 195;
                    float ray[2] = { i * 32 + 16,i2 * 32 + 16 };
                    float goal[2] = { player[0] + 16 - ray[0],player[1] + 16 - ray[1] };
                    float minus = { max(abs(goal[0]),abs(goal[1])) };
                    goal[0] /= minus;
                    goal[1] /= minus;
                    while ((!map[(int)ray[0] / 32][(int)ray[1] / 32] || map[(int)ray[0] / 32][(int)ray[1] / 32] == map[i][i2] ||
                        map[(int)ray[0] / 32][(int)ray[1] / 32] == coinBlock || map[(int)ray[0] / 32][(int)ray[1] / 32] == ladderBlock) 
                        && ray[0] > 0 && ray[0] < 1080 && ray[1] > 0 && ray[1] < 1080) {
                        ray[0] += goal[0];
                        ray[1] += goal[1];
                    }
                    createEntity(1, i * 32 + 16, i2 * 32 + 16, ray[0], ray[1], 60);
                }
                break;
            case basicTurretBlock:
                if (mapData[i][i2]) {
                    mapData[i][i2]--;
                }
                if (!mapData[i][i2] && playerLoS(i,i2)) {
                    float ray[2] = { i * 32 + 16,i2 * 32 + 16 };
                    float goal[2] = { player[0] + 16 - ray[0],player[1] + 16 - ray[1] };
                    float minus = max(abs(player[0] + 16 - ray[0]),abs(player[1] + 16 - ray[1]));
                    goal[0] /= minus;
                    goal[1] /= minus;
                    createEntity(0, i * 32 + 16, i2 * 32 + 16, goal[0] * 3,goal[1] * 3);
                    mapData[i][i2] = 45;
                }
                break;
            }
        }
    }
}

void levelFN() {
    if (!init) {
        initFN();
        init = true;
    }
   
    playerCollision();
    input();
    player[2] /= 1.09;
    player[3] /= 1.09;
    drawPlayer();
    drawMap();
    if (beginGame) {
        updateBlocks();
        updateEntity();
    }
    else {
        drawWord("press space to begin", 20, 800, 1120, 4);
    }
}