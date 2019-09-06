/*
>- Author: Max Wong
>- Date: Sep 4, 2019
>- Updated: Sep 5, 2019
>- Purpose: To write a tic tac toe game and learn the basics to design in ASCII
>-
>- [version 0.0.1]
>- Thanks to Vedaant Srivastava for the error trapping system and play-testing
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>-
>- [TO DO]
>- commenting
>- Find Errors
    >- loop reset
    >- AI vs Partner
>-
*/

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <dos.h> //for delay
#include <windows.h>

using namespace std;

bool stringChecker(string); //This function checks if an input in a string can be coverted into an integer
bool checkWin(char [][3]); //This function checks for a winner

int main()
{
    string inputCommand; //This string is used to get the players input
    char gameBoard [3][3]; //This is the array that saves the board
    int playerInputX; //This gets the x position the player wants to place a piece
    int playerInputY; //This is the y position the player wants to place a piece

    bool gamePlaying = true; //This determines if the player still wants to play the game
    bool matchPlaying = false; //This determines if the player is in a match
    bool playerOneTurn = true; //This determines who's turn it is
    bool choosingSpot = false; //This determines if the player is playing
    bool playingWithAI = false; //Determines if you are playing alone or with a partner

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
        cout << ">- type /q to quit" << endl;
        if(!playingWithAI) cin >> inputCommand;
        if(playingWithAI) inputCommand = "/p";

        if(inputCommand == "/q")
        {
            gamePlaying = false;
        }
        if(inputCommand == "/a")
        {
            playingWithAI = true;
            system("CLS");
        }
        if(inputCommand == "/p")
        {
            matchPlaying = true;

            while(matchPlaying)
            {
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
                            playerInputY = ::atof(inputCommand.c_str());

                            cout << ">- Please select a number to choose your row" << endl;
                            cout << "[1]" << endl << "[2]" << endl << "[3]" << endl;
                            cin >> inputCommand;

                            if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                            {
                                playerInputX = ::atof(inputCommand.c_str());

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

                        if(!playingWithAI)
                        {
                            cout << ">- Please select a number to choose your column" << endl;
                            cout << "[1] [2] [3]" << endl;
                            cin >> inputCommand;

                            if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                            {
                                playerInputY = ::atof(inputCommand.c_str());

                                cout << ">- Please select a number to choose your row" << endl;
                                cout << "[1]" << endl << "[2]" << endl << "[3]" << endl;
                                cin >> inputCommand;

                                if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                                {
                                    playerInputX = ::atof(inputCommand.c_str());

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
                        else
                        {
                            Sleep( 100 );

                            playerInputX = rand() % 2;
                            playerInputY = rand() % 2;
                            if(gameBoard[playerInputX][playerInputY] == ' ')
                            {
                                gameBoard[playerInputX][playerInputY] = 'O';
                                choosingSpot = false;
                                playerOneTurn = true;
                            }
                        }

                    }
                }

                if(checkWin(gameBoard))
                {
                    cout << ">- Press any key to return to menu" << endl;
                    getch();
                    matchPlaying = false;
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

    if((gameBoard[0][0] == 'X' && gameBoard[0][1] == 'X' && gameBoard[0][2] == 'X'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[1][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[1][2] == 'X'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[2][0] == 'X' && gameBoard[2][1] == 'X' && gameBoard[2][2] == 'X'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][0] == 'X' && gameBoard[1][0] == 'X' && gameBoard[2][0] == 'X'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][1] == 'X' && gameBoard[1][1] == 'X' && gameBoard[2][1] == 'X'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][2] == 'X' && gameBoard[1][2] == 'X' && gameBoard[2][2] == 'X'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][0] == 'X' && gameBoard[1][1] == 'X' && gameBoard[2][2] == 'X'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][2] == 'X' && gameBoard[1][1] == 'X' && gameBoard[2][0] == 'X'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    /////////////////////////////////////////////////////////////
     if((gameBoard[0][0] == 'O' && gameBoard[0][1] == 'O' && gameBoard[0][2] == 'O'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[1][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[1][2] == 'O'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[2][0] == 'O' && gameBoard[2][1] == 'O' && gameBoard[2][2] == 'O'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][0] == 'O' && gameBoard[1][0] == 'O' && gameBoard[2][0] == 'O'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][1] == 'O' && gameBoard[1][1] == 'O' && gameBoard[2][1] == 'O'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][2] == 'O' && gameBoard[1][2] == 'O' && gameBoard[2][2] == 'O'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][0] == 'O' && gameBoard[1][1] == 'O' && gameBoard[2][2] == 'O'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    if((gameBoard[0][2] == 'O' && gameBoard[1][1] == 'O' && gameBoard[2][0] == 'O'))
    {
        cout << "Yay! Player X wins" << endl;
        return true;
    }
    else if(gameBoard[0][0] != ' ' && gameBoard[0][1] != ' ' && gameBoard[0][2] != ' ' && gameBoard[1][0] != ' ' && gameBoard[1][1] != ' ' && gameBoard[1][2] != ' ' && gameBoard[2][0] != ' ' && gameBoard[2][1] != ' ' && gameBoard[2][2] != ' ')
    {
        cout << "Sorry, its a tie!" << endl;
    return true;
    }
    else
    {
        return false;
    }
}
