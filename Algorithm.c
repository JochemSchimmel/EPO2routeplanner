#include <stdio.h>
#include <math.h>
#include "headers.h"


/*
//takes dimensions and matrix as input, prints all values in the matrix
void printMaze(){
    int i, j;
    for (i = 0; i < dimensions; i++){
        for( j = 0; j < dimensions; j++){

            printf(" %02d", matrix[i][j]);
        }
        printf("\n");
    }
}


Function called by traceback function




  Takes a cell with x and y coords as input. 
  I is passed to the function
 If a neighbour has value 0, it gives this neighbour the value i + 1
*/




/*
void printCrossing(int y, int x){
    if((x % 2 == 0) && (y % 2 == 0)){
        if((x >=2 && y >= 2)&&(x<= 10 && y <= 10)) printf("c%d%d\n", (y-2)/2, (x-2)/2);
    } 
}
*\



/*
//Changes all values in the matrix back to 0, but keeps the mines and nogo cells
void refreshMatrix(){
    int i, j;
    for (i = 0; i < dimensions; i++){
        for( j = 0; j < dimensions; j++){
            if(matrix[i][j] != -1){
                matrix[i][j] = 0;
            }
        }
    }
}

int windDirectionToAngle(char windDirection){
    int angle;
    switch (windDirection)
    {
    case 'n':
        angle = 0;
        break;
    case 'e':
        angle = 90;
        break;
    case 's':
        angle = 180;
        break;
    case 'w':
        angle = 270;
        break;
    }
    return angle;
}


char determineNextCommand(char nextDirection, char currentDirection){  
    char nextCommand;
    int nextAngle = windDirectionToAngle(nextDirection);
    int currAngle = windDirectionToAngle(currentDirection);

    int angle = nextAngle - currAngle;
    if(angle < -90) angle = angle + 360;
    switch(angle){
        case 0:
        nextCommand = 0x4;

        case 90:
        nextCommand = 0x1;

        case 180:
        nextCommand = 0x8;

        case 270:
        nextCommand = 0x2;
    }
    return nextCommand;
}



    takes a filled in matrix as input. Starting at a point x,y, 
    it visits the neighbour with value i -1, where the function is called recursively
    stops when the x y coords are the destination

void traceBack(int y, int x, int matrix[13][13], int n){
    int currentCellValue = matrix[y][x];
    if( currentCellValue == 1) return;
    if(y + 1 < n){
        if(matrix[y+1][x] == currentCellValue - 1){
                printCrossing(y + 1,x);
                traceBack(y + 1,x,matrix,n);
                return;
        }
    }
    if(x + 1 < n){
        if(matrix[y][x + 1] == currentCellValue - 1){
            printCrossing(y, x + 1);
            traceBack(y,x + 1,matrix,n);
            return;
        }
    }
    if(y - 1 > -1){
        if(matrix[y-1][x] == currentCellValue - 1){
                printCrossing(y - 1,x);
                traceBack(y - 1,x,matrix,n);
                return; 
        }
    }

    if(x - 1 > -1){
        if(matrix[y][x - 1] == currentCellValue - 1){
            printCrossing(y, x-1);
            traceBack(y,x - 1,matrix,n);
            return;
        }
    }
}
*/

int algorithm(int Dstations[], int t, int Stations[13][2]){
    int i = 0;
    int temp;
    int startX = 2;
    int startY = 8;
    int x = 0;
    int y = 0;
    float magnitude;
    float highestMag = 1000;
    float currentMag;
    int currentStation;
    int currentI;
    for (i = 0; i < t; i++) {
        temp = Dstations[i];
        if (temp != -1) {
            x = Stations[temp][0];
            y = Stations[temp][1];
            magnitude = sqrt(pow(startX - x, 2) + pow(startY - y, 2));
            if (magnitude < highestMag) {
                currentMag = magnitude;
                highestMag = magnitude;
                currentStation = Dstations[i];
                 currentI = i;
            }
        }

        printf("x: %d y: %d magnitude: %f, Current magnitude: %f, CurrentStation: %d Delete: %d\n", x, y, magnitude, currentMag, currentStation, currentI);

    }  

    short n = 9;
    int l = 1;
    int finishX = Stations[currentStation][0];
    int finishY = Stations[currentStation][1];
    matrix[finishX][finishY] = 1;
    

    Dstations[currentI] = -1;
     for (i = 0; i < n; i++) {
        printf("%d ", Dstations[i]);
    }
    printf("\n");
    return;
}

int main(){

    int startX, startY, finishY, finishX, startStation, finishStation, steps;
    int i = 1;
    int (*mazePointer)[13];
    int numDestinations = 3;

    int matrix[9][9] = {{-1, -1,  0, -1,  0, -1,  0, -1, -1},
                        {-1, -1,  0, -1,  0, -1,  0, -1, -1},
                        { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                        {-1, -1,  0, -1,  0, -1,  0, -1, -1},
                        { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                        {-1, -1,  0, -1,  0, -1,  0, -1, -1},
                        { 0,  0,  0,  0,  0,  0,  0,  0,  0},
                        {-1, -1,  0, -1,  0, -1,  0, -1, -1},
                        {-1, -1,  0, -1,  0, -1,  0, -1, -1}};    

     //First element empty to match index
     //x, y coords per station
    int stations[13][2] = {{0,0},
    {2,8}, {4,8}, {6,8}, {8,6}, {8,4}, {8,2}, {6,0}, {4,0}, {2,0}, {0,2}, {0,4}, {0,6}};
    int destinationStations[3] = {3,-1,8};
    


     algorithm(destinationStations, numDestinations, stations);

    //initialises the startstation
    startStation = 12;
    char currentDirection = 'n';
/*
    findNearestDestination(numDestinations, destinationChainHead, currentLocation, currentDirection);
    //target = findNearestDestination(destinationCoords);
    steps = algorithm(currentLocation, target, commandChainHead, halfCrossingList, startDirection);
*/
    return 0;
}