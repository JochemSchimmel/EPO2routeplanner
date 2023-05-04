#include <stdio.h>

void printMaze(int matrix[13][13], short n){
    int i, j;
    for (i = 0; i < n; i++){
        for( j = 0; j < n; j++){

            printf(" %02d", matrix[i][j]);
        }
        printf("\n");
    }
}

void checkNeighbours(int matrix[13][13], short n, int x, int y, int i){
    if(y + 1 < n){
        if(matrix[y + 1][x] == 0){
            matrix[y + 1][x] = i + 1;
        }
    }
    if(y - 1 > 0){
        if(matrix[y - 1][x] == 0){
            matrix[y - 1][x] = i + 1;
        }
    }
    if(x + 1 < n){
        if(matrix[y][x + 1] == 0){
            matrix[y][x + 1] = i + 1;
        }
    }
    if(x - 1 > 0){
        if(matrix[y][x - 1] == 0){
            matrix[y][x - 1] = i + 1;
        }
    }
}


void checkfori(int matrix[13][13], short n, int i){
    int y, x;
    int (*matrixPtr)[13];
    printMaze(matrixPtr, n);
    printf("i = %d\n", i);
    for (y = 0; y < n; y++){
        for( x = 0; x < n; x++){
            if(matrix[y][x] = i){
                
                matrixPtr = matrix;
                checkNeighbours(matrixPtr, n, x, y, i);
            }
            
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
    int startX, startY, finishY, finishX;
    
    short dimensions = 13;
    int startStation = 3;
    int finishStation = 11;
    int (*mazePtr)[13];
    int stations[12][2] = {
                {12,4}, {12,6},{12,8},
                {8,12}, {6,12},{4,12}, 
                {0,8},  {0,6},{0,4}, 
                {4,0},  {6,0},{8,0} 
                };
    mazePtr = maze;
    //give startstation value i = 1
    startY = stations[startStation - 1][0];
    startX = stations[startStation - 1][1];
    finishY = stations[finishStation - 1][0];
    finishX = stations[finishStation - 1][1];
    
    maze[finishY][finishX] = 1;
    int i = 1;
    
    //while(maze[startY][startX] < 1){
    int a;
    for(a = 0; a < 4; a++){

    
        checkfori(mazePtr, dimensions, i);
        
        i++;
        
    }    
    //}

    
    return 0;
}