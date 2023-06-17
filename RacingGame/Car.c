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

extern int flag;
extern clock_t itemTimeStart;
extern clock_t itemTimeEnd;

extern void useItem();

static COORD curPos;

bool LeftRightChange = false;

static void SetCurrentCursorPos(int x, int y) {
    COORD position = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

static COORD GetCurrentCursorPos(void) {
    COORD curPoint;
    CONSOLE_SCREEN_BUFFER_INFO curInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curPoint.X = curInfo.dwCursorPosition.X;
    curPoint.Y = curInfo.dwCursorPosition.Y;

    return curPoint;
}

void showCar(char carBlock[5][9]) {
    int x, y;
    for (y = 0; y < 5; y++) {
        for (x = 0; x < 8; x++) {
            SetCurrentCursorPos(curPosX + x, curPosY + y);
            if (flag == 0)
                textcolor(15, 0);
            if (flag == 1)
                textcolor(4, 0);
            printf("%c", carBlock[y][x]);
        }

    }
}

void DeleteCar(char carBlock[5][9]) {
    int y, x;
    COORD curPos = GetCurrentCursorPos();
    for (y = 0; y < 5; y++) {
        for (x = 0; x < 9; x++) {
            SetCurrentCursorPos(curPosX + x, curPosY + y);
            printf(" ");
        }
    }
}