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


/*
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
*/


/*
    takes a filled in matrix as input. Starting at a point x,y, 
    it visits the neighbour with value i -1, where the function is called recursively
    stops when the x y coords are the destination
*/
void traceBack(int y, int x, char directionList[99], int currentDirection){
    int currentCellValue = matrix[y][x];
    char * directionListPtr = directionList;
    int nextDirection;
    if( currentCellValue == 1) return;
    if(y + 1 < dimensions){
        if(matrix[y+1][x] == currentCellValue - 1){
                nextDirection = determineRelativeDirection(180, currentDirection, directionListPtr);
                traceBack(y + 1,x, directionListPtr, nextDirection);
                return;
        }
    }
    if(x + 1 < dimensions){
        if(matrix[y][x + 1] == currentCellValue - 1){
            nextDirection = determineRelativeDirection(90, currentDirection,directionListPtr);
            currentDirection = nextDirection;
            traceBack(y,x + 1, directionListPtr, nextDirection);
            return;
        }
    }
    if(y - 1 > -1){
        if(matrix[y-1][x] == currentCellValue - 1){
                nextDirection = determineRelativeDirection(0, currentDirection);
                currentDirection = nextDirection;
                traceBack(y - 1,x, directionListPtr, nextDirection);
                return; 
        }
    }

    if(x - 1 > -1){
        if(matrix[y][x - 1] == currentCellValue - 1){
            nextDirection = determineRelativeDirection(270, currentDirection);
            traceBack(y,x - 1, directionListPtr, nextDirection);
            return;
        }
    }
}
/*
struct Coords findNearestStation(struct Coords destinations[]){
    struct Coords target;
    target.x = 5;
    target.y = 3;
    return target;
}
*/



/*
 * Function that takes the stations and coords of all stations as inputs, and returns a refererence to the memory adress
 of a list of all coords of the stations, so 
 * a list of coordinate structs can be made
*/
struct Coords * stationToCoords(int stations, int stationCoords, int numberOfDestinations){
    int i = 0;
    struct Coords * destinationCoordList[numberOfDestinations];

    for (i = 0; i < numberOfDestinations; i++){
        destinationCoordList[i].x = stationCoords[numberOfDestinations[i]][0];
        destinationCoordList[i].y = stationCoords[numberOfDestinations[i]][1];
    }
    return &destinationCoordList[0];
}


int algorithm(struct Coords startLocation, struct Coords targetLocation){
    matrix[startLocation.y][startLocation.x] = 1;
    int i = 0;
    int steps = 0;
    while(matrix[targetLocation.y][targetLocation.x] < 1){
        i++;
        checkfori(i);
    }
    steps = i;

    return steps;
}


/* Function that finds the closest station using the xy coords of stations, the list of stations to visit
 * Returns a struct with the coords of the closest station

struct Coords findNearestStation(int stationsXY, int * destinationStations, struct Coords currentLocation){
    
    int i, j;
    int leastSteps = 999;
    int totalSteps;
    int closestStation = 0;
    for(i = 0; i < numDestinations; i++){
        while(matrix[currentLocation.y][currentLocation.x] < 1){
            totalSteps = algorithm(currentLocation, targetLocation);
        }
        if(totalSteps < leastSteps){ 
            leastSteps = totalSteps;
            closestStation = destinationStations[i];
        }
    }
    struct Coords target;
    target.x = stationsXY[destinationStations[i]][0];
    target.y = stationsXY[destinationStations[i]][1];
    return target;

}
*/

struct Coords findNearestDestination(struct Coords * destinationPtr, struct Coords currentLocation, int numberOfDestinations){
    struct Coords nearestDestination;
    int i, steps;
    int leastSteps = 999;
    for(i = 0; i < numberOfDestinations; i++){
        steps = algorithm(currentLocation, destinationPtr[i]);
        if(steps < leastSteps) {
            leastSteps = steps;
            nearestDestination = destinationPtr[i];
        }
    }

    return nearestDestination;
}

int main(){

    struct Coords target;
    struct Coords currentLocation;
    struct Coords *destinationPtr;
    int startX, startY, finishY, finishX, startStation, finishStation, steps;

     //First element empty to match index
     //x, y coords per station
    int stations[13][2] = {{0,0},
    {2,8}, {4,8}, {6,8}, {8,6}, {8,4}, {8,2}, {6,0}, {4,0}, {2,0}, {0,2}, {0,4}, {0,6}};
    int destinationStations[] = {10,11,1};
    int numDestinations = sizeof(destinationStations)/sizeof(destinationStations[0]); 
    int * stationsPtr = stations;
    int * destinationStationsPtr = destinationStations;
    destinationPtr = stationToCoords(destinationStationsPtr, stationsPtr, numDestinations);
    

    //initialises the startstation
    startStation = 1;
    char startDirection = 'n';
    currentLocation.x = stations[startStation][0];
    currentLocation.x = stations[startStation][1];

    
    
    
    char directionList[99];
    char *directionPtr = directionList;
    char currentDirection = startDirection;


    //struct Coords * destinationCoords = stationToCoords(destinationStations, stations);
    //target = findNearestStation(stations, destinationStations, currentLocation);
    target = findNearestDestination(destinationPtr, currentLocation, numDestinations);
    //target = findNearestDestination(destinationCoords);
    steps = algorithm(currentLocation, target);
    traceBack(startY, startX, directionPtr, currentDirection);
    
    return 0;
}