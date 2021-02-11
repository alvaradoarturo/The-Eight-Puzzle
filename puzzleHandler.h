#ifndef PUZZLEHANDLER_H
#define PUZZLEHANDLER_H

using namespace std;

enum puzzleOperators {moveLeft, moveRight, moveUp, moveDown};

struct movablePiece {
    int row;
    int column;
};

class puzzle {
    private:
        int depthReached;
        int nodesExpanded;
        int goalState[3][3];
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
        int puzzleBoard[3][3];
};

puzzle::puzzle(){
    cout << "Reached Constructor" << endl;
    defaultPuzzle();
    generateGoalState();
}
puzzle::puzzle(int arr[]){
    cout << "Reached custom constructor" << endl;
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
    cout << "Reached generate puzzle" << endl;
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
    cout << "Reached print puzzle" << endl;
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
    cout << "Row: " << blankSquare.row + 1 << endl;
    cout << "Col: " << blankSquare.column + 1 << endl;
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
                possibleArray[i][j] =  puzzleBoard[i][j] ;
            } 
        }
        int swap = possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column];
        possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column] =  possibleArray[parentNode.blankSquare.row - 1][parentNode.blankSquare.column];
        possibleArray[parentNode.blankSquare.row - 1][parentNode.blankSquare.column] = swap;
    }
    static int returnedArray[9];
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            returnedArray[boardIncrementer] = possibleArray[i][j];
            boardIncrementer++;   
        } 
    }
    return returnedArray;
}
int* puzzle::blankDown(puzzle parentNode){
    int possibleArray[3][3];
    int boardIncrementer = 0;
    if(parentNode.blankSquare.row == 0){
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
    static int returnedArray[9];
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            returnedArray[boardIncrementer] = possibleArray[i][j];
            boardIncrementer++;   
        } 
    }
    return returnedArray;
}
int* puzzle::blankRight(puzzle parentNode){
    int possibleArray[3][3];
    int boardIncrementer = 0;
    if(parentNode.blankSquare.row == 0){
        return NULL;
    }
    else{
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                possibleArray[i][j] =  puzzleBoard[i][j] ;
            } 
        }
        int swap = possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column];
        possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column] =  possibleArray[parentNode.blankSquare.row ][parentNode.blankSquare.column - 1];
        possibleArray[parentNode.blankSquare.row ][parentNode.blankSquare.column - 1] = swap;
    }
    static int returnedArray[9];
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            returnedArray[boardIncrementer] = possibleArray[i][j];
            boardIncrementer++;   
        } 
    }
    return returnedArray;
}
int* puzzle::blankLeft(puzzle parentNode){
    int possibleArray[3][3];
    int boardIncrementer = 0;
    if(parentNode.blankSquare.row == 0){
        return NULL;
    }
    else{
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                possibleArray[i][j] =  puzzleBoard[i][j] ;
            } 
        }
        int swap = possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column];
        possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column] =  possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column + 1];
        possibleArray[parentNode.blankSquare.row][parentNode.blankSquare.column + 1] = swap;
    }
    static int returnedArray[9];
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            returnedArray[boardIncrementer] = possibleArray[i][j];
            boardIncrementer++;   
        } 
    }
    return returnedArray;
}

#endif