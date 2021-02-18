#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <queue>
#include <list>
#include <bits/stdc++.h>
#include "utilityFunctions.h"
#include "puzzleHandler.h"
#include "ucSearch.h"

using namespace std;


int main(int argc, char** argv)
{
    queue<puzzle*> puzzleHeap;
    //queue<puzzle*> priorityHeap;
    //vector<puzzle*> priorityHeap;

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
    
    cout << "Enter your choice of algorithm:" << endl;
    cout << "   1. Uniform Cost Search" << endl;
    cout << "   2. A* with the Misplaced Tile Heuristic" << endl;
    cout << "   3. A* with the Manhattan Distance Heuristic" << endl;
    cin >> option;

    if(option == 1){
        // Call the gerenal search algorithm for Uniform Cost
        cout << "Calling UC Search" << endl;
        userPuzzle->generalSearh(userPuzzle, puzzleHeap);       
    }
    else if(option == 2){
        // Calling A* with Misplaced Tile
        cout << "A* with Misplaced Tile" << endl;
        userPuzzle->misplacedTile(userPuzzle);
    }
        else if(option == 3){
        // Calling A* with Manhattan Distance 
        cout << "A* with Manhattan Distance" << endl;
        userPuzzle->manhattanDistance(userPuzzle);
    }
    else{
        cout << "Sorry, option selected is not valid" << endl;
    }

        
    return 0;
}