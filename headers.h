#ifndef HEADER_FILE
#define HEADER_FILE

struct Coords{
    int x;
    int y;
};

struct Commands{
    char command;
    struct Commands * next;
};

//                           9      8      7
int matrix[9][9] =  {{0,  0, 0,  0, 0,  0, 0,  0,  0},
                    { 0, -1, 0, -1, 0, -1, 0, -1,  0},
/*              10*/{ 0,  0, 0,  0, 0,  0, 0,  0,  0},/*6*/
                    { 0, -1, 0, -1, 0, -1, 0, -1,  0},
/*              11*/{ 0,  0, 0,  0, 0,  0, 0,  0,  0},/*5*/
                    { 0, -1, 0, -1, 0, -1, 0, -1,  0},
/*              12*/{ 0,  0, 0,  0, 0,  0, 0,  0,  0},/*4*/
                    { 0, -1, 0, -1, 0, -1, 0, -1,  0},
                    { 0,  0, 0,  0, 0,  0, 0,  0,  0}};
//                           1      2      3
short dimensions = 9;
#endif