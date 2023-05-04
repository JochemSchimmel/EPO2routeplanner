#include <stdio.h>

void printMatrix(int matrix[4][4]){
    int i, j;
    for (i = 0; i < 13; i++){
        for( j = 0; j < 13; j++){

            printf(" %02d", i,j, matrix[i][j]);
        }
        printf("\n");
    }

}


int main(){
    int (*mazePtr)[4][4];
    int maze[4][4] = {{1,2,3,4},{5,6,7,8},{9,8,7,6},{5,4,3,2}};
    mazePtr = &maze[0][0]; //points to first element of matrix
    //buildMatrix(mazePtr);
    printMatrix(mazePtr);
    //initialiseMatrix();
    return 0;
}