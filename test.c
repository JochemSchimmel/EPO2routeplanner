#include <stdio.h>

void printMatrix(int matrix[4][4], short int n){
    int i, j;
    for (i = 0; i < n; i++){
        for( j = 0; j < n; j++){

            printf(" %02d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("%d", matrix[3][1]);

}


int main(){
    short int arrDimension = 4;
    int maze[4][4] = {{10, 11, 12, 13},{20, 21, 22, 23},{30, 31, 32, 33},{3,4,3,9}};
    int (*mazePtr)[4];
    mazePtr = maze; //points to first element of matrix
    //buildMatrix(mazePtr);
    printMatrix(mazePtr, arrDimension);
    //initialiseMatrix();
    return 0;
}