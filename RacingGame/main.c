#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>
#include "Car.h"
#include "Items.h"

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


char potions[5][10] = {
  " ♡  ♡ ",
  "♡♡♡♡",
  " ♡♡♡ ",
  "   ♡   ",
  "        "
};


void setRoad() {
    double ly, ry;
    double y;
    int obNum;

    for (int i = 0; i < 360; i++) {
        if (i % ITEM1 == 0 && i != 0)
            road[i][1] = 10;    // 좋은 item 
        else if (i % ITEM2 == 0 && i != 0)
            road[i][1] = 11;    // 나쁜 item 
        else if (i % OB1 == 0) road[i][1] = 1;
        else if (i % OB2 == 0) road[i][1] = 2;
        else if (i % OB3 == 0) road[i][1] = 3;
        else if (i % OB4 == 0) road[i][1] = 4;
        else if (i % OB5 == 0) road[i][1] = 5;
        else if (i % OB6 == 0) road[i][1] = 6;
        else if (i % OB7 == 0) road[i][1] = 7;
        else if (i % OB8 == 0) road[i][1] = 8;
        else if (i % OB9 == 0) road[i][1] = 9;
        else  road[i][1] = 0;
    }
    road[POTION][1] = 12;

    for (int i = 0; i < 90; i++)
    {
        road[i][0] = 25;
        road[i][2] = 70;
    }

    for (int i = 0, j = 90; i < 1440; j++, i += 8) {
        y = sin(i * 3.14 / 180);

        ly = y * 20 + 25.0;
        ry = y * 20 + 70.0;

        road[j][0] = ly;
        road[j][2] = ry;
    }

    for (int i = 270, k = 0; i < 360; i++)
    {
        road[i][0] = 25 + k;
        road[i][2] = 70 + k;
        if (i < 292) k++;
        else if (i >= 293 && i < 315) k--;
        else if (i >= 315 && i < 337) k++;
        else if (i >= 338 && i < 360)  k--;
    }
}

int stage = 1;

void show_road() {

    int road_idx = 0;
    int j = 0;
    int i, k = 0;
    int tmp;
    srand(time(NULL));

    obstacle ob1[3];
    ob1[0].rN = 0;
    ob1[1].rN = 0;
    ob1[2].rN = 0;
    ob1[0].x = 24;
    ob1[1].x = 6;
    ob1[2].x = 41;

    obstacle ob2[3];
    ob2[0].rN = 1;
    ob2[1].rN = 1;
    ob2[2].rN = 1;
    ob2[0].x = 10;
    ob2[1].x = 18;
    ob2[2].x = 35;

    obstacle ob3[3];
    ob3[0].rN = 2;
    ob3[1].rN = 2;
    ob3[2].rN = 2;
    ob3[0].x = 39;
    ob3[1].x = 30;
    ob3[2].x = 8;

    itemStruct it;
    it.x = 7;

    int potionX;

    int roadPos = tmpCycle[tmpC] + curPosY;

    int degree = 360;
    int x, y;
    x = 25;
    y = 15;
    while (1) {
        if (stage == 1) {
            SetCurrentCursorPos(x, y++);
            printf(" ■■■  ■■■■    ■       ■■■    ■■■      ■");
            SetCurrentCursorPos(x, y++);
            printf("■          ■      ■■     ■         ■       ■ ■");
            SetCurrentCursorPos(x, y++);
            printf("  ■■      ■     ■  ■    ■  ■■   ■■■      ■");
            SetCurrentCursorPos(x, y++);
            printf("      ■    ■    ■ ■ ■   ■    ■   ■          ■");
            SetCurrentCursorPos(x, y++);
            printf(" ■■■     ■   ■      ■   ■■■    ■■■    ■■■");
            SetCurrentCursorPos(x, y++);
            Sleep(1000);
            x = 25;
            y = 15;
            printf("                                                               ");
            SetCurrentCursorPos(x, y++);
            printf("                                                               ");
            SetCurrentCursorPos(x, y++);
            printf("                                                               ");
            SetCurrentCursorPos(x, y++);
            printf("                                                               ");
            SetCurrentCursorPos(x, y++);
            printf("                                                               ");
            SetCurrentCursorPos(x, y++);
            printf("                                                               ");

            stage++;
        }
        showCar(car[carNumber]);

        textcolor(WHITE, BLACK);
        for (k = degree - road_idx, j = 0; j < 45; j++, k++) {
            k = k % degree;
            gotoxy(road[k][0], j);
            textcolor(WHITE, GREEN);
            printf("*");
            textcolor(WHITE, BLACK);
            int obstacleX = 0;
            int itemX = 0;
            tmp = road[k][1];
            int tmpX;

            switch (tmp) { // 
            case 0:  break;
            case 1:  gotoxy(road[k][0] + ob1[0].x, j);
                showObstacles1(ob1[0]);
                obstacleX = road[k][0] + ob1[0].x;
                break;
            case 2:  gotoxy(road[k][0] + ob1[1].x, j);
                showObstacles1(ob1[1]);
                obstacleX = road[k][0] + ob1[1].x;
                break;
            case 3:  gotoxy(road[k][0] + ob1[2].x, j);
                showObstacles1(ob1[2]);
                obstacleX = road[k][0] + ob1[2].x;
                break;
            case 4:  gotoxy(road[k][0] + ob2[0].x, j);
                showObstacles1(ob2[0]);
                obstacleX = road[k][0] + ob2[0].x;
                break;
            case 5:  gotoxy(road[k][0] + ob2[1].x, j);
                showObstacles1(ob2[1]);
                obstacleX = road[k][0] + ob2[1].x;
                break;
            case 6:  gotoxy(road[k][0] + ob2[2].x, j);
                showObstacles1(ob2[2]);
                obstacleX = road[k][0] + ob2[2].x;
                break;
            case 7:  gotoxy(road[k][0] + ob3[0].x, j);
                showObstacles1(ob3[0]);
                obstacleX = road[k][0] + ob3[0].x;
                break;
            case 8:  gotoxy(road[k][0] + ob3[1].x, j);
                showObstacles1(ob3[1]);
                obstacleX = road[k][0] + ob3[1].x;
                break;
            case 9:  gotoxy(road[k][0] + ob3[2].x, j);
                showObstacles1(ob3[2]);
                obstacleX = road[k][0] + ob3[2].x;
                break;

            case 10:
                itemX = road[k][0] + 7;

                tmpX = itemX;
                textcolor(BLACK, YELLOW);
                for (int i = 0; i < 5; i++) {
                    gotoxy(tmpX + i * 7, j);
                    printf("%s", itemIcon);
                }
                textcolor(WHITE, BLACK);

                break;
            case 11: itemX = road[k][0] + 7;

                tmpX = itemX;
                textcolor(WHITE, LIGHTRED);
                for (int i = 0; i < 5; i++) {
                    gotoxy(tmpX + i * 7, j);

                    printf("%s", itemIcon);
                }
                textcolor(WHITE, BLACK);
                break;
            case 12:
                potionX = road[POTION][0] + 20;
                textcolor(LIGHTBLUE, BLACK);
                gotoxy(potionX, j);
                printf("%s", potions[0]);
                gotoxy(potionX, j + 1);
                printf("%s", potions[1]);
                gotoxy(potionX, j + 2);
                printf("%s", potions[2]);
                gotoxy(potionX, j + 3);
                printf("%s", potions[3]);
                textcolor(WHITE, BLACK);
                break;

            default:
                break;
            }
            //obstacle collision
            if ((tmp >= 1 && tmp <= 9) && k == roadPos) {
                flag = 0;
                int p = (obstacleX - curPosX);
                p = p > 0 ? p : -p;
                if (p < 7) {
                    flag = 1;
                    heart--;
                    if (heart == 0) {
                        return;
                    }
                }
            }
            // item collision
            if ((tmp == 10 || tmp == 11) && k == roadPos) {
                item = rand() % 4 + 1;

                gameBoardInfo();
                if (item == 1) {
                    // key 변환
                    using = true;
                    LeftRightChange = true;
                    itemTimeStart = clock();
                }
            }
            // potion collision
            if (tmp == 12 && k == roadPos) {
                int p = (potionX - curPosX);
                p = p > 0 ? p : -p;
                if (p < 5) {
                    if ((heart + 1) <= tmpHeart) {
                        heart += 1;

                    }
                }
            }

            gotoxy(road[k][2], j);
            textcolor(WHITE, GREEN);
            printf("*");
            textcolor(WHITE, BLACK);

        }

        Sleep(speed);

        for (k = degree - road_idx, j = 0; j < 45; j++, k++) {
            k = k % degree;
            gotoxy(road[k][0], j);
            printf(" ");
            tmp = road[k][1];
            switch (tmp) {
            case 0:  break;
            case 1:  gotoxy(road[k][0] + ob1[0].x, j);
                deleteObstacles1();
                break;
            case 2:  gotoxy(road[k][0] + ob1[1].x, j);
                deleteObstacles1();
                break;
            case 3:  gotoxy(road[k][0] + ob1[2].x, j);
                deleteObstacles1();
                break;
            case 4:  gotoxy(road[k][0] + ob2[0].x, j);
                deleteObstacles1();
                break;
            case 5:  gotoxy(road[k][0] + ob2[1].x, j);
                deleteObstacles1();
                break;
            case 6:  gotoxy(road[k][0] + ob2[2].x, j);
                deleteObstacles1();
                break;
            case 7:  gotoxy(road[k][0] + ob3[0].x, j);
                deleteObstacles1();
                break;
            case 8:  gotoxy(road[k][0] + ob3[1].x, j);
                deleteObstacles1();
                break;
            case 9:  gotoxy(road[k][0] + ob3[2].x, j);
                deleteObstacles1();
                break;
            case 10:

                for (int i = 0; i < 5; i++) {
                    gotoxy(road[k][0] + 7 + i * 7, j);
                    printf("  ", itemIcon);
                }
                break;
            case 11:
                for (int i = 0; i < 5; i++) {
                    gotoxy(road[k][0] + 7 + i * 7, j);

                    printf("  ", itemIcon);
                }
                break;
            case 12:
                potionX = road[POTION][0] + 20;
                gotoxy(potionX, j);
                printf("%s", potions[4]);
                gotoxy(potionX, j + 1);
                printf("%s", potions[4]);
                gotoxy(potionX, j + 2);
                printf("%s", potions[4]);
                gotoxy(potionX, j + 3);
                printf("%s", potions[4]);
                break;

            default:
                break;
            }

            gotoxy(road[k][2], j);
            printf(" ");
        }
        detectcollisionRoad(roadPos);


        for (int i = 0; i < 100; i++) {
            ProcessKeyInPut(roadPos);
        }

        roadPos--;
        if (roadPos <= 0) {
            roadPos = 360;
        }

        itemTimeEnd = clock();
        if ((double)(itemTimeEnd - itemTimeStart) / CLOCKS_PER_SEC >= 1.0 && using == true && item == 4) {
            item = 0;
        }
        if ((double)(itemTimeEnd - itemTimeStart) / CLOCKS_PER_SEC >= 5.0 && using == true) {
            if (BoostChange == true) {
                if (carNumber == 0) {
                    carSpeed = 105.4;
                }
                else {
                    carSpeed = 85.4;
                }
            }

            LeftRightChange = false;
            BoostChange = false;
            CarChange = false;
            speed = tmpSpeed;
            carNumber = tmpCarNumber;


            item = 0;
            using = false;
        }
        end = clock();
        gameTime = (double)(end - start) / CLOCKS_PER_SEC; //초단위 변환
        gameBoardInfo();

        road_idx++;

        if (road_idx % 45 == 0) {
            tmpC++;
            tmpC = tmpC % 8;
            roadPos = tmpCycle[tmpC] + curPosY;

        }
        if (road_idx > degree) {
            road_idx = 0;
            it.x = road[1][0];

        }

        if (road_idx + 2 == degree) {
            // stage 변경!
            if (stage == 2) {
                x = 25;
                y = 15;
                SetCurrentCursorPos(x, y++);
                printf(" ■■■  ■■■■    ■       ■■■    ■■■     ■■");
                SetCurrentCursorPos(x, y++);
                printf("■          ■      ■■     ■         ■       ■    ■");
                SetCurrentCursorPos(x, y++);
                printf("  ■■      ■     ■  ■    ■  ■■   ■■■        ■");
                SetCurrentCursorPos(x, y++);
                printf("      ■    ■    ■ ■ ■   ■    ■   ■           ■");
                SetCurrentCursorPos(x, y++);
                printf(" ■■■     ■   ■      ■   ■■■    ■■■    ■■■■");
                SetCurrentCursorPos(x, y++);
                Sleep(2000);
                x = 25;
                y = 15;
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                speed *= 0.6;
                carSpeed += 20;
                stage++;
            }
            else if (stage == 3) {
                x = 25;
                y = 15;
                SetCurrentCursorPos(x, y++);
                printf(" ■■■  ■■■■    ■       ■■■    ■■■    ■■■");
                SetCurrentCursorPos(x, y++);
                printf("■          ■      ■■     ■         ■       ■    ■");
                SetCurrentCursorPos(x, y++);
                printf("  ■■      ■     ■  ■    ■  ■■   ■■■        ■");
                SetCurrentCursorPos(x, y++);
                printf("      ■    ■    ■ ■ ■   ■    ■   ■       ■    ■");
                SetCurrentCursorPos(x, y++);
                printf(" ■■■     ■   ■      ■   ■■■    ■■■    ■■■");
                Sleep(2000);
                x = 25;
                y = 15;
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                SetCurrentCursorPos(x, y++);
                printf("                                                               ");
                speed *= 0.6;
                carSpeed += 20;
                stage++;
            }
        }

        if (heart == 0) {
            break;
        }
    }
}

int main() {
    sprintf(command, "mode con: lines=%d cols=%d", lines, cols);
    system(command);
    RemoveCursor();

    int re;

    initScreen();
    int key;
    key = _getch();
    eraseScreen();
    carNumber = gameInfoSelect();

    eraseScreen();
    countMotion();
    eraseScreen();

    gameBoardInfo();

    SetCurrentCursorPos(curPosX, curPosY);
    start = clock();

    showCar(car[carNumber]);
    setRoad();
    show_road();

    eraseScreen();
    gameOver(score);
    Sleep(1500);
    eraseScreen();


}