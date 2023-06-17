#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>


// score --> time
// 물약 아이템

// 스테이지 만들기
// 중간에 난이도 업
// 아이템 나오는 빈도 수를 늘리고, 아이템 3개씩 나오게 함
// 첫번째 자동차 속도 100 --> 10 --> 1
// 두번째 자동차 속도 80 --> 8 -> 1
// BGM
// PPT


#define COMMAND_SIZE 256

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 

#define OB1 67
#define OB2 91
#define OB3 47
#define OB4 59
#define OB5 87
#define OB6 57
#define OB7 71
#define OB8 49
#define OB9 38

#define ITEM1 187 // 좋은 아이템
#define ITEM2 79 // 

#define POTION 80 // 물약

int flag = 0;
double road[360][3];

char command[COMMAND_SIZE] = { '\0', };

int curPosX = 38;
int curPosY = 36;

extern bool LeftRightChange;
extern bool BoostChange;
extern bool CarChange;
bool using = false;


clock_t start;
clock_t end;

char userName[30];
int score = 0;
double speed = 100.0;
int carNumber = 0;
int item = 0; // 현재 아이템
int heart = 6; // 초기 목숨
int gameTime = 0;
int tmpCarNumber;
extern double carSpeed;
extern double tmpSpeed;
extern int tmpHeart;

clock_t itemTimeStart = 0;
clock_t itemTimeEnd = 0;

int tmpCycle[8] = { 0,315,270,225,180,135,90,45 };
int tmpC = 0;

int lines = 45;
int cols = 150;


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