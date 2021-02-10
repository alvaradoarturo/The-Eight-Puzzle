#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include "puzzleHandler.h"
// Create a function that outputs starting menu
using namespace std;


int startingMenu(){
    
    int userInput;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle" << endl;
    cin >> userInput;
    
    if(userInput == 1 ) {
        return userInput;
    }

    if(userInput == 2){
        return userInput;
    }

    else{
        cout << "Invalid Input" << endl;
        startingMenu();
    }
    return userInput;
}


#endif