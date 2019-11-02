/*
>- Author: Max Wong
>- Date: Nov 1, 2019
>- Updated: Nov 1, 2019
>- Purpose: To create rock paper scissors lizard spock
*/

#include <iostream>

using namespace std;

bool didPlayerWin(int, int);

int main()
{
    int playerOneChoice;
    int playerTwoChoice;

    while(playerOneChoice != 9)
    {
        cout << ">- [1] Rock" << endl << ">- [2] Paper" << endl << ">- [3] Scissors" << endl << ">- [4] Lizzard" << endl << ">- [5] Spock" << endl << endl;

        cout << ">- [Player 1] Please pick a number to choose your choice" << endl;
        cin >> playerOneChoice;

        playerTwoChoice = rand()%5;
        cout << "AI: " << playerTwoChoice+1 << endl;

        if(playerOneChoice-1 == playerTwoChoice)
        {
            cout << " Tie" << endl;
        }
        else if(didPlayerWin(playerOneChoice-1, playerTwoChoice))
        {
            cout << " Player One won" << endl;
        }
        else
        {
            cout << " Player Two won" << endl;
        }

        cout << " Press 9 to quit" << endl;
        system("PAUSE");
        system("CLS");
    }
    return 0;
}

bool didPlayerWin(int inputOne, int inputTwo)
{
    if(inputTwo == (inputOne + 2)%5 || inputTwo == (inputOne + 3)%5)
    {
        return true;
    }
    /*
    else if(inputTwo == (inputOne + 1)%5 || inputTwo == (inputOne + 4)%5)
    {
        return false;
    }
    */
    return false;
}
