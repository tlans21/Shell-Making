#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

typedef char MapData ;
typedef struct _currentlocation{
    int X;
    int Y;
} Location;

#define MAP_H 20
#define MAP_W 10
#define HALF_W 15
#define HALF_H 10

#define WALL 5
#define EMPTY 0
#define BLOCK 1

void init(){
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 100; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y){
    COORD pos;
    pos.X = 2*x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}




int KeyDown(){
    if(kbhit()){
        return _getch(); 
    }else{
        return -1;
    }
}

void drawWall(char map[MAP_H][MAP_W]){
    int height;
    int width;
    int input;
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(outhandle, 11); // 11?? ???? ???? ??? ???


    //???? ?? ????
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
    printf("<Exit : 'T' / Pause : 'P'>");
    SetConsoleTextAttribute(outhandle, 7);
}

int frontMenu(){
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int input;

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

    while(1){
        input = KeyDown();
        if(input == 's' || input == 'S'){
            break;
        }
        if(input == 't' || input == 'T'){
            break;
        }
        gotoxy(7, 15);
        SetConsoleTextAttribute(outhandle, 11);
        printf(" === Press 's' to start ===");
        Sleep(1000/2);
        gotoxy(7, 15);
        printf("                                 \n");
        Sleep(1000/2);
        gotoxy(20, 20);
    }

    return input;
}

void drawMap(char map[MAP_H][MAP_W]){
    int height;
    int width;
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);

    for(height = 0; height < MAP_H; height++){
        for(width = 0; width < MAP_W; width++){
            gotoxy(width + 2, height +2);
            if(map[height][width] == EMPTY){
                printf(".");
            }else if(map[height][width] == BLOCK){
                SetConsoleTextAttribute(outhandle, 14);
                printf("��");
                SetConsoleTextAttribute(outhandle, 7);
            }
        }
        printf("\n");
    }
}

void drawSubMap(int best, int score){
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(outhandle, 14);
    gotoxy(HALF_W + 4, HALF_H + 1);
    printf("%4d", best);
    gotoxy(HALF_W + 4, HALF_H + 2);
    printf("%4d", score);
    SetConsoleTextAttribute(outhandle, 7);
}

void drawSubShape(char map[MAP_H][MAP_W], int shape[4][4]){
    int height;
    int width;
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for(height = 3; height <= 6; height++){
        for(width = HALF_W+1; width <=HALF_W+4; width++){
            gotoxy(width, height);
            printf(" ");
        }
    }
    for(height = 3; height <= 6; height++){
        for(width = HALF_W+1; width <=HALF_W+4; width++){
            if(shape[height-3][width - HALF_W - 1] == BLOCK){
                gotoxy(width, height);
                SetConsoleTextAttribute(outhandle, 14);
                printf("��");
                SetConsoleTextAttribute(outhandle, 7);
            }
        }
    }
}

void drawShape(char map[MAP_H][MAP_W], int shape[4][4], Location Loc){
    int height;
    int width;

    for(height = 0; height < 4; height++){
        for(width = 0; width <4; width++){
            if(shape[height][width] == BLOCK){
                map[Loc.Y + height][Loc.X + width] = BLOCK;
            }
        }
    }
}
///////////////////////////////////////////////////////

void startTime(){
    int i;
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);

    for(i = 0; i < 3; i++){
        gotoxy(2, 0);
        SetConsoleTextAttribute(outhandle, 14);
        printf("Start : %d sec", 3-i);
        Sleep(1000);
    }
    gotoxy(2,0);
    printf("                    ");
}

void mapInit(char map[MAP_H][MAP_W]){
    int i = 0;
    int j = 0;

    for(i = 0; i < MAP_H; i++){
        for(j = 0; j < MAP_W; j++){
            map[i][j] = EMPTY;
        }
    }
}
void locInit(Location * Loc){
    Loc->X = 3;
    Loc->Y = 0;
}
void copyBlock(int blockShape[4][4], int copy[4][4]){
    int i;
    int j;
    for(i = 0; i < 4; i ++){
        for(j = 0; j < 4; j++){
            blockShape[i][j] = copy[i][j];
        }
    }
}
void setBlock(int blockshape[4][4]){
    int shape[7][4][4] = {
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,0,0},
            {0,1,1,1},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,1},
            {0,1,0,0},
            {0,0,0,0}
        }
    };
    srand((unsigned int)(time(NULL)));

    switch(rand() % 7){
        case 0:
            copyBlock(blockshape, shape[0]);
            break;
        case 1:
            copyBlock(blockshape, shape[1]);
            break;
        case 2:
            copyBlock(blockshape, shape[2]);
            break;
        case 3:
            copyBlock(blockshape, shape[3]);
            break;
        case 4:
            copyBlock(blockshape, shape[4]);
            break;
        case 5:
            copyBlock(blockshape, shape[5]);
            break;
        case 6:
            copyBlock(blockshape, shape[6]);
        default :
            break;
    }
}

void removeShape(char map[MAP_H][MAP_W], int blockshape[4][4],Location * Loc){
    int height;
    int width;

    for(height = 0; height<4; height++){
        for(width = 0; width < 4; width++){
            if(blockshape[height][width] == BLOCK){
                map[Loc->Y + height][Loc->X + width] = EMPTY;
            }
        }
    }
}

int getShapeLeftLoc(int blockShape[4][4]){
    int height;
    int width;
    int leftW = 4;
    for(width = 0; width < 4; width++){
        for(height = 0; height<4; height++){
            if(blockShape[height][width] == BLOCK){
                if(leftW > width){
                    leftW = width;
                }
            }
        }
    }
    return leftW;
}
int getShapeRightLoc(int blockShape[4][4]){
    int height;
    int width;
    int rightW = 0;
    for(width = 3; width >= 0; width--){
        for(height = 3; height>=0; height--){
            if(blockShape[height][width] == BLOCK){
                if(rightW < width){
                    rightW = width;
                }
            }
        }
    }
    return rightW+1;
}

int getShapeBottomLoc(int blockShape[4][4]){
    int height;
    int width;
    int bottomH = 0;
    for(width = 3; width >= 0 ; width--){
        for(height = 3; height >= 0; height--){
            if(blockShape[height][width] == BLOCK){
                if(bottomH < height){
                    bottomH = height;
                }
            }
        }
    }
    return bottomH+1;
}
int getEachBottomLoc(int blockShape[4][4], int width){
    int height;
    int bottomH = -1;
    for(height = 3; height >= 0; height--){
        if(blockShape[height][width] == BLOCK){
            if(bottomH < height){
                bottomH = height;
            }
        }
    }
    return bottomH;
}

int main(){
    init();
    //char map[MAP_H][MAP_W] ={0,};
    //wall1(map[MAP_H][MAP_W]);
    frontMenu();
    //_getch();
    return 0;
}



