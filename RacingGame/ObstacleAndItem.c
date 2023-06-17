#include <Windows.h>
#include <stdbool.h>
#include <time.h>

#define BLACK 0
#define RED 4
#define YELLOW 14 
#define WHITE 15 


char Obstacles[10][9] = {
    "еквгек",
    "еки╕ек",
    "еке°ек",
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
