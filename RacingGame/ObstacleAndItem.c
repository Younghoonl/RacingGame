#include <Windows.h>
#include <stdbool.h>
#include <time.h>

#define BLACK 0
#define RED 4
#define YELLOW 14 
#define WHITE 15 


char Obstacles[10][9] = {
    "������",
    "������",
    "������",
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
    * �ʱ� item = 0 , item�� collision �Ŀ� item 1~3�߿� �ϳ� ���� -> space Ű ������, ���
    * item 0 : �������� �������� ����
    * item 1 : Ű �¿� ��ȯ
    * item 2 : �ν���
    * item 3 : �ڵ��� ��ȯ
    */

    if (item == 0) {
        return; // �ƹ� �ϵ� �Ͼ�� ����
    }
    else if (item == 1) {
        // key ��ȯ
        LeftRightChange = true;
    }
    else if (item == 2) {
        // �ν���
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