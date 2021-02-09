#ifndef UTILITYFUNCTION_H
#define UTILITYFUNCTION_H
// Create a function that outputs starting menu
using namespace std;

void defaultPuzzle();
void customPuzzle();
void startingMenu(){
    int userInput;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle" << endl;
    cin >> userInput;
    if(userInput == 1){
        defaultPuzzle();
    }
    else{
        customPuzzle();
    }
}

void defaultPuzzle(){
    ;
}
void customPuzzle(){
    ;
}

#endif