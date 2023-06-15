#include <stdio.h>
#include "communication.h"

int main(){
    int a;
    char commands[] = {0x84, 0x84, 0x84};
    int numCommands = sizeof(commands)/sizeof(char); 
    a = runCar(numCommands, commands);
    return 0;
}