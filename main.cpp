#include <iostream>
#include <cstdio>
#include <unistd.h>
#include "utilityFunctions.h"
#include "puzzleHandler.h"
using namespace std;


int main(int argc, char** argv)
{
    puzzle *userPuzzle;
    int option = startingMenu();
    if(option == 1){
        userPuzzle = new puzzle();
    }
    else{
        userPuzzle = new puzzle();
    }
    userPuzzle->printPuzzle();
    





    return 0;
}