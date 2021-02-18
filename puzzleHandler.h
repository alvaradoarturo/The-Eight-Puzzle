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

enum puzzleOperators {moveLeft, moveRight, moveUp, moveDown};


struct movablePiece {
    int row;
    int column;
};

class puzzle {
    private:
        movablePiece blankSquare;
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
        void printBlankPosition();
        void generalSearh(puzzle* problem,  queue<puzzle*> puzzleHeap); 
        void misplacedTile(puzzle* problem);   
        void manhattanDistance(puzzle* problem);
        bool puzzleEquality(int arr[3][3], int goal[3][3]);
        int calculateMisplacedTile(puzzle* currentPuzzle);
        int calculateManhattanDistance(puzzle* currentPuzzle);
        int heuristicVal = 0;
        int puzzleBoard[3][3];
        int goalState[3][3];
        int depthLevel = 0;
        int estCheapestSol = 0;
        puzzle* repeatedStates[0];
        int repeatedSize = 0;
        bool repeatedState(puzzle*);
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
void puzzle::printBlankPosition(){
    cout << "Row: " << blankSquare.row  << endl;
    cout << "Col: " << blankSquare.column << endl;
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

void puzzle::generalSearh(puzzle* problem, queue<puzzle*> puzzleHeap){
    auto start = high_resolution_clock::now(); 
    puzzleHeap.push(problem);
    bool finishedProblem = false;
    int nodesExpanded = 0;
    int depthReached = 0;
    puzzle *topNode;
    do {
        if(puzzleHeap.empty()){
            cout << "NO SOLUTION" << endl;
            break;
        }
        // cout << "Next solution" << endl;
        topNode = puzzleHeap.front();
        puzzleHeap.pop();
        // topNode->printPuzzle();
        if(problem->puzzleEquality(problem->goalState, topNode->puzzleBoard )){
            finishedProblem = true;
            cout << "Solution Found" << endl;
            break;
        }
        // Expands up operation
        int* upArray;
        upArray = topNode->blankUp(*topNode);
        if(upArray != NULL){
            puzzle *upPuzzle = new puzzle(upArray);
            nodesExpanded++;
            upPuzzle->depthLevel = topNode->depthLevel + 1;
            puzzleHeap.push(upPuzzle);
        }
        // Expands down operation
        int* downArray;
        downArray = topNode->blankDown(*topNode);
        if(downArray != NULL){
            puzzle *downPuzzle = new puzzle(downArray);
            nodesExpanded++;
            downPuzzle->depthLevel = topNode->depthLevel + 1;
            puzzleHeap.push(downPuzzle);
        }
        // Expands Right puzzle
        int* rightArray;
        rightArray = topNode->blankRight(*topNode);
        if(rightArray != NULL){
            puzzle *rightPuzzle = new puzzle(rightArray);
            nodesExpanded++;
            rightPuzzle->depthLevel = topNode->depthLevel + 1;
            puzzleHeap.push(rightPuzzle);
        }

        // Expands Left Puzzle
        int* leftArray;
        leftArray = topNode->blankLeft(*topNode);
        if(leftArray != NULL){
            puzzle *leftPuzzle = new puzzle(leftArray);
            nodesExpanded++;
            leftPuzzle->depthLevel = topNode->depthLevel + 1;
            puzzleHeap.push(leftPuzzle);
        }
        
    }while(1);
    cout << "To solve this problem the search algorithm expanded a total of " << nodesExpanded << " nodes." << endl;
    cout << "The depth of the goal node was: " << topNode->depthLevel << "."<<  endl;
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 
    cout << "Milliseconds: " << duration.count() << endl; 
}

void puzzle::misplacedTile(puzzle* problem){
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
       // cout << "Next solution" << endl;
        topNode = priorityHeap.front();

       priorityHeap.erase(priorityHeap.begin());
       nodesExpanded++;
        if(problem->puzzleEquality(problem->goalState, topNode->puzzleBoard )){
            cout << "Solution Found" << endl;
            break;
        }
        // Expands up operation
        int* upArray;
        upArray = topNode->blankUp(*topNode);
        if(upArray != NULL){
            upPuzzle = new puzzle(upArray);
            upPuzzle->depthLevel = topNode->depthLevel + 1;
            upPuzzle->heuristicVal = upPuzzle->calculateMisplacedTile(upPuzzle) ;
            upPuzzle->estCheapestSol = upPuzzle->heuristicVal + upPuzzle->depthLevel;
           // if(upPuzzle->repeatedState(upPuzzle) == false){
               priorityHeap.push_back(upPuzzle);
           // }
        }
        // Expands down operation
        int* downArray;
        downArray = topNode->blankDown(*topNode);
        if(downArray != NULL){
            downPuzzle = new puzzle(downArray);
            downPuzzle->depthLevel = topNode->depthLevel + 1;
            downPuzzle->heuristicVal = downPuzzle->calculateMisplacedTile(downPuzzle)  ;
            downPuzzle->estCheapestSol = downPuzzle->heuristicVal + downPuzzle->depthLevel;
        //    if(downPuzzle->repeatedState(downPuzzle) == false){
               priorityHeap.push_back(downPuzzle);
        //    }
        }
        // Expands Right puzzle
        int* rightArray;
        rightArray = topNode->blankRight(*topNode);
        if(rightArray != NULL){
            rightPuzzle = new puzzle(rightArray);
            rightPuzzle->depthLevel = topNode->depthLevel + 1;
            rightPuzzle->heuristicVal = rightPuzzle->calculateMisplacedTile(rightPuzzle) ;
            rightPuzzle->estCheapestSol = rightPuzzle->heuristicVal + rightPuzzle->depthLevel;
          //  if(rightPuzzle->repeatedState(rightPuzzle) == false){
                priorityHeap.push_back(rightPuzzle);
            //}
        }

        // Expands Left Puzzle
        int* leftArray;
        leftArray = topNode->blankLeft(*topNode);
        if(leftArray != NULL){
            leftPuzzle = new puzzle(leftArray);
            leftPuzzle->depthLevel = topNode->depthLevel + 1;
            leftPuzzle->heuristicVal = leftPuzzle->calculateMisplacedTile(leftPuzzle);
            leftPuzzle->estCheapestSol = leftPuzzle->heuristicVal + leftPuzzle->depthLevel;
           // if(leftPuzzle->repeatedState(leftPuzzle) == false){
               priorityHeap.push_back(leftPuzzle);
           // }
        }
        sortHeap();
    }while(1);
    cout << "To solve this problem the search algorithm expanded a total of " << nodesExpanded << " nodes." << endl;
    cout << "The depth of the goal node was: " << topNode->depthLevel << "."<<  endl;
    cout << "Number of nodes inside queue at the time of completion: " << priorityHeap.size() << "." << endl;
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 
    cout << duration.count() << endl; 
}

void puzzle::manhattanDistance(puzzle* problem){
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
       // cout << "Next solution" << endl;
        topNode = priorityHeap.front();

       priorityHeap.erase(priorityHeap.begin());
       nodesExpanded++;
        if(problem->puzzleEquality(problem->goalState, topNode->puzzleBoard )){
            cout << "Solution Found" << endl;
            break;
        }
        // Expands up operation
        int* upArray;
        upArray = topNode->blankUp(*topNode);
        if(upArray != NULL){
            upPuzzle = new puzzle(upArray);
            upPuzzle->depthLevel = topNode->depthLevel + 1;
            upPuzzle->heuristicVal = upPuzzle->calculateManhattanDistance(upPuzzle) ;
            upPuzzle->estCheapestSol = upPuzzle->heuristicVal + upPuzzle->depthLevel;
           // if(upPuzzle->repeatedState(upPuzzle) == false){
               priorityHeap.push_back(upPuzzle);
           // }
        }
        // Expands down operation
        int* downArray;
        downArray = topNode->blankDown(*topNode);
        if(downArray != NULL){
            downPuzzle = new puzzle(downArray);
            downPuzzle->depthLevel = topNode->depthLevel + 1;
            downPuzzle->heuristicVal = downPuzzle->calculateManhattanDistance(downPuzzle)  ;
            downPuzzle->estCheapestSol = downPuzzle->heuristicVal + downPuzzle->depthLevel;
        //    if(downPuzzle->repeatedState(downPuzzle) == false){
               priorityHeap.push_back(downPuzzle);
        //    }
        }
        // Expands Right puzzle
        int* rightArray;
        rightArray = topNode->blankRight(*topNode);
        if(rightArray != NULL){
            rightPuzzle = new puzzle(rightArray);
            rightPuzzle->depthLevel = topNode->depthLevel + 1;
            rightPuzzle->heuristicVal = rightPuzzle->calculateManhattanDistance(rightPuzzle) ;
            rightPuzzle->estCheapestSol = rightPuzzle->heuristicVal + rightPuzzle->depthLevel;
          //  if(rightPuzzle->repeatedState(rightPuzzle) == false){
                priorityHeap.push_back(rightPuzzle);
            //}
        }

        // Expands Left Puzzle
        int* leftArray;
        leftArray = topNode->blankLeft(*topNode);
        if(leftArray != NULL){
            leftPuzzle = new puzzle(leftArray);
            leftPuzzle->depthLevel = topNode->depthLevel + 1;
            leftPuzzle->heuristicVal = leftPuzzle->calculateManhattanDistance(leftPuzzle);
            leftPuzzle->estCheapestSol = leftPuzzle->heuristicVal + leftPuzzle->depthLevel;
           // if(leftPuzzle->repeatedState(leftPuzzle) == false){
               priorityHeap.push_back(leftPuzzle);
           // }
        }
        sortHeap();
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
                    hueristicVal += abs(row - i);
                    hueristicVal += abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 2){
                    int row = 0;
                    int col = 1;
                    hueristicVal += abs(row - i);
                    hueristicVal += abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 3){
                    int row = 0;
                    int col = 2;
                    hueristicVal += abs(row - i);
                    hueristicVal += abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 4){
                    int row = 1;
                    int col = 0;
                    hueristicVal += abs(row - i);
                    hueristicVal += abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 5){
                    int row = 1;
                    int col = 1;
                    hueristicVal += abs(row - i);
                    hueristicVal += abs(col - j);
                }  
                else if(currentPuzzle->puzzleBoard[i][j] == 6){
                    int row = 1;
                    int col = 2;
                    hueristicVal += abs(row - i);
                    hueristicVal += abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 7){
                    int row = 2;
                    int col = 0;
                    hueristicVal += abs(row - i);
                    hueristicVal += abs(col - j);
                }
                else if(currentPuzzle->puzzleBoard[i][j] == 8){
                    int row = 2;
                    int col = 1;
                    hueristicVal += abs(row - i);
                    hueristicVal += abs(col - j);
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
    for(k = 0; k < repeatedSize ; k++ ){
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(topPuzzle->puzzleBoard[i][j] == repeatedStates[k]->puzzleBoard[i][j]){
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
    repeatedStates[repeatedSize] = topPuzzle;
    repeatedSize++;
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