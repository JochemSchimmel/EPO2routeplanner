#include <stdio.h>

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

void printMaze(int matrix[13][13], short n){
    int i, j;
    for (i = 0; i < n; i++){
        for( j = 0; j < n; j++){

            printf(" %02d", matrix[i][j]);
        }
        printf("\n");
    }
}

void addValueToNeighbours(int matrix[13][13], short n, int x, int y, int i){
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

void printCrossing(int y, int x){
    if((x % 2 == 0) && (y % 2 == 0)){
        if((x >=2 && y >= 2)&&(x<= 10 && y <= 10)) printf("c%d%d\n", (y-2)/2, (x-2)/2);
    } 
}


void checkfori(int matrix[13][13], short n, int i){
    int y, x;
    
    for (y = 0; y < n; y++){
        for( x = 0; x < n; x++){
            if(matrix[y][x] == i){
                int (*matrixPtr)[13];
                matrixPtr = matrix;
                addValueToNeighbours(matrixPtr, n, x, y, i);
            }
            
        }
        
    }
    
}



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


int main()

{//                                      9      8      7
    int maze[13][13] = {{-1, -1, -1, -1, 0, -1, 0, -1, 0, -1, -1, -1, -1},
                        {-1, -1, -1, -1, 0, -1, 0, -1, 0, -1, -1, -1, -1},
                        {-1, -1,  0,  0, 0,  0, 0,  0, 0,  0,  0, -1, -1},
                        {-1, -1,  0, -1, 0, -1, 0, -1, 0, -1,  0, -1, -1},
    /*              10*/{ 0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0,  0,  0},/*6*/
                        {-1, -1,  0, -1, 0, -1, 0, -1, 0, -1,  0, -1, -1},
    /*              11*/{ 0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0,  0,  0},/*5*/
                        {-1, -1,  0, -1, 0, -1, 0, -1, 0, -1,  0, -1, -1},
    /*              12*/{ 0,  0,  0,  0, 0,  0, 0,  0, 0,  0,  0,  0,  0},/*4*/
                        {-1, -1,  0, -1, 0, -1, 0, -1, 0, -1,  0, -1, -1},
                        {-1, -1,  0,  0, 0,  0, 0,  0, 0,  0,  0, -1, -1},
                        {-1, -1, -1, -1, 0, -1, 0, -1, 0, -1, -1, -1, -1},
                        {-1, -1, -1, -1, 0, -1, 0, -1, 0, -1, -1, -1, -1}};
    //                                   1      2      3
    int stations[13][2] = { //First element empty to match index
                {0,0},
                {12,4}, {12,6},{12,8},
                {8,12}, {6,12},{4,12}, 
                {0,8},  {0,6},{0,4}, 
                {4,0},  {6,0},{8,0} 
                };


    int startX, startY, finishY, finishX, startStation, finishStation;
    
    short dimensions = 13;
    int (*mazePtr)[13];
    int (*stationPtr) = getInput(mazePtr);
    startStation = stationPtr[0];
    finishStation = stationPtr[1];
    printf("%d %d\n", startStation, finishStation);
    mazePtr = maze;
    //give startstation value i = 1
    startY = stations[startStation][0];
    startX = stations[startStation][1];
    finishY = stations[finishStation][0];
    finishX = stations[finishStation][1];
    
    maze[finishY][finishX] = 1;
    int i = 1;
    
    while(maze[startY][startX] < 1){
        checkfori(mazePtr, dimensions, i);
        printMaze(mazePtr, dimensions);
        printf("\n");
        i++;
        
    }    
    traceBack(startY, startX, mazePtr, dimensions);
    
    return 0;
}