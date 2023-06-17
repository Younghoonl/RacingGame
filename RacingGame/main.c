#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>


typedef struct ObstacleStruct {
    int rN;
    int x;
}obstacle;

typedef struct ItemStruct {
    int x, y;
}itemStruct;

int gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.Y = y;
    pos.X = x;
    SetConsoleCursorPosition(hConsole, pos);
    return 0;
}

int main() {

}