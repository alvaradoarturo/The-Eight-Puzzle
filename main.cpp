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
        // userPuzzle = new puzzle();
        int puzzleElement;
        int puzzleArray[9];
        for(int i = 0 ; i < 9 ; ++i){
            cin >> puzzleElement;
            puzzleArray[i] = puzzleElement;
        }
        userPuzzle = new puzzle(puzzleArray);
    }
    userPuzzle->printPuzzle();
    userPuzzle->printBlankPosition();
    
    return 0;
}