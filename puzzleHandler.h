#ifndef PUZZLEHANDLER_H
#define PUZZLEHANDLER_H

#include <chrono>
#include <bits/stdc++.h>
#include <list>
#include <vector>

#define col_max 2
#define row_max 2

using namespace std;
using namespace std::chrono; 

struct movablePiece {
    int row;
    int column;
};

class puzzle {
    private:
        movablePiece blankSquare;
        vector<puzzle*> repeatedStates;
        vector<puzzle*> priorityHeap;
    public:
        puzzle();
        puzzle(int arr[]);
        void generateGoalState();
        void defaultPuzzle();
        int* blankUp(puzzle parentNode);
        int* blankDown(puzzle parentNode);
        int* blankLeft(puzzle parentNode);
        int* blankRight(puzzle parentNode);        
        void generatePuzzle(int arr[]);
        void printPuzzle();
        void generalSearch(puzzle* problem, int queuingFunction);  
        bool puzzleEquality(int arr[3][3], int goal[3][3]);
        int calculateMisplacedTile(puzzle* currentPuzzle);
        int calculateManhattanDistance(puzzle* currentPuzzle);
        int heuristicVal = 0;
        int puzzleBoard[3][3];
        int goalState[3][3];
        int depthLevel = 0;
        int estCheapestSol = 0;
        bool repeatedState(puzzle* inQuestion);
        void sortHeap();
};

puzzle::puzzle(){
    defaultPuzzle();
    generateGoalState();
}
puzzle::puzzle(int arr[]){
    generatePuzzle(arr);
    generateGoalState();
}

void puzzle::defaultPuzzle() {
    int defaultBoard[9] = { 1, 2, 3, 4, 8, 0, 7, 6, 5};
    generatePuzzle(defaultBoard);
    blankSquare.row = 1;
    blankSquare.column = 2;
     
}
void puzzle::generateGoalState(){
    int solvedBoard[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    int boardIncrementer = 0;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            goalState[i][j] = solvedBoard[boardIncrementer];
            boardIncrementer++; 
        }
    }         
}
void puzzle::generatePuzzle(int arr[]) {
    int boardIncrementer = 0;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            puzzleBoard[i][j] = arr[boardIncrementer];
            boardIncrementer++; 
            if(puzzleBoard[i][j] == 0)
            {
                blankSquare.row = i;
                blankSquare.column = j;
            }    
       }
    }   
}
void puzzle::printPuzzle(){
    int columnCount = 0;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
           if(columnCount < 2){
               cout << puzzleBoard[i][j] << " " ;
               columnCount++;
           }
           else{
               cout << puzzleBoard[i][j] << " " << endl;
               columnCount = 0;
           }
        }
    }   
}

int* puzzle::blankUp(puzzle parentNode){
    int possibleArray[3][3];
    int boardIncrementer = 0;
    if(parentNode.blankSquare.row == 0){
        return NULL;
    }
    else{
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                possibleArray[i][j] = parentNode.puzzleBoard[i][j] ;
            } 
        }
        int swap = possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column];
        possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column] =  possibleArray[parentNode.blankSquare.row - 1][parentNode.blankSquare.column ];
        possibleArray[parentNode.blankSquare.row - 1][parentNode.blankSquare.column] = swap;
    }
    static int upArray[9];
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            upArray[boardIncrementer] = possibleArray[i][j];
            boardIncrementer++;   
        } 
    }
    return upArray;
}
int* puzzle::blankDown(puzzle parentNode){
    int possibleArray[3][3];
    int boardIncrementer = 0;
    if(parentNode.blankSquare.row == row_max){
        return NULL;
    }
    else{
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                possibleArray[i][j] =  puzzleBoard[i][j] ;
            } 
        }
        int swap = possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column];
        possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column] =  possibleArray[parentNode.blankSquare.row + 1][parentNode.blankSquare.column];
        possibleArray[parentNode.blankSquare.row + 1][parentNode.blankSquare.column] = swap;
    }
    static int downArray[9];
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            downArray[boardIncrementer] = possibleArray[i][j];
            boardIncrementer++;   
        } 
    }
    return downArray;
}
int* puzzle::blankRight(puzzle parentNode){
    int possibleArray[3][3];
    int boardIncrementer = 0;
    if(parentNode.blankSquare.column == 2){
        return NULL;
    }
    else{
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                possibleArray[i][j] =  puzzleBoard[i][j] ;
            } 
        }
        int swap = possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column];
        possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column] =  possibleArray[parentNode.blankSquare.row ][parentNode.blankSquare.column + 1];
        possibleArray[parentNode.blankSquare.row ][parentNode.blankSquare.column + 1 ] = swap;
    }
    static int rightArray[9];
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            rightArray[boardIncrementer] = possibleArray[i][j];
            boardIncrementer++;   
        } 
    }
    return rightArray;
}
int* puzzle::blankLeft(puzzle parentNode){
    int possibleArray[3][3];
    int boardIncrementer = 0;
    if(parentNode.blankSquare.column == 0){
        return NULL;
    }
    else{
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                possibleArray[i][j] =  puzzleBoard[i][j] ;
            } 
        }
        int swap = possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column];
        possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column] =  possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column - 1];
        possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column - 1] = swap;
    }
    static int leftArray[9];
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            leftArray[boardIncrementer] = possibleArray[i][j];
            boardIncrementer++;   
        } 
    }
    return leftArray;
}

bool puzzle::puzzleEquality(int arr[3][3], int goal[3][3]){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(arr[i][j] != goal[i][j]){
                return false;
            }          
        } 
    }
    return true;
}

void puzzle::generalSearch(puzzle* problem, int queuingFunction){
    auto start = high_resolution_clock::now(); 
    priorityHeap.push_back(problem);
    int nodesExpanded = 0;
    int depthReached = 0;
    puzzle *topNode;
    puzzle *upPuzzle;
    puzzle *downPuzzle;
    puzzle *rightPuzzle;
    puzzle *leftPuzzle;
    do {
        if(priorityHeap.empty()){
            cout << "NO SOLUTION" << endl;
            break;
        }
        topNode = priorityHeap.front();
        priorityHeap.erase(priorityHeap.begin());
        // topNode->printPuzzle();
        // cout << "--------------------------" << endl;
        if(problem->puzzleEquality(problem->goalState, topNode->puzzleBoard )){
            cout << "Solution Found" << endl;
            break;
        }
        nodesExpanded++;
        // Expands up operation
        int* upArray;
        upArray = topNode->blankUp(*topNode);
        if(upArray != NULL ){
            upPuzzle = new puzzle(upArray);
            upPuzzle->depthLevel = topNode->depthLevel + 1;
            if(queuingFunction == 1){
                upPuzzle->heuristicVal = 1;
            }
            else if(queuingFunction == 2) {
                upPuzzle->heuristicVal = upPuzzle->calculateMisplacedTile(upPuzzle) ;
            }
            else{
                upPuzzle->heuristicVal = upPuzzle->calculateManhattanDistance(upPuzzle) ;
            }
            upPuzzle->estCheapestSol = upPuzzle->heuristicVal + upPuzzle->depthLevel;
            if(!repeatedState(upPuzzle)){
                priorityHeap.push_back(upPuzzle);
            }
        }
        // Expands down operation
        int* downArray;
        downArray = topNode->blankDown(*topNode);
        if(downArray != NULL){
            downPuzzle = new puzzle(downArray);
            downPuzzle->depthLevel = topNode->depthLevel + 1;
            if(queuingFunction == 1){
                downPuzzle->heuristicVal = 1;
            }
            else if(queuingFunction == 2) {
                downPuzzle->heuristicVal = downPuzzle->calculateMisplacedTile(downPuzzle) ;
            }
            else{
                downPuzzle->heuristicVal = downPuzzle->calculateManhattanDistance(downPuzzle) ;
            }
            downPuzzle->estCheapestSol = downPuzzle->heuristicVal + downPuzzle->depthLevel;
            if(!repeatedState(downPuzzle)){
                priorityHeap.push_back(downPuzzle);
            }
        }
        // Expands Right puzzle
        int* rightArray;
        rightArray = topNode->blankRight(*topNode);
        if(rightArray != NULL){
            rightPuzzle = new puzzle(rightArray);
            rightPuzzle->depthLevel = topNode->depthLevel + 1;
            if(queuingFunction == 1){
                rightPuzzle->heuristicVal = 1;
            }
            else if(queuingFunction == 2) {
                rightPuzzle->heuristicVal = rightPuzzle->calculateMisplacedTile(rightPuzzle) ;
            }
            else{
                rightPuzzle->heuristicVal = rightPuzzle->calculateManhattanDistance(rightPuzzle) ;
            }
            rightPuzzle->estCheapestSol = rightPuzzle->heuristicVal + rightPuzzle->depthLevel;
            if(!repeatedState(rightPuzzle)){
                priorityHeap.push_back(rightPuzzle);
            }
        }
        // Expands Left Puzzle
        int* leftArray;
        leftArray = topNode->blankLeft(*topNode);
        if(leftArray != NULL){
            leftPuzzle = new puzzle(leftArray);
            leftPuzzle->depthLevel = topNode->depthLevel + 1;
            if(queuingFunction == 1){
                leftPuzzle->heuristicVal = 1;
            }
            else if(queuingFunction == 2) {
                leftPuzzle->heuristicVal = leftPuzzle->calculateMisplacedTile(leftPuzzle) ;
            }
            else{
                leftPuzzle->heuristicVal = leftPuzzle->calculateManhattanDistance(leftPuzzle) ;
            }
            leftPuzzle->estCheapestSol = leftPuzzle->heuristicVal + leftPuzzle->depthLevel;
            if(!repeatedState(leftPuzzle)){
                priorityHeap.push_back(leftPuzzle);
            }
        }
        if(queuingFunction == 2 || queuingFunction == 3){
            sortHeap();
        }
    }while(1);
    cout << "To solve this problem the search algorithm expanded a total of " << nodesExpanded << " nodes." << endl;
    cout << "The depth of the goal node was: " << topNode->depthLevel << "."<<  endl;
    cout << "Number of nodes inside queue at the time of completion: " << priorityHeap.size() << "." << endl;
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 
    cout << duration.count() << endl;    
}

int puzzle::calculateMisplacedTile(puzzle* currentPuzzle){
    int misplacedCnt = 0;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(currentPuzzle->puzzleBoard[i][j] != currentPuzzle->goalState[i][j]){
                misplacedCnt++;
            }          
        } 
    }   
    return misplacedCnt;
}
int puzzle::calculateManhattanDistance(puzzle* currentPuzzle){
    int hueristicVal = 0;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(currentPuzzle->puzzleBoard[i][j] != currentPuzzle->goalState[i][j]){
                if(currentPuzzle->puzzleBoard[i][j] == 1){
                    int row = 0;
                    int col = 0;
                    hueristicVal += abs(row - i) + abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 2){
                    int row = 0;
                    int col = 1;
                    hueristicVal += abs(row - i) + abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 3){
                    int row = 0;
                    int col = 2;
                    hueristicVal += abs(row - i) + abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 4){
                    int row = 1;
                    int col = 0;
                    hueristicVal += abs(row - i) + abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 5){
                    int row = 1;
                    int col = 1;
                    hueristicVal += abs(row - i) + abs(col - j);
                }  
                else if(currentPuzzle->puzzleBoard[i][j] == 6){
                    int row = 1;
                    int col = 2;
                    hueristicVal += abs(row - i) + abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 7){
                    int row = 2;
                    int col = 0;
                    hueristicVal += abs(row - i) + abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 8){
                    int row = 2;
                    int col = 1;
                    hueristicVal += abs(row - i) + abs(col - j);
                }
                else{
                    ;
                }                                                                                                              
            }          
        } 
    }   
    return hueristicVal;
}
bool puzzle::repeatedState(puzzle* topPuzzle){
    int k ;
    int equality = 0;
    for(k = 0; k < repeatedStates.size() ; k++ ){
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(topPuzzle->puzzleBoard[i][j] == repeatedStates.at(k)->puzzleBoard[i][j]){
                    equality++;
                }          
            } 
        }
        if(equality == 9) {
            return true;
        }
        else{
            equality = 0;
        }
    }
    repeatedStates.push_back(topPuzzle);
    return false;
}
void puzzle::sortHeap(){
    for(int i = 0 ; i < priorityHeap.size() ; i++){
        for(int j = i + 1 ; j < priorityHeap.size() ; j++){
            if(priorityHeap.at(j)->estCheapestSol < priorityHeap.at(i)->estCheapestSol){
                puzzle* swap = priorityHeap.at(i);
                priorityHeap.at(i) = priorityHeap.at(j);
                priorityHeap.at(j) = swap;
            }
        }
    }
}
#endif