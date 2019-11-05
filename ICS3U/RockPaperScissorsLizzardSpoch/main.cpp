/*
>- Author: Max Wong
>- Date: Nov 1, 2019
>- Updated: Nov 1, 2019
>- Purpose: To create rock paper scissors lizard spock
*/

#include <iostream>
//For error trapping
#include<limits>
#include <windows.h>   // WinApi header

using namespace std;

void didPlayerWin(int, int);
float getAnswer(); //Function used to get the players response as an integer (with error trapping)

int main()
{
    int playerOneChoice;
    int playerTwoChoice;

    while(playerOneChoice <= 5)
    {
        cout << ">- [1] Rock" << endl << ">- [2] Paper" << endl << ">- [3] Scissors" << endl << ">- [4] Lizzard" << endl << ">- [5] Spock" << endl << endl;

        cout << ">- [Player 1] Please pick a number to choose your choice" << endl << ">- Type 9 to quit" << endl;
        playerOneChoice = getAnswer();

        playerTwoChoice = rand()%5;
        cout << ">- AI: " << playerTwoChoice+1 << endl;

        didPlayerWin(playerOneChoice-1, playerTwoChoice)

        system("PAUSE");
        system("CLS");
    }
    return 0;
}

void didPlayerWin(int inputOne, int inputTwo)
{
    if(inputOne == inputTwo)
    {
        cout << " Tie" << endl;
    }
    else if(inputTwo == (inputOne + 2)%5 || inputTwo == (inputOne + 3)%5)
    {
        cout << " Player One won" << endl;
    }
    else
    {
        cout << " Player Two won" << endl;
    }
    return;
}

//Get player input. Check to see if there is an error
float getAnswer ()
{
    float playerInput; //This variable is used to get the player's input
    bool findingInput; //This bool determines if the loop continues running

    do
    {
        findingInput = false; //By default, the loop will end

        cout << ">- Your input: "; //Get player input
        cin >> playerInput;

        if(cin.fail())//Check to see if player entered a "bad" input type
        {
            cin.clear(); //Clear all flags
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore incorrect symbols
            cout << endl << ">- [Error], please enter a number value!" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}
