/*
>- Author: Max Wong
>- Date: Sep 4, 2019
>- Updated: Sep 10, 2019
>- Purpose: To write a tic tac toe game and learn the basics to design in ASCII
>-
>- [version 0.0.7]
>- Thanks to Vedaant Srivastava for the error trapping system and play-testing
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [TO DO]
>- Efficiency
>-
*/

//Declaring Libraries
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

//Declaring namspace
using namespace std;

//Declaring functions
bool stringChecker(string); //This function checks if an input in a string can be coverted into an integer
bool checkWin(char [][3], int); //This function checks for a winner
int resetArray(char [][3], int); //This function is used to reset the array
void readArray(char [][3]); //This function is used to print out the array

int main()
{
    //Declaring variables
    string inputCommand; //This string is used to get the players input
    char gameBoard [3][3]; //This is the array that saves the board
    int playerInputX; //This gets the x position the player wants to place a piece
    int playerInputY; //This is the y position the player wants to place a piece
    int aiAttemptCount = 0; //This keeps track of how many times the AI has attempted: for astetics
    int itemsDone = 0;

    bool gamePlaying = true; //This determines if the player still wants to play the game
    bool matchPlaying = false; //This determines if the player is in a match
    bool playerOneTurn = true; //This determines who's turn it is
    bool choosingSpot = false; //This determines if the player is playing
    bool playingWithAI = false; //Determines if you are playing alone or with a partner

    while(gamePlaying)
    {

        //Get player input on AI vs Partner
        cout << ">- Welcome to Tic Tac Toe" << endl;
        cout << ">- Would you like to play alone or with a partner?" << endl;
        cout << ">- type /a for alone or /p for partner" << endl;
        cout << ">- type /q to quit" << endl;
        if(!playingWithAI) cin >> inputCommand;
        if(playingWithAI) inputCommand = "/p";

        //Determine if player is going against AI
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
            //Start match
            matchPlaying = true;
                //reset board + tie counter
                resetArray(gameBoard, itemsDone);

            do{
                readArray(gameBoard);

                //Check for a winner / us function
                if(checkWin(gameBoard, itemsDone))
                {
                    cout << ">- Press any key to return to menu" << endl;
                    getch();
                    matchPlaying = false;
                    playingWithAI = false;
                }

                if(matchPlaying)
                {
                    if(playerOneTurn)
                    {
                        choosingSpot = true;
                        aiAttemptCount = 0;
                        //Get player's input
                        while(choosingSpot){
                            cout << ">- Player X's Turn" << endl;
                            cout << ">- Please select a number to choose your column" << endl;
                            cout << "[1] [2] [3]" << endl;
                            cin >> inputCommand;
                            //Get horizontal input
                            if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                            {
                                playerInputY = ::atof(inputCommand.c_str());
                                //Get vertical input
                                cout << ">- Please select a number to choose your row" << endl;
                                cout << "[1]" << endl << "[2]" << endl << "[3]" << endl;
                                cin >> inputCommand;
                                //Error trapping
                                if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                                {
                                    playerInputX = ::atof(inputCommand.c_str());
                                    //checking to see if area is availabled
                                    if(gameBoard[playerInputX - 1][playerInputY - 1] != 'O' && gameBoard[playerInputX - 1][playerInputY - 1] != 'X' )
                                    {
                                        //If yes, set player spot
                                        itemsDone += 1;
                                        gameBoard[playerInputX - 1][playerInputY - 1] = 'X';
                                        choosingSpot = false;
                                        playerOneTurn = false;
                                    }
                                    else
                                    {
                                        //Otherwise, print error message
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

                            if(!playingWithAI)
                            {
                                //Get player's input
                                //Hrizontal input
                                cout << ">- Player O's Turn" << endl;
                                cout << ">- Please select a number to choose your column" << endl;
                                cout << "[1] [2] [3]" << endl;
                                cin >> inputCommand;

                                //Error trapping
                                if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                                {
                                    playerInputY = ::atof(inputCommand.c_str());
                                    //Vertical input
                                    cout << ">- Please select a number to choose your row" << endl;
                                    cout << "[1]" << endl << "[2]" << endl << "[3]" << endl;
                                    cin >> inputCommand;
                                    //Error trapping
                                    if(stringChecker(inputCommand) && (inputCommand == "1" || inputCommand == "2" || inputCommand == "3"))
                                    {
                                        playerInputX = ::atof(inputCommand.c_str());
                                        //Check if spot is available
                                        if(gameBoard[playerInputX - 1][playerInputY - 1] != 'O' && gameBoard[playerInputX - 1][playerInputY - 1] != 'X' )
                                        {
                                            //If yes, place marker down
                                            itemsDone += 1;
                                            gameBoard[playerInputX - 1][playerInputY - 1] = 'O';
                                            choosingSpot = false;
                                            playerOneTurn = true;

                                        }
                                        else
                                        {
                                            //Otherwise, print error message
                                            cout << ">- That place is already taken" << endl << endl;
                                        }
                                    }
                                }
                            }
                            //Playing with AI
                            else if(playingWithAI)
                            {
                                //Show indication of loading progress
                                cout << ">- AI Calculating..." << endl;
                                aiAttemptCount ++;
                                cout << ">- Attempt #..." << aiAttemptCount << endl;
                                //Delay 100 ms
                                Sleep( 100 );
                                //Choose a random input
                                playerInputX = rand() % 3;
                                playerInputY = rand() % 3;
                                if(gameBoard[playerInputX][playerInputY] == ' ')
                                {
                                    //If random input wokrs, place marker down
                                    itemsDone += 1;
                                    gameBoard[playerInputX][playerInputY] = 'O';
                                    choosingSpot = false;
                                    playerOneTurn = true;
                                }
                            }
                        }
                    }
                }
                system("CLS");

            }while(matchPlaying);
        }
        else
        {
            //Otherwise, print error message
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

bool checkWin( char gameBoard [][3] , int itemsPlaced)
{

    //Check through all possible combinations to find a winner
    for(int i = 0; i < 3; i++)
    {
        if(gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][0] != ' ')
        {
            cout << "Yay! Player " << gameBoard[i][0] << " won!" << endl;
            return true;
        }
        if(gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i] && gameBoard[0][i] != ' ')
        {
            cout << "Yay! Player " << gameBoard[0][i] << " won!" << endl;
            return true;
        }
    }
    //Now find a specific winner
    if(((gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2]) || (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0]))  && gameBoard[1][1] != ' ')
    {
        cout << "Yay! Player " << gameBoard[1][1] << " won!" << endl;
        return true;
    }

    else if(itemsPlaced == 9)
    {
        //If all spots are placed down, tie game
        cout << "Sorry, its a tie!" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

int resetArray(char gameBoard[][3], int itemsDone)
{
    //reset board + tie counter
    for(int i = 0; i < 3; i++ )
    {
        for(int j = 0; j < 3; j++)
        {
            gameBoard[i][j] = ' ';
        }
    }
    itemsDone = 0;
    return itemsDone;
}

void readArray(char gameBoard[][3])
{
    system("CLS");
    //Load gameBoard
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
    return;
}
