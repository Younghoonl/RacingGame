#pragma once
#include <Windows.h>
#include <stdbool.h>
#include <time.h>


#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define XX 120
#define Z 122

extern int curPosX;
extern int curPosY;
extern int carNumber;
extern char car[4][5][9];
extern double road[360][3];
extern int item;

typedef struct ObstacleStruct {
    int rN;
    int x;
}obstacle;