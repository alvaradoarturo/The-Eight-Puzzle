#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <queue>
#include "utilityFunctions.h"
#include "puzzleHandler.h"
#include "ucSearch.h"
using namespace std;



int main(int argc, char** argv)
{
    queue<puzzle*> puzzleHeap;
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
    // Check to see original state of puzzle
    cout << "This is our starting puzzle" << endl;
    userPuzzle->printPuzzle();
    userPuzzle->printBlankPosition();
    
    // Call the gerenal search algorithm for Uniform Cost
    cout << "Calling UC Search" << endl;
    generalSearh(userPuzzle, puzzleHeap);
        
    return 0;
}