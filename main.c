#include <stdio.h>
#include "headers.h"

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
void addValueToNeighbours(int x, int y, int i){
    if(y + 1 < dimensions){
        if(matrix[y + 1][x] == 0){
            matrix[y + 1][x] = i + 1;
        }
    }
    if(y - 1 > -1){
        if(matrix[y - 1][x] == 0){
            matrix[y - 1][x] = i + 1;
        }
    }
    if(x + 1 < dimensions){
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




void checkfori(int i){
    int y, x;
    
    for (y = 0; y < dimensions; y++){
        for( x = 0; x < dimensions; x++){
            if(matrix[y][x] == i){
                addValueToNeighbours(x, y, i);
            }
            
        }
        
    }
    
}

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


/*
    takes a filled in matrix as input. Starting at a point x,y, 
    it visits the neighbour with value i -1, where the function is called recursively
    stops when the x y coords are the destination
*/
void traceBack(struct Coords location, struct Commands *currentCommandPtr, struct Destinations crossingList, char currentDirection){
    int currentCellValue = matrix[location.y][location.x];
    char nextDirection;
    int y = location.y;
    int x = location.x;
    struct Coords nextLocation;
    crossingList.coords = location;

    
    if(currentCellValue == 1) {
        currentCommandPtr = NULL;
        return;
    }
    if(y + 1 < dimensions){
        if(matrix[y+1][x] == currentCellValue - 1){              
            nextLocation.x = x;
            nextLocation.y = y + 1;
            nextDirection = 's';
            currentCommandPtr->command = determineNextCommand(nextDirection, currentDirection);
            traceBack(nextLocation, currentCommandPtr->next, *(crossingList.next), nextDirection);
            return;
        }
    }
    if(x + 1 < dimensions){
        if(matrix[y][x + 1] == currentCellValue - 1){            
            nextLocation.x = x + 1;
            nextLocation.y = y;
            nextDirection = 'e';
            currentCommandPtr->command = determineNextCommand(nextDirection, currentDirection);
            traceBack(nextLocation, currentCommandPtr->next, *(crossingList.next), nextDirection);
            return;
        }
    }
    if(y - 1 > -1){
        if(matrix[y-1][x] == currentCellValue - 1){                       
            nextLocation.x = x;
            nextLocation.y = y - 1;
            nextDirection = 'n';
            currentCommandPtr->command = determineNextCommand(nextDirection, currentDirection);
            traceBack(nextLocation, currentCommandPtr->next, *(crossingList.next), nextDirection);
            return; 
        }
    }

    if(x - 1 > -1){
        if(matrix[y][x - 1] == currentCellValue - 1){
            nextLocation.x = x - 1;
            nextLocation.y = y;
            nextDirection = 'w';
            currentCommandPtr->command = determineNextCommand(nextDirection, currentDirection);
            traceBack(nextLocation, currentCommandPtr->next, *(crossingList.next), nextDirection);
            return;
        }
    }
}


/*
 * Function that takes the stations and coords of all stations as inputs, and returns a refererence to the memory adress
 of a list of all coords of the stations, so 
 * a list of coordinate structs can be made
*/
struct Destinations * stationToCoords(int stationCoords[13][2], int numberOfDestinations, int destinationStations[numberOfDestinations]){
    int i = 0;
    struct Destinations destinationChain;
    struct Destinations *destinationChainHead;
    destinationChainHead = &destinationChain;

    for (i = 0; i < numberOfDestinations - 1; i++){ //Loops to numberofDestinations - 1 so the pointer to next can be set to NULL
        destinationChain.coords.x = stationCoords[destinationStations[i]][0];
        destinationChain.coords.x = stationCoords[destinationStations[i]][1];
        destinationChain = *(destinationChain.next);
    }
    destinationChain.coords.x = stationCoords[destinationStations[i]][0];
    destinationChain.coords.x = stationCoords[destinationStations[i]][1];
    destinationChain.next = NULL;
    return destinationChainHead;
}


int algorithm(struct Coords startLocation, struct Coords targetLocation, struct Commands *commandChain, struct Destinations crossingList, char currentDirection){
    matrix[targetLocation.y][targetLocation.x] = 1;
    int i = 0;
    int steps = 0;
    while(matrix[targetLocation.y][targetLocation.x] < 1){
        i++;
        checkfori(i);
    }
    steps = i;
    traceBack(startLocation, commandChain, crossingList , currentDirection);
    refreshMatrix();
    return steps;
}

/*
When this function is called, the first item in the 'destination' linked list becomes the closest station
*/
findNearestDestination(int numberOfDestinations, struct Destinations *destinationChainHead, struct Coords currentLocation, char startDirection){
    struct Destinations *closestDestination;
    struct Destinations currentDestination;
    struct Destinations *prevDestination;
    struct Destinations *temp_1, *temp_2;
    struct Commands * trash; //We only need this pointer to make the algorithm function work
    struct Destinations trash2; //Again, the retrun value of this pointer by the algorithm func is not used in this function
    currentDestination = *destinationChainHead;
    int i, steps;
    int leastSteps = 999;
    while(currentDestination.next){
        steps = algorithm(currentLocation, currentDestination.coords, trash, trash2, startDirection);
        if(steps < leastSteps) {
            leastSteps = steps;
            temp_1 = destinationChainHead;
            destinationChainHead = &currentDestination;
            temp_2 = &currentDestination.next;
            prevDestination->next = &temp_2;
        }
        prevDestination = &currentDestination;
        currentDestination = *(currentDestination.next);
    }
}

int main(){

    struct Coords target;
    struct Coords currentLocation;
    struct Coords *destinationPtr;

    struct Destinations *destinationChainHead;
    struct Commands *commandChainHead;
    struct Destinations *halfCrossingListHead;
    struct Destinations halfCrossingList;
    halfCrossingListHead = &halfCrossingList;
    
    int startX, startY, finishY, finishX, startStation, finishStation, steps;

     //First element empty to match index
     //x, y coords per station
    int stations[13][2] = {{0,0},
    {2,8}, {4,8}, {6,8}, {8,6}, {8,4}, {8,2}, {6,0}, {4,0}, {2,0}, {0,2}, {0,4}, {0,6}};
    int destinationStations[] = {10,11,1};

    int numDestinations = sizeof(destinationStations)/sizeof(destinationStations[0]); 
    int * stationsPtr = stations;
    int * destinationStationsPtr = destinationStations;
    
    destinationChainHead = stationToCoords(destinationStationsPtr, numDestinations, stationsPtr);
    

    //initialises the startstation
    startStation = 1;
    char startDirection = 'n';
    currentLocation.x = stations[startStation][0];
    currentLocation.x = stations[startStation][1];


    

    char currentDirection = startDirection;



    findNearestDestination(numDestinations, destinationChainHead, currentLocation, currentDirection);
    //target = findNearestDestination(destinationCoords);
    steps = algorithm(currentLocation, target, commandChainHead, halfCrossingList, startDirection);
    
    return 0;
}