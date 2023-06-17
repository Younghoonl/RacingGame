#include <Windows.h>
#include <stdbool.h>
#include <time.h>

#define BLACK 0
#define RED 4
#define YELLOW 14 
#define WHITE 15 


char Obstacles[10][9] = {
    "ⅹ∀ⅹ",
    "ⅹ㉧ⅹ",
    "ⅹωⅹ",
    "      ",
};

extern double road[360][3];
extern int item;
extern bool LeftRightChange;
extern bool using;
bool BoostChange = false;
bool CarChange = false;
extern double speed;
extern double carSpeed;
extern int carNumber;
extern int heart;
extern int tmpHeart;
extern clock_t itemTimeStart;
extern clock_t itemTimeEnd;

static int gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.Y = y;
    pos.X = x;
    SetConsoleCursorPosition(hConsole, pos);
    return 0;
}

typedef struct ObstacleStruct {
    int rN; // randomNumber
    int x;
}obstacle;

typedef struct ItemStruct {
    int x;
}itemStruct;

void textcolor(int foreground, int background)
{
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void showObstacles1(obstacle ob) {

    textcolor(RED, BLACK);
    printf("%s", Obstacles[ob.rN]);
    textcolor(WHITE, BLACK);
}

void deleteObstacles1() {
    printf("%s", Obstacles[3]);
}

void useItem() {
    /*
    * 초기 item = 0 , item과 collision 후에 item 1~3중에 하나 지정 -> space 키 누르면, 사용
    * item 0 : 아이템이 존재하지 않음
    * item 1 : 키 좌우 변환
    * item 2 : 부스터
    * item 3 : 자동차 변환
    */

    if (item == 0) {
        return; // 아무 일도 일어나지 않음
    }
    else if (item == 1) {
        // key 변환
        LeftRightChange = true;
    }
    else if (item == 2) {
        // 부스터
        BoostChange = true;
        speed /= 10;
        carSpeed += 22.5;
    }
    else if (item == 3) {
        CarChange = true;
        carNumber = 4;
    }
    else if (item == 4) {
        if ((heart + 1) <= tmpHeart) {
            heart += 1;

        }
    }

    using = true;
}