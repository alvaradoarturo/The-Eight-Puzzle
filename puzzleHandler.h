#ifndef PUZZLEHANDLER_H
#define PUZZLEHANDLER_H

using namespace std;

enum puzzleOperators {moveLeft, moveRight, moveUp, moveDown};

class puzzle {
    private:
        int puzzleBoard[3][3];
        int depthReached;
        int nodesExpanded;
        int goalState[3][3];
    public:
        puzzle();
        puzzle(int arr[]);
        void generateGoalState();
        void defaultPuzzle();
        void moveEmptyPiece(enum puzzleOperators){
            ;
        }
        void generatePuzzle(int arr[]);
        void printPuzzle();
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

#endif