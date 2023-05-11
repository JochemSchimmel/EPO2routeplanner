#include <stdio.h>
#include "headers.h"
//takes dimensions and matrix as input, prints maze
void printMaze(short n, int matrix[n][n]){
    int i, j;
    for (i = 0; i < n; i++){
        for( j = 0; j < n; j++){

            printf(" %02d", matrix[i][j]);
        }
        printf("\n");
    }
}

/*
int* getInput(int matrix[13][13]){
    int numberOfEdges;
    scanf("%d", &numberOfEdges);
    int i, x, y, start, finish;
    char direction;
    for (i = 0; i < numberOfEdges; i++){
        scanf("%d %d %c", &y, &x, &direction);
        switch(direction){
            case 'n':
                matrix[2*y + 1][2*x + 2] = -1;
                break;
            case 'e':
                matrix[2*y + 2][2*x + 3] = -1;
                break;   
            case 's': 
                matrix[2*y + 3][2*x + 2] = -1;
                break;
            case 'w': 
                matrix[2*y + 2][2*x + 1] = -1;
                break;

        }
    }
    scanf("%d %d", &start, &finish);
    int stationList[2] = {start, finish};
    int *stationListPtr = stationList;
    return stationListPtr;
}
*/

/*Function called by traceback function

*/
void addValueToNeighbours( short n, int matrix[n][n], int x, int y, int i){
    if(y + 1 < n){
        if(matrix[y + 1][x] == 0){
            matrix[y + 1][x] = i + 1;
        }
    }
    if(y - 1 > -1){
        if(matrix[y - 1][x] == 0){
            matrix[y - 1][x] = i + 1;
        }
    }
    if(x + 1 < n){
        if(matrix[y][x + 1] == 0){
            matrix[y][x + 1] = i + 1;
        }
    }
    if(x - 1 > -1){
        if(matrix[y][x - 1] == 0){
            matrix[y][x - 1] = i + 1;
        }
    }
}

/*
void printCrossing(int y, int x){
    if((x % 2 == 0) && (y % 2 == 0)){
        if((x >=2 && y >= 2)&&(x<= 10 && y <= 10)) printf("c%d%d\n", (y-2)/2, (x-2)/2);
    } 
}
*/

void checkfori(short n, int matrix[n][n], int i){
    int y, x;
    
    for (y = 0; y < n; y++){
        for( x = 0; x < n; x++){
            if(matrix[y][x] == i){
                int (*matrixPtr)[n];
                matrixPtr = matrix;
                addValueToNeighbours(matrixPtr, n, x, y, i);
            }
            
        }
        
    }
    
}

//Changes all values in the matrix back to 0, but keeps the mines and nogo cells
void refreshMatrix(int n, int matrix[n][n]){
    int i, j;
    for (i = 0; i < n; i++){
        for( j = 0; j < n; j++){
            if(matrix[i][j] != -1){
                matrix[i][j] = 0;
            }
        }
    }
}



char determineRelativeDirection(int nextDirectionAngle, char currentDirection, char directionList[99]){
    int angle = nextDirectionAngle - currentDirection;
    char turn;
    if(angle < -90) angle = angle + 360;
    if(angle == 270) angle -= 90;
    switch(angle){
        case 0:
        turn = 0x4;
        case -90:
        turn = 0x2;
        case 90:
        turn = 0x1;
        case 180:
        turn = 0x8;
    }
    return turn;
}

void traceBack(int n, int matrix[n][n], int y, int x, char directionList[99], int currentDirection, int steps){
    int currentCellValue = matrix[y][x];
    char * directionListPtr = directionList;
    int nextDirection;
    if( currentCellValue == 1) return;
    if(y + 1 < n){
        if(matrix[y+1][x] == currentCellValue - 1){
                nextDirection = determineRelativeDirection(180, currentDirection, directionListPtr);
                currentDirection = nextDirection;
                traceBack(y + 1,x,matrix,n);
                return;
        }
    }
    if(x + 1 < n){
        if(matrix[y][x + 1] == currentCellValue - 1){
            nextDirection = determineRelativeDirection(90, currentDirection,directionListPtr);
            currentDirection = nextDirection;
            traceBack(y,x + 1,matrix,n);
            return;
        }
    }
    if(y - 1 > -1){
        if(matrix[y-1][x] == currentCellValue - 1){
                nextDirection = determineRelativeDirection(0, currentDirection);
                currentDirection = nextDirection;
                traceBack(y - 1,x,matrix,n);
                return; 
        }
    }

    if(x - 1 > -1){
        if(matrix[y][x - 1] == currentCellValue - 1){
            nextDirection = determineRelativeDirection(270, currentDirection);
            traceBack(y,x - 1,matrix,n);
            return;
        }
    }
}


int main()
{//                              9      8      7
    int maze[9][9] =    {{0,  0, 0,  0, 0,  0, 0,  0,  0},
                        { 0, -1, 0, -1, 0, -1, 0, -1,  0},
    /*              10*/{ 0,  0, 0,  0, 0,  0, 0,  0,  0},/*6*/
                        { 0, -1, 0, -1, 0, -1, 0, -1,  0},
    /*              11*/{ 0,  0, 0,  0, 0,  0, 0,  0,  0},/*5*/
                        { 0, -1, 0, -1, 0, -1, 0, -1,  0},
    /*              12*/{ 0,  0, 0,  0, 0,  0, 0,  0,  0},/*4*/
                        { 0, -1, 0, -1, 0, -1, 0, -1,  0},
                        { 0,  0, 0,  0, 0,  0, 0,  0,  0}};
    //                           1      2      3
    
     //First element empty to match index
    int stations[13][2] = {{0,0},
                {12,4}, {12,6}, {12,8},{8,12}, {6,12}, {4,12}, {0,8},  {0,6},  {0,4}, {4,0},  {6,0},  {8,0}};

    //station 0 does not exist, stations 1-3 face north, stations 4-6 face east, etc
    char startStationDirection[13] = {'x', 'n','n','n','w','w','w','s','s','s','e','e','e'};

    int startX, startY, finishY, finishX, startStation, finishStation;
    short dimensions = 9;
    int (*mazePtr)[dimensions];
    mazePtr = maze;
    //int (*stationPtr) = getInput(mazePtr);
    //startStation = stationPtr[0];
    //finishStation = stationPtr[1];
    //printf("%d %d\n", startStation, finishStation);
    startStation = 1;
    finishStation = 11;
    //Decides the direction based on startstation, n, e, s or w
    char startDirection = startStationDirection[startStation];
    //give startstation value i = 1
    startY = stations[startStation][0];
    startX = stations[startStation][1];
    finishY = stations[finishStation][0];
    finishX = stations[finishStation][1];
    

    char directionList[99];
    char *directionPtr = directionList;
    char currentDirection = startDirection;
    maze[finishY][finishX] = 1;
    int i = 1;
    while(maze[startY][startX] < 1){
        checkfori(dimensions, mazePtr, i);
        printMaze(dimensions, mazePtr);
        printf("\n");
        i++;
        
    }
    int steps = 0;
    traceBack(dimensions, mazePtr, startY, startX, directionPtr, currentDirection, steps);
    
    return 0;
}