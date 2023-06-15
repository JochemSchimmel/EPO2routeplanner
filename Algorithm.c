#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "headers.h"
#include "comm.h"


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

int algorithm(int Dstations[], int t, int Stations[13][2], int startStation){
    int i = 0;
    int temp;
    int startX = Stations[startStation][0];
    int startY = Stations[startStation][1];
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
        //printf("%d ", Dstations[i]);
    }
    printf("\n");
    return currentStation;
}

int main(){

    int startX, startY, finishY, finishX, startStation, finishStation, steps;
    //int i = 1;
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
    int destinationStations[3] = {10,7,5};
    
    //initialises the startstation
    startStation = 1;
    char currentDirection = 'n';
    char totalCommands_all[128] = "";

    for(int i=0;i<3;i++){
        int des = algorithm(destinationStations, numDestinations, stations, startStation);
        
        int desX = stations[des][0];
        int desY = stations[des][1];
        int beginX = stations[startStation][0];
        int beginY = stations[startStation][1];

        int nextX = desX - beginX;
        int nextY = desY - beginY;

        char commandsX[9] ="";
        char commandsY[9] = "";
        char totalCommands[18] = "";

        char forward = 'f';
        char left = 'l';
        char right = 'r';

        char tmp;

        int done = 0;

        if (startStation == 1 || startStation == 2 || startStation == 3 || startStation == 7 || startStation == 8 || startStation == 9) {
            if(des == 4 || des == 5 || des == 6 || des == 10 || des == 11 || des == 12){
                for (int i = 0; i<abs(nextY); i++) {
                    strcat(commandsY, &forward);
                }
                
                for (int j = 0; j<abs(nextX); j++) {
                    while(done == 0){
                    if((startStation == 7 || startStation == 8 || startStation == 9)){
                        if (nextX > 0) {
                            commandsX[0] = left;
                            done = 1;
                        }
                        if(nextX < 0) {
                            commandsX[0] = right;
                            done = 1;
                        }
 
                    } else if ((startStation == 1 || startStation == 2 || startStation == 3)) {
                        if (nextX < 0) {
                            commandsX[0] = left;
                            done = 1;
                        }
                        if(nextX > 0) {
                            commandsX[0] = right;
                            done = 1;
                        }
                    }
                    }
                    if(done != 0){
                        strcat(commandsX, &forward);
                    }
                    
                }

                strcat(totalCommands, commandsY);
                strcat(totalCommands, commandsX);

            } else if(des == 1 || des == 2 || des == 3){
                
                done = 0;

                if (startStation == 1 || startStation == 2 || startStation == 3){
                    if(done == 0){                        
                        if(nextX < 0) {
                            commandsX[0] = left;
                            tmp = left;
                            done = 1;
                        } else if(nextX > 0) {
                            commandsX[0] = right;
                            tmp = right;
                            done = 1;
                        }

                        for (int i = 0; i+1<abs(nextX);i++) {
                            strcat(commandsY, &forward);
                        }
                    }

                    strcat(totalCommands, commandsX);
                    strcat(totalCommands, commandsY);
                    strcat(totalCommands, commandsX);
                    
                } else if(startStation == 7 || startStation == 8 || startStation == 9) {
                    for (int i = 0; i<abs(nextY); i++){
                        strcat(commandsY, &forward);
                    }

                    if(nextX < 0){
                        commandsX[0] = right;
                        for (int j = 0; j<abs(nextX); j++){
                            strcat(commandsX,&forward);     
                        }
                        commandsX[abs(nextX)] = left;
                    } else if (nextX > 0) {
                        commandsX[0] = left;
                        for (int j = 0; j+1<abs(nextX); j++){
                            strcat(commandsX,&forward);     
                        }
                        commandsX[abs(nextX)] = right;
                    } else {
                        strcat(commandsX, &forward);
                    }


                    strcat(totalCommands, commandsY);
                    strcat(totalCommands, commandsX);
                }
                

            } else if(des == 7 || des == 8 || des == 9){
                
                done = 0;

                if (startStation == 7 || startStation == 8 || startStation == 9){
                    if(done == 0){                        
                        if(nextX < 0) {
                            commandsX[0] = right;
                            tmp = right;
                            done = 1;
                        } else if(nextX > 0) {
                            commandsX[0] = left;
                            tmp = left;
                            done = 1;
                        }

                        for (int i = 0; i+1<abs(nextX);i++) {
                            strcat(commandsY, &forward);
                        }
                    }

                    strcat(totalCommands, commandsX);
                    strcat(totalCommands, commandsY);
                    strcat(totalCommands, commandsX);
                    
                } else if(startStation == 1 || startStation == 2 || startStation == 3) {
                    for (int i = 0; i<abs(nextY); i++){
                        strcat(commandsY, &forward);
                    }

                    if(nextX < 0){
                        commandsX[0] = left;
                        for (int j = 0; j<abs(nextX); j++){
                            strcat(commandsX,&forward);     
                        }
                        commandsX[abs(nextX)] = right;
                    } else if (nextX > 0) {
                        commandsX[0] = right;
                        for (int j = 0; j+1<abs(nextX); j++){
                            strcat(commandsX,&forward);     
                        }
                        commandsX[abs(nextX)] = left;
                    } else {
                        strcat(commandsX, &forward);
                    }

                    strcat(totalCommands, commandsY);
                    strcat(totalCommands, commandsX);

                }
                

            }

            printf("\n\nTotal: %s\n\n", totalCommands);

        } else if (startStation == 4 || startStation == 5 || startStation == 6 || startStation == 10 || startStation == 11 || startStation == 12) {
            if(des == 1 || des == 2 || des == 3 || des == 7 || des == 8 || des == 9){
                for (int i = 0; i<abs(nextX); i++) {
                    strcat(commandsX, &forward);
                }
                
                for (int j = 0; j<abs(nextY); j++) {
                    while(done == 0){
                    if((startStation == 10 || startStation == 11 || startStation == 12)){
                        if (nextY > 0) {
                            commandsY[0] = right;
                            done = 1;
                        }
                        if(nextY < 0) {
                            commandsY[0] = left;
                            done = 1;
                        }
 
                    } else if ((startStation == 4 || startStation == 5 || startStation == 6)) {
                        if (nextY < 0) {
                            commandsY[0] = right;
                            done = 1;
                        }
                        if(nextY > 0) {
                            commandsY[0] = left;
                            done = 1;
                        }
                    }
                    }
                    if(done != 0){
                        strcat(commandsY, &forward);
                    }
                    
                }

                strcat(totalCommands, commandsX);
                strcat(totalCommands, commandsY);

            } else if(des == 4 || des == 5 || des == 6){
                
                done = 0;

                if (startStation == 4 || startStation == 5 || startStation == 6){
                    if(done == 0){                        
                        if(nextY < 0) {
                            commandsY[0] = right;
                            tmp = right;
                            done = 1;
                        } else if(nextY > 0) {
                            commandsY[0] = left;
                            tmp = left;
                            done = 1;
                        }

                        for (int i = 0; i+1<abs(nextY);i++) {
                            strcat(commandsX, &forward);
                        }
                    }

                    strcat(totalCommands, commandsY);
                    strcat(totalCommands, commandsX);
                    strcat(totalCommands, commandsY);
                    
                } else if(startStation == 10 || startStation == 11 || startStation == 12) {
                    for (int i = 0; i<abs(nextX); i++){
                        strcat(commandsX, &forward);
                    }

                    if(nextY < 0){
                        commandsX[0] = left;
                        for (int j = 0; j<abs(nextY); j++){
                            strcat(commandsY,&forward);     
                        }
                        commandsY[abs(nextY)] = right;
                    } else if (nextY > 0) {
                        commandsY[0] = right;
                        for (int j = 0; j+1<abs(nextY); j++){
                            strcat(commandsY,&forward);     
                        }
                        commandsY[abs(nextY)] = left;
                    } else {
                        strcat(commandsY, &forward);
                    }


                    strcat(totalCommands, commandsX);
                    strcat(totalCommands, commandsY);
                }
                

            } else if(des == 10 || des == 11 || des == 12){
                
                done = 0;

                if (startStation == 10 || startStation == 11 || startStation == 12){
                    if(done == 0){                        
                        if(nextY < 0) {
                            commandsY[0] = left;
                            tmp = left;
                            done = 1;
                        } else if(nextY > 0) {
                            commandsY[0] = right;
                            tmp = right;
                            done = 1;
                        }

                        for (int i = 0; i+1<abs(nextY);i++) {
                            strcat(commandsX, &forward);
                        }
                    }

                    strcat(totalCommands, commandsY);
                    strcat(totalCommands, commandsX);
                    strcat(totalCommands, commandsY);
                    
                } else if(startStation == 4 || startStation == 5 || startStation == 6) {
                    for (int i = 0; i<abs(nextX); i++){
                        strcat(commandsX, &forward);
                    }

                    if(nextY < 0){
                        commandsY[0] = right;
                        for (int j = 0; j<abs(nextY); j++){
                            strcat(commandsY,&forward);     
                        }
                        commandsY[abs(nextY)] = left;
                    } else if (nextY > 0) {
                        commandsY[0] = left;
                        for (int j = 0; j+1<abs(nextY); j++){
                            strcat(commandsY,&forward);     
                        }
                        commandsY[abs(nextY)] = right;
                    } else {
                        strcat(commandsY, &forward);
                    }

                    strcat(totalCommands, commandsX);
                    strcat(totalCommands, commandsY);

                }
                

            }

            printf("\n\nTotal: %s\n\n", totalCommands);

        }

        strcat(totalCommands_all, totalCommands);

        startStation = des;
        
    }

    int a;
    
    char commands[] = {};
    for(int i = 0; i<strlen(totalCommands_all); i++){
        if (totalCommands_all[i] == 'f') {
            commands[i] = 0x84;
        } else if (totalCommands_all[i] == 'r') {
            commands[i] = 0x81;
        } else if (totalCommands_all[i] == 'l') {
            commands[i] = 0x82;
        }
    }
    int numCommands = sizeof(commands)/sizeof(char);       
    a = runCar(numCommands, commands);
    
/*
    findNearestDestination(numDestinations, destinationChainHead, currentLocation, currentDirection);
    //target = findNearestDestination(destinationCoords);
    steps = algorithm(currentLocation, target, commandChainHead, halfCrossingList, startDirection);
*/
    return 0;
}