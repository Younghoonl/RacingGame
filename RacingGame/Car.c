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

void ShiftLeft() {

    DeleteCar(car[carNumber]);
    curPosX -= 2;
    SetCurrentCursorPos(curPosX, curPosY);
    showCar(car[carNumber]);
}

void ShiftRight() {
    DeleteCar(car[carNumber]);
    curPosX += 2;
    SetCurrentCursorPos(curPosX, curPosY);
    showCar(car[carNumber]);
}


int detectcollisionRoad(int roadPos) {
    if (curPosX < road[roadPos][0]) {
        ShiftRight();
        return 1;
    }
    else if (curPosX + 9 > road[roadPos][2]) {
        ShiftLeft();
        return 1;
    }
    return 0;
}

void ProcessKeyInPut(int roadPos) {
    int key;
    if (_kbhit() != 0) {
        key = _getch();
        switch (key) {
        case LEFT:
            if (detectcollisionRoad(roadPos) == 1) {
                return;
            }
            if (LeftRightChange == false) {
                ShiftLeft();
            }
            else {
                ShiftRight();
            }
            break;
        case RIGHT:
            if (detectcollisionRoad(roadPos) == 1) {
                return;
            }
            if (LeftRightChange == false) {
                ShiftRight();
            }
            else {
                ShiftLeft();
            }
            break;
        case SPACE:
            useItem();

            itemTimeStart = clock();
            break;
        case XX:
            if (detectcollisionRoad(roadPos) == 1) {
                return;
            }
            if (LeftRightChange == false) {
                ShiftRight();
                ShiftRight();
                ShiftRight();
            }
            else {
                ShiftLeft();
            }
            break;
        case Z:
            if (detectcollisionRoad(roadPos) == 1) {
                return;
            }
            if (LeftRightChange == false) {
                ShiftLeft();
                ShiftLeft();
                ShiftLeft();
            }
            else {
                ShiftRight();
            }
            break;
        default:
            break;
        }

    }
}