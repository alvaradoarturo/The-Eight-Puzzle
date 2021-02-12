#ifndef PUZZLEHANDLER_H
#define PUZZLEHANDLER_H

#define col_max 2
#define row_max 2

using namespace std;

enum puzzleOperators {moveLeft, moveRight, moveUp, moveDown};

struct movablePiece {
    int row;
    int column;
};

class puzzle {
    private:
        movablePiece blankSquare;
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
        void generalSearh(puzzle* problem,  priority_queue<puzzle*> puzzleHeap);    
        int puzzleBoard[3][3];
        int goalState[3][3];
        bool puzzleEquality(int arr[3][3], int goal[3][3]);
        int depthLevel = 0;

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

void generalSearh(puzzle* problem, queue<puzzle*> puzzleHeap){
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
        cout << "Next solution" << endl;
        topNode = puzzleHeap.front();
        puzzleHeap.pop();
        topNode->printPuzzle();
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

}



#endif