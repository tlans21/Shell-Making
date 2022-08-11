#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

typedef char MapData ;

#define MAP_H 20
#define MAP_W 10
#define HALF_W 15
#define HALF_H 10

void init(){
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;// Ŀ�� ǥ�� ���� 1�� 0����
    cursorInfo.dwSize = 100; // Ŀ���� �β�
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y){
    COORD pos;
    pos.X = 2*x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



//kbhit()�� Ű�� �������� 1, �� ������ 0�� ��ȯ
//Ű����� �Է����� �� ����ڴ� �̰��� ���� �� �ʿ䰡����
int KeyDown(){
    if(kbhit()){
        return _getch(); //Ű���� �Է� ������ ����� x
    }else{
        return -1;
    }
}

void drawWall(char map[MAP_H][MAP_W]){
    int height;
    int width;
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(outhandle, 11); // 11�� ���� ���� �� �ڸ�


    //���� �� ����
    for(height = 0; height <= MAP_H + 1; height++){
        for(width = 0; width <= MAP_W + 1; width++){
            gotoxy(width + 1, height + 1);
            if(height == 0 || width == 0 || height == MAP_H + 1 || width == MAP_W + 1){
                printf("��");
            }
        }
    }

    gotoxy(HALF_W, 1);
    SetConsoleTextAttribute(outhandle, 14);
    printf("<Next>");
    SetConsoleTextAttribute(outhandle, 11);
    gotoxy(HALF_W, 2);

    for(height = 0; height <=6; height++){
        for(width = HALF_W; width <=HALF_W+6; width++){
            gotoxy(width, height + 2);
            if(width == HALF_W || height == 0 || width == HALF_W + 6 || height == 6){
                printf("��");
            }
        }
    }
    SetConsoleTextAttribute(outhandle, 14);
    gotoxy(HALF_W, HALF_H + 1);
    printf("Best Score : ");
    gotoxy(HALF_W, HALF_H + 2);
    printf("Score : ");
    gotoxy(HALF_W, HALF_H + 12);
    printf("<���� : 'T' / Pause : 'P'>");
    SetConsoleTextAttribute(outhandle, 7);
}

int frontMenu(){
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int Keyinput;

    gotoxy(1, 2);
    SetConsoleTextAttribute(outhandle, 11);
    printf("=====================================================");
    gotoxy(1, 3);
    SetConsoleTextAttribute(outhandle, 14);
    printf("====================T E T R I S======================");
    gotoxy(1, 4);
    SetConsoleTextAttribute(outhandle, 11);
    printf("=====================================================");

    SetConsoleTextAttribute(outhandle, 14);
    gotoxy(2, 6);
    printf("Left : �� ");
    gotoxy(2, 7);
    printf("Right : �� ");
    gotoxy(2, 8);
    printf("Rotation : �� ");
    gotoxy(2, 9);
    printf("Down : �� OR Space bar");
    gotoxy(2, 10);
    printf("Exit : 'T' ");
    return 0;
}



int main(){
    //char map[MAP_H][MAP_W] ={0,};
    //wall1(map[MAP_H][MAP_W]);
    //frontMenu();
    //_getch();
    return 0;
}



