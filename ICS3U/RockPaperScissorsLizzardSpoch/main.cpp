#include <iostream>

using namespace std;

bool didPlayerWin(int, int, int[]);

int main()
{
    int decisionCombinations[10] = {5,1,2,4,3,5,2,4,3,1};
    int playerOneChoice;
    int playerTwoChoice;

    while(true)
    {
        cout << ">- [1] Rock" << endl << ">- [2] Paper" << endl << ">- [3] Scissors" << endl << ">- [4] Lizzard" << endl << ">- [5] Spock" << endl << endl;

        cout << ">- [Player 1] Please pick a number to choose your choice" << endl;
        cin >> playerOneChoice;

        playerTwoChoice = rand()%5+1;
        cout << "AI: " << playerTwoChoice << endl;

        if(playerOneChoice == playerTwoChoice)
        {
            cout << " Tie" << endl;
        }
        else if(didPlayerWin(playerOneChoice, playerTwoChoice, decisionCombinations))
        {
            cout << " Player One won" << endl;
        }
        else if(didPlayerWin(playerTwoChoice, playerOneChoice, decisionCombinations))
        {
            cout << " Player Two won" << endl;
        }

        system("PAUSE");
        system("CLS");
    }
    return 0;
}

bool didPlayerWin(int inputOne, int inputTwo, int decisionCombinations[])
{
    if(inputOne == 1 && inputTwo == 2 || inputOne == 1 && inputTwo == 5)
    {
        return false;
    }
    else if(decisionCombinations[inputOne-1] == decisionCombinations[inputTwo-1]+1 || decisionCombinations[inputOne+4] == decisionCombinations[inputTwo+4]+1 )
    {
        return true;
    }
    else
    {
        return true;
    }
}
