#include <stdio.h>
#include "headers.h"

//takes dimensions and matrix as input, prints all values in the matrix
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

/*
 * Takes a cell with x and y coords as input. 
 * I is passed to the function
 If a neighbour has value 0, it gives this neighbour the value i + 1
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

/*
    takes a filled in matrix as input. Starting at a point x,y, 
    it visits the neighbour with value i -1, where the function is called recursively
    stops when the x y coords are the destination
*/
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

struct coords findNearestStation(stationList){
    struct coords target;
    target.x = 5;
    target.y = 3;
    return target;
}


int main(){
    short dimensions = 9;
    //                           9      8      7
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
    struct coords target;
    struct coords currentLocation;
    short dimensions = 9;

     //First element empty to match index
    int stations[13][2] = {{0,0},
                {8,2}, {8,4}, {8,6}, {6,8}, {4,8}, {2,8}, {0,6}, {0,4}, {0,2}, {2,0}, {4,0}, {6,0}};

    int destinationStations = {10,11,1};
    int *destinationStationsPtr = destinationStations;
    int startX, startY, finishY, finishX, startStation, finishStation;
    
    int (*mazePtr)[dimensions];
    mazePtr = maze;

    //
    startStation = 1;
    char startDirection = 'n';
    currentLocation.x = 8;
    currentLocation.y = 2;
    //Decides the direction based on startstation, n, e, s or w
    
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

    target = findNearestStation(destinationStationsPtr);
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