#pragma once
#define levelDataSize 1098
extern int levelID;
enum mapPieces{airBlock,stoneBlock,flagBlock,ladderBlock,basicTurretBlock,coinBlock,laserTurretBlock,gravityTurretBlock};
extern enum mapPieces;
void drawMap();
extern unsigned char map[33][33];
extern unsigned short int mapData[33][33];
extern unsigned char mapSource[33][33];