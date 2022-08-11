#include<stdio.h>
#include<conio.h>
#include<windows.h>

void GotoXY(int x, int y){
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//conio.h 입력헤더를 사용하여 입력 버퍼를 화면에 표시하지않고 바로 출력
//COORD 안에 있는 멤버 변수 X, Y를 연산자를 통해 사용이 가능


int main(void){
    int i;
    int x = 9;
    int y = 2;
    GotoXY(x, y);
    printf("┌");
    for(i = 0; i < 29; i++){
        printf("─");
    }
    printf("┐");

    for(i = 1; i < 22; i++){
        y++;
        GotoXY(x, y);
        printf("│");

        if(i == 12){
            GotoXY(18, i);
            printf(" ~Hello~");
        }
        x += 30;
        GotoXY(x, y);
        printf("│");
        x = 9;
    }

    GotoXY(x, y);
    printf("└");
    for(i = 0; i < 29; i++){
        printf("─");
    }
    printf("┘");

    _getch();

    return 0;
}