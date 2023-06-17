#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

#define GBOARD_WIDTH 150
#define GBOARD_HEIGHT 40

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

extern char userName[30];
extern int carNumber;
extern char car[4][5][9];
extern int score;
extern double speed;
extern int item; // 현재 아이템
extern int heart; // 초기 목숨
extern int gameTime;
extern int tmpCarNumber;
extern char Itemshape[3][3][15];

int tmpHeart;
double carSpeed; // 보여주기 식 스피드
double tmpSpeed; // 최초의 스피드



void SetCurrentCursorPos(int x, int y) {
    COORD position = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

COORD GetCurrentCursorPos(void) {
    COORD curPoint;
    CONSOLE_SCREEN_BUFFER_INFO curInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curPoint.X = curInfo.dwCursorPosition.X;
    curPoint.Y = curInfo.dwCursorPosition.Y;

    return curPoint;
}


void RemoveCursor() {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void initScreen() {
    int ScreenX, ScreenY;
    ScreenX = 4;
    ScreenY = 1;

    SetCurrentCursorPos(ScreenX, ScreenY);
    for (int i = 0; i < 142; i++) {
        printf("*");
        Sleep(1);
    }
    for (int i = ScreenY + 1; i < 38; i++) {
        SetCurrentCursorPos(ScreenX + 141, i);
        printf("*");
        Sleep(1);
    }
    for (int i = 143; i > 4; i--) {
        SetCurrentCursorPos(i, 37);
        printf("*");
        Sleep(1);
    }
    for (int i = 37; i > ScreenY; i--) {
        SetCurrentCursorPos(ScreenX, i);
        printf("*");
        Sleep(1);
    }

    textcolor(CYAN, BLACK);
    SetCurrentCursorPos(41, 6);
    for (int i = 0; i < 30; i++) {
        printf("〓");
    }
    SetCurrentCursorPos(41, 16);
    for (int i = 0; i < 30; i++) {
        printf("〓");
    }
    textcolor(WHITE, BLACK);


    /* 게임 이름 start 버튼 생성  */

    textcolor(BLUE, BLACK);
    /*
    printf("■■■■   ■■■■    ■■■■  ■          ■  ■■■■ ");
    printf("■     ■  ■     ■      ■      ■        ■   ■");
    printf("■      ■ ■     ■      ■       ■      ■    ■ ");
    printf("■      ■ ■■■■       ■        ■    ■     ■■■■");
    printf("■      ■ ■ ■          ■         ■  ■      ■");
    printf("■     ■  ■   ■        ■          ■■       ■");
    printf("■■■■   ■     ■   ■■■■        ■        ■■■■");
*/

    int x = 32;
    int y = 7;
    x += 10;
    y -= 2;
    SetCurrentCursorPos(x, y + 3);
    printf("■■■■   ■■■■    ■■■■  ■          ■  ■■■■ ");
    SetCurrentCursorPos(x, y + 4);
    printf("■     ■  ■     ■      ■      ■        ■   ■");
    SetCurrentCursorPos(x, y + 5);
    printf("■      ■ ■     ■      ■       ■      ■    ■ ");
    SetCurrentCursorPos(x, y + 6);
    printf("■      ■ ■■■■       ■        ■    ■     ■■■■");
    SetCurrentCursorPos(x, y + 7);
    printf("■      ■ ■ ■          ■         ■  ■      ■");
    SetCurrentCursorPos(x, y + 8);
    printf("■     ■  ■   ■        ■          ■■       ■");
    SetCurrentCursorPos(x, y + 9);
    printf("■■■■   ■     ■   ■■■■        ■        ■■■■");
    Sleep(100);

    textcolor(WHITE, BLACK);

    SetCurrentCursorPos(x + 16, y + 13);
    //Sleep(1000);
    printf("**운 전 의 달 인**");
    SetCurrentCursorPos(x + 30, 16);
    int curPosX = 43;
    int curPosY = 24;
    for (y = 0; y < 5; y++) {
        for (x = 0; x < 8; x++) {
            SetCurrentCursorPos(curPosX + x, curPosY + y);
            printf("%c", car[0][y][x]);
        }
    }
    Sleep(100);
    curPosX += 15;
    for (y = 0; y < 5; y++) {
        for (x = 0; x < 8; x++) {
            SetCurrentCursorPos(curPosX + x, curPosY + y);
            printf("%c", car[1][y][x]);
        }
    }
    Sleep(100);
    curPosX += 15;
    for (y = 0; y < 5; y++) {
        for (x = 0; x < 8; x++) {
            SetCurrentCursorPos(curPosX + x, curPosY + y);
            printf("%c", car[2][y][x]);
        }
    }
    Sleep(100);
    curPosX += 15;
    for (y = 0; y < 5; y++) {
        for (x = 0; x < 8; x++) {
            SetCurrentCursorPos(curPosX + x, curPosY + y);
            printf("%c", car[3][y][x]);
        }
    }
    curPosX = 18;
    curPosY = 24;
    textcolor(YELLOW, BLACK);

    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒■▒▒■▒▒▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒■▒▒■▒▒▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒■▒▒▒▒▒▒▒▒■▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒■■■■■▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒");


    curPosX = 115;
    curPosY = 24;

    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒■▒▒■▒▒▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒■▒▒■▒▒▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒■▒▒▒▒▒▒▒▒■▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒■■■■■▒▒");
    SetCurrentCursorPos(curPosX, curPosY++);
    printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒");

    textcolor(WHITE, BLACK);

}

void eraseScreen() {
    SetCurrentCursorPos(9, 1);
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 150; j++) {
            printf(" ");
        }
    }
}

void countMotion() {
    /* 게임 시작 전 READY 3 - 2 - 1 재생 */
    int x, y;
    x = 50;
    y = 15;
    int tmp = y;

    textcolor(RED, BLACK);
    /*
    printf("■■■    ■■■       ■      ■■■    ■    ■ ");
    printf("■   ■   ■          ■■     ■    ■  ■    ■ ");
    printf("■■■    ■■■     ■  ■    ■    ■   ■■■ ");
    printf("■   ■   ■        ■ ■ ■   ■    ■     ■   ");
    printf("■    ■  ■■■   ■      ■  ■■■       ■   ");
    */
    SetCurrentCursorPos(x, y++);
    printf("■■■    ■■■       ■      ■■■    ■    ■ ");
    SetCurrentCursorPos(x, y++);
    printf("■   ■   ■          ■■     ■    ■  ■    ■ ");
    SetCurrentCursorPos(x, y++);
    printf("■■■    ■■■     ■  ■    ■    ■   ■■■ ");
    SetCurrentCursorPos(x, y++);
    printf("■   ■   ■        ■ ■ ■   ■    ■     ■   ");
    SetCurrentCursorPos(x, y++);
    printf("■    ■  ■■■   ■      ■  ■■■       ■   ");
    Sleep(1500);

    eraseScreen();
    x = 64;
    y = 7;
    y = tmp;
    textcolor(YELLOW, BLACK);

    SetCurrentCursorPos(x, y++);
    printf("* * * * * * ");
    SetCurrentCursorPos(x, y++);
    printf("* * * * * * * ");
    SetCurrentCursorPos(x, y++);
    printf("          * *");
    SetCurrentCursorPos(x, y++);
    printf("          * *");
    SetCurrentCursorPos(x, y++);
    printf("* * * * * * ");
    SetCurrentCursorPos(x, y++);
    printf("* * * * * * * ");
    SetCurrentCursorPos(x, y++);
    printf("          * *");
    SetCurrentCursorPos(x, y++);
    printf("          * *");
    SetCurrentCursorPos(x, y++);
    printf("* * * * * * *");
    SetCurrentCursorPos(x, y++);
    printf("* * * * * * ");
    SetCurrentCursorPos(x, y++);
    Sleep(500);
    eraseScreen();
    y = tmp;
    SetCurrentCursorPos(x, y++);
    printf("* * * * * * ");
    SetCurrentCursorPos(x, y++);
    printf("* * * * * * * ");
    SetCurrentCursorPos(x, y++);
    printf("          * *");
    SetCurrentCursorPos(x, y++);
    printf("         * *");
    SetCurrentCursorPos(x, y++);
    printf("        * *");
    SetCurrentCursorPos(x, y++);
    printf("      * *");
    SetCurrentCursorPos(x, y++);
    printf("    * *");
    SetCurrentCursorPos(x, y++);
    printf(" * *");
    SetCurrentCursorPos(x, y++);
    printf("* * * * * * *");
    SetCurrentCursorPos(x, y++);
    printf("* * * * * * * ");
    SetCurrentCursorPos(x, y++);
    Sleep(500);
    eraseScreen();
    x += 2;
    y = tmp;
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    printf("* *");
    SetCurrentCursorPos(x, y++);
    Sleep(500);

    textcolor(WHITE, BLACK);

}

void gameOver(int score) {

    int x = 40;
    int y = 10;
    SetCurrentCursorPos(x, y++);
    printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");
    SetCurrentCursorPos(x, y++);
    printf("|　DRIVE MASTER　　　　　　　　　　　　　　　　　　　[－][口][×] |");
    SetCurrentCursorPos(x, y++);
    printf("|￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣  ￣￣￣￣￣￣|");
    SetCurrentCursorPos(x, y++);
    printf("|　 GAME OVER!                                            　　　 |");
    SetCurrentCursorPos(x, y++);
    printf("|　 다시 도전하세요!                                      　　　 |");
    SetCurrentCursorPos(x, y++);
    printf("|　 당신의 점수는 ?                                       　　　 |");
    SetCurrentCursorPos(x, y++);
    printf("|　　　　＿＿＿＿＿＿　　　          ＿＿＿＿＿＿           　　　|");
    SetCurrentCursorPos(x, y++);
    printf("| 　　　｜   %d    |　              ｜   종료    |　              |", gameTime);
    SetCurrentCursorPos(x, y++);
    printf("|　　　　￣￣￣￣￣￣　　　          ＿＿＿＿＿＿             　|");
    SetCurrentCursorPos(x, y++);
    printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");
    Sleep(1000);
    SetCurrentCursorPos(50, 50);

}