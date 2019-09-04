#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <string>
#include <conio.h>

using namespace std;

bool stringChecker(string);
bool checkWin(char [][3]);

int main()
{
    string inputCommand; //This string is used to get the players input
    char gameBoard [3][3]; //This is the array that saves the board
    int playerInputX;
    int playerInputY;

    bool gamePlaying = true;
    bool matchPlaying = false;
    bool playerOneTurn = true;
    bool choosingSpot = false;

    for(int i = 0; i < 3; i++ )
    {
        for(int j = 0; j < 3; j++)
        {
            gameBoard[i][j] = ' ';
        }
    }

    while(gamePlaying)
    {

        cout << ">- Welcome to Tic Tac Toe" << endl;
        cout << ">- Would you like to play alone or with a partner?" << endl;
        cout << ">- type /a for alone or /p for partner" << endl;
        cin >> inputCommand;

        if(inputCommand == "/a")
        {
            system("CLS");
        }
        if(inputCommand == "/p")
        {
            matchPlaying = true;

            while(matchPlaying){
                system("CLS");

                for(int i = 0; i < 3; i++)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        cout << "[" << gameBoard[i][j] << "] ";
                    }
                    cout << endl;
                }
                cout << ">- press any key to continue" << endl;
                getch();
                cout << endl;

                if(playerOneTurn)
                {
                    choosingSpot = true;
                    while(choosingSpot){
                        cout << ">- Player X's Turn" << endl;
                        cout << ">- Please select a number to choose your column" << endl;
                        cout << "[1] [2] [3]" << endl;
                        cin >> inputCommand;

                        if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                        {
                            playerInputX = ::atof(inputCommand.c_str());

                            cout << ">- Please select a number to choose your row" << endl;
                            cout << "[1]" << endl << "[2]" << endl << "[3]" << endl;
                            cin >> inputCommand;

                            if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                            {
                                playerInputY = ::atof(inputCommand.c_str());

                                if(gameBoard[playerInputX - 1][playerInputY - 1] != 'O' && gameBoard[playerInputX - 1][playerInputY - 1] != 'X' )
                                {
                                    gameBoard[playerInputX - 1][playerInputY - 1] = 'X';
                                    choosingSpot = false;
                                    playerOneTurn = false;
                                }
                                else
                                {
                                    cout << ">- That place is already taken" << endl << endl;

                                }
                            }
                        }
                    }
                }
                else
                {
                    choosingSpot = true;
                    while(choosingSpot){
                        cout << ">- Player O's Turn" << endl;
                        cout << ">- Please select a number to choose your column" << endl;
                        cout << "[1] [2] [3]" << endl;
                        cin >> inputCommand;

                        if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                        {
                            playerInputX = ::atof(inputCommand.c_str());

                            cout << ">- Please select a number to choose your row" << endl;
                            cout << "[1]" << endl << "[2]" << endl << "[3]" << endl;
                            cin >> inputCommand;

                            if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                            {
                                playerInputY = ::atof(inputCommand.c_str());

                                if(gameBoard[playerInputX - 1][playerInputY - 1] != 'O' && gameBoard[playerInputX - 1][playerInputY - 1] != 'X' )
                                {
                                    gameBoard[playerInputX - 1][playerInputY - 1] = 'O';
                                    choosingSpot = false;
                                    playerOneTurn = true;

                                }
                                else
                                {
                                    cout << ">- That place is already taken" << endl << endl;
                                }
                            }
                        }
                    }
                }

                if(checkWin(gameBoard))
                {
                    cout << ">- Press any key to return to menu" << endl;
                    getch();
                }

                system("CLS");
            }
        }
        else
        {
            cout << ">- Please input a valid statement" << endl;
        }


    }

    return 0;
}

//Function used to check if input string is a float
//Credit to Vedaant for this function
bool stringChecker(string myString)
{
    long double flMyString;
    ostringstream conversion;

    //Checks the string using built in iostream library
    stringstream(myString) >> flMyString;
    conversion << setprecision(9) << flMyString;

    string convFlMyString = conversion.str();

    //If initial string does not match corrected string, string is not a float
    if (convFlMyString == myString)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkWin( char gameBoard [][3] )
{
    if(gameBoard[0][0] == 'X')
    return false;
}
