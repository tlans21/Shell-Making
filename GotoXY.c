#include<stdio.h>
#include<conio.h>
#include<windows.h>

void GotoXY(int x, int y){
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//conio.h �Է������ ����Ͽ� �Է� ���۸� ȭ�鿡 ǥ�������ʰ� �ٷ� ���
//COORD �ȿ� �ִ� ��� ���� X, Y�� �����ڸ� ���� ����� ����


int main(void){
    int i;
    int x = 9;
    int y = 2;
    GotoXY(x, y);
    printf("��");
    for(i = 0; i < 29; i++){
        printf("��");
    }
    printf("��");

    for(i = 1; i < 22; i++){
        y++;
        GotoXY(x, y);
        printf("��");

        if(i == 12){
            GotoXY(18, i);
            printf(" ~Hello~");
        }
        x += 30;
        GotoXY(x, y);
        printf("��");
        x = 9;
    }

    GotoXY(x, y);
    printf("��");
    for(i = 0; i < 29; i++){
        printf("��");
    }
    printf("��");

    _getch();

    return 0;
}