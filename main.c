#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>


typedef struct _currentlocation{
    int X;
    int Y;
} Location;

#define MAP_H 20
#define MAP_W 10
#define HALF_W 15
#define HALF_H 10
#define EXIT 100

#define WALL 5
#define EMPTY 0
#define BLOCK 1

#define UP 72
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ESC 27
#define DOWN 80


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
        return getch(); 
    }else{
        return -1;
    }
}

void drawWall(char map[MAP_H][MAP_W]){
    int height;
    int width;
    int input;
    HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(outhandle, 11); 


    
    for(height = 0; height <= MAP_H + 1; height++){
        for(width = 0; width <= MAP_W + 1; width++){
            gotoxy(width + 1, height + 1);
            if(height == 0 || width == 0 || height == MAP_H + 1 || width == MAP_W + 1){
                printf("■");
            }
        }
        printf("\n");
    }

    gotoxy(HALF_W, 1);
    SetConsoleTextAttribute(outhandle, 14);
    printf("<Next>");
    SetConsoleTextAttribute(outhandle, 11);
    

    for(height = 2; height <=7; height++){
        for(width = HALF_W; width <=HALF_W+5; width++){
            gotoxy(width, height + 2);
            if(width == HALF_W || height == 2 || width == HALF_W + 5 || height == 7){
                printf("■");
            }
        }
    }
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
    printf("Left : ← ");
    gotoxy(2, 7);
    printf("Right : → ");
    gotoxy(2, 8);
    printf("Rotation : ↑ ");
    gotoxy(2, 9);
    printf("Down :  OR Space bar");
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
        SetConsoleTextAttribute(outhandle, 7);
        Sleep(1000/2);
        gotoxy(7, 15);
        printf("                                 \n");
        Sleep(1000/2);
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
                printf("■");
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
                printf("■");
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
void locationInit(Location * Loc){
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

void removeShape(char map[MAP_H][MAP_W], int blockshape[4][4], Location * Loc){
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
int getEachLeftLoc(int blockShape[4][4], int height){
    int width;
    int leftW = 5;
    for(width = 0; width < 4; width++){
        if(blockShape[height][width] == BLOCK){
            if(leftW > width){
                leftW = width;
            }
        }
    }
    return leftW;
}
int getEachRightLoc(int blockShape[4][4], int height){
    int width;
    int rightW = -1;
    for(width = 0; width < 4; width++){
        if(blockShape[height][width] == BLOCK){
            if(rightW < width){
                rightW = width;
            }
        }
    }
    return rightW;
}

void goLeft(char map[MAP_H][MAP_W], int blockShape[4][4], Location* Loc){
    int leftW = getShapeLeftLoc(blockShape);//가장 왼쪽 끝 위치 알기, 즉 범위 설정
    int boundaryArr[4] = {0};
    int i;
    for(i = 0; i < 4; i++){
        boundaryArr[i] = getEachLeftLoc(blockShape, i);
        //각 높이별로 왼쪽이 어디에있는지 기록, 각 왼쪽 위치
    }

    if((Loc -> X) + leftW > 0){
        if(!((boundaryArr[0] != 5 && map[Loc->Y ][Loc->X + boundaryArr[0] - 1] != EMPTY)
        ||(boundaryArr[1] != 5 && map[Loc->Y + 1][Loc->X + boundaryArr[1] - 1] != EMPTY)
        ||(boundaryArr[2] != 5 && map[Loc->Y + 2][Loc->X + boundaryArr[2] - 1] != EMPTY)
        ||(boundaryArr[3] != 5 && map[Loc->Y + 3][Loc->X + boundaryArr[3] - 1] != EMPTY))){

            removeShape(map, blockShape, Loc);
            (Loc->X)--;
        }
    }
}

void goRight(char map[MAP_H][MAP_W], int blockShape[4][4], Location * Loc){
    int rightW = getShapeRightLoc(blockShape);
    int boundaryArr[4] = {0};
    int i;
    for(i = 0; i < 4; i++){
        boundaryArr[i] = getEachLeftLoc(blockShape, i);
    }

    if((Loc -> X) + rightW < MAP_W){
        if(!((boundaryArr[0] != 5 && map[Loc->Y ][Loc->X + boundaryArr[0] + 1] != EMPTY)
        ||(boundaryArr[1] != 5 && map[Loc->Y + 1][Loc->X + boundaryArr[1] + 1] != EMPTY)
        ||(boundaryArr[2] != 5 && map[Loc->Y + 2][Loc->X + boundaryArr[2] + 1] != EMPTY)
        ||(boundaryArr[3] != 5 && map[Loc->Y + 3][Loc->X + boundaryArr[3] + 1] != EMPTY))){

            removeShape(map, blockShape, Loc);
            (Loc -> X)++;
        }
    }
}

int fixShape(char map[MAP_H][MAP_W], int blockShape[4][4], Location *Loc){
    int width;
    int height;
    for(width = 0; width < 4; width++){
        for(height = 0; height < 4; height++){
            if(blockShape[height][width] == 1){
                map[Loc->Y + height][Loc->X + width] = BLOCK;
            }
        }
    }
}

int goDown(char map[MAP_H][MAP_W], int blockShape[4][4], Location *Loc){
    int bottomH = getShapeBottomLoc(blockShape);
    int bottomArr[4] = {0};
    int i;
    
    for(i = 0; i < 4; i++){
        bottomArr[i] = getEachBottomLoc(blockShape, i);
    }

    if(Loc->Y + bottomH == MAP_H 
    ||(bottomArr[0] != -1 && map[Loc->Y + bottomArr[0] +1][Loc->X] != EMPTY)
    ||(bottomArr[1] != -1 && map[Loc->Y + bottomArr[1] +1][Loc->X + 1] != EMPTY)
    ||(bottomArr[2] != -1 && map[Loc->Y + bottomArr[2] +1][Loc->X + 2] != EMPTY)
    ||(bottomArr[3] != -1 && map[Loc->Y + bottomArr[3] +1][Loc->X + 3] != EMPTY)){
        fixShape(map, blockShape, Loc);
            Sleep(1000/8);
            return TRUE;
    }

    if(Loc->Y + bottomH < MAP_H){
        removeShape(map, blockShape, Loc);
        Sleep(1000/8);
        (Loc->Y)++;
    }
    return FALSE;
}

void rotate(char map[MAP_H][MAP_W], int blockShape[4][4], Location *Loc){
    int i;
    int j;
    int tmp[4][4];
    int leftW, rightW, bottomH;

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(blockShape[i][j] ==BLOCK){
                tmp[j][3-i] == blockShape[i][j];
                blockShape[i][j] = EMPTY;
            }
        }
    }

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(tmp[i][j] == 1){
                blockShape[i][j] = BLOCK;
            }
        }
    }
    leftW = getShapeLeftLoc(blockShape);
    if(Loc->X +leftW < 0){
        goRight(map, blockShape, Loc);
        if(leftW == 0){
            goRight(map, blockShape, Loc);
        }
    }

    rightW = getShapeRightLoc(blockShape);
    if(Loc->X + rightW >MAP_W){
        goLeft(map, blockShape, Loc);
        if(rightW == 4){
            goLeft(map, blockShape, Loc);
        }
    }
        
    bottomH = getShapeBottomLoc(blockShape);
    if(Loc->Y + bottomH > MAP_H){
        removeShape(map, blockShape, Loc);
        (Loc->Y)--;
        if(bottomH == 4){
            (Loc->Y)--;
        }
    }
}

int goSpace(char map[MAP_H][MAP_W], int blockShape[4][4], Location *Loc){
    int bottomH = getShapeBottomLoc(blockShape);
    int bottomArr[4] = {0};
    int i;
    for(i=0; i<4; i++){
        bottomArr[i] = getEachBottomLoc(blockShape, i);
    }
    while(1){
        if(Loc->Y + bottomH == MAP_H 
        ||(bottomArr[0] != -1 && map[Loc->Y + bottomArr[0] + 1][Loc -> X + 0] !=EMPTY)
        ||(bottomArr[1] != -1 && map[Loc->Y + bottomArr[1] + 1][Loc -> X + 1] !=EMPTY)
        ||(bottomArr[2] != -1 && map[Loc->Y + bottomArr[2] + 1][Loc -> X + 2] !=EMPTY)
        ||(bottomArr[3] != -1 && map[Loc->Y + bottomArr[3] + 1][Loc -> X + 3] !=EMPTY)){

            fixShape(map, blockShape, Loc);

            Sleep(1000/8);
            return TRUE;
        }
        if(Loc->Y + bottomH < MAP_H){
            removeShape(map, blockShape, Loc);
            (Loc->Y)++;  //점점 내려가는 역할
        }
    }
    return FALSE;
}

void deleteLine(char map[MAP_H][MAP_W], int height){
    int width;
    for(width = 0; width < MAP_W; width++){
        map[height][width] = EMPTY;
    }
}

void organizeLine(char map[MAP_H][MAP_W], int height){
    int width;
    while(height > 1){
        for(width = 0; width<MAP_W; width++){
            map[height][width] = map[height-1][width];
        }
        height--;
    }
}


void checkLine(char map[MAP_H][MAP_W], Location Loc, int *score){
    int height;
    int width;
    int full;
    int count = 0;

    for(height = MAP_H; height >= (Loc.Y - 1); height--){
        full = 0;
        for(width = 0; width < MAP_W; width++){
            if(map[height][width] == EMPTY){
                break;
            }else{
                full++;
            }
        }
        if(full == MAP_W){
            (*score) +=5;
            deleteLine(map, height);
            organizeLine(map, height);
        }
    }
}
int GameOver(char map[MAP_H][MAP_W], int score, int bestScore){
    FILE * wfp;
    int width = 0;
    for(width = 0; width < MAP_W; width++){
        if(map[0][width] == BLOCK){
        HANDLE outhandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(outhandle, 14);
        gotoxy(HALF_W -7, HALF_H-2);
        printf("====== Game Over ======");
        gotoxy(HALF_W -6, HALF_H-1);
        printf("Your Score : %4d\n", score);
        SetConsoleTextAttribute(outhandle, 7);
        gotoxy(1, MAP_H + 3);

        if(score >= bestScore){
            wfp = fopen("score.txt", "w");
            fprintf(wfp, "%d", score);
            fclose(wfp);
        }

        system("pause");
        return TRUE;
        }
    }

    return FALSE;
}
/////////////////////////

int GameStart(char map[MAP_H][MAP_W]){
    int key;
    int reachBottom = FALSE;
    int one = TRUE;
    int score = 0;
    int bestScore = 0;
    int blockShape[4][4] = {0};
    int blockShapeSub[4][4] = {0};
    Location loc = {2,2};
    FILE * rfp;
    if((rfp = fopen("score.txt", "r")) == NULL){
        FILE * wfp;
        wfp = fopen("score.txt", "w");
        fprintf(wfp, "%d", 0);
        fclose(wfp);
    }
    fscanf(rfp, "%d", &bestScore);
    mapInit(map);
    drawWall(map);

    locationInit(&loc);
    setBlock(blockShape);
    drawSubShape(map, blockShapeSub);

    while(1){
        if(reachBottom == TRUE){
            if(GameOver(map,score, bestScore)){
                return EXIT;
            }
            checkLine(map, loc, &score);
            checkLine(map, loc, &score);
            locationInit(&loc);
            copyBlock(blockShape, blockShapeSub);
            setBlock(blockShapeSub);
            drawSubShape(map, blockShapeSub);
            reachBottom = FALSE;
        }

        drawSubMap(bestScore, score);
        drawShape(map, blockShape, loc);
        drawMap(map);
        reachBottom = goDown(map, blockShape, &loc);
        if(reachBottom == TRUE){
            continue;
        }
        key = KeyDown();
        if(key == 't' || key == 'T'){
            break;
        }
        if(key == 'p' || key == 'P'){
            system("pause");
            system("cls");
            drawMap(map);
            drawWall(map);
        }
        if(key == SPACE){
            goSpace(map, blockShape, &loc);
        }
        if(key == 224 || key == 0){
            key = getch();
            if(key == UP){
                rotate(map, blockShape, &loc);
            }else if(key == LEFT){
                goLeft(map, blockShape, &loc);
            }else if(key == RIGHT){
                goRight(map, blockShape, &loc);
            }
        }
    }
    return EXIT;
}



int main(){
    char map[MAP_H][MAP_W] = {0};
    int key;
    init();

    system("color 7");
    system("mode con: cols=57 lines=25");

    while(1){
        key = frontMenu();
        if(key == 't' || key == 'T'){
            break;
        }
        system("cls");
        GameStart(map);
        Sleep(1000/3);
        system("cls");
    }
    return 0;

}



