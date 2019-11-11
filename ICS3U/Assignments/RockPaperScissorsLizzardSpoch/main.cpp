/*
>- Author: Max Wong
>- Date: Nov 1, 2019
>- Updated: Nov 6, 2019
>- Purpose: To create rock paper scissors lizard spock
*/

#include <iostream>
//For error trapping
#include<limits>
#include <windows.h>   // WinApi header
//For displaying menu

using namespace std;

void didPlayerWin(int, int); //This function is used to determine if the player wins or looses or ties
float getAnswer(); //Function used to get the players response as an integer (with error trapping)
void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number

int main()
{
    //Define variables
    int playerOneChoice=1; //This int saves the choice chosen by the player
    int playerTwoChoice=1; //This int saves the chocie chosen by the AI
    string myOptions[6] = {"Scissors", "Paper", "Rock", "Lizard", "Spock", "To Quit"}; //This array is used in the menu that allows custome size

    //Continue the loop untill the player enters 6 or more to exit the loop
    while(playerOneChoice <= 5)
    {

        //Display menu
        displayMenu(myOptions, 6);
        playerOneChoice = getAnswer(); //Get input through error trapping

        playerTwoChoice = rand()%5; //Get AI's random input
        cout << ">- AI: " << playerTwoChoice+1 << endl; //Display AI choice

        didPlayerWin(playerOneChoice-1, playerTwoChoice); //Call function to determine who wins

        system("PAUSE"); //clear console and reset
        system("CLS");
    }
    return 0;
}

//This function is used to determine if the player wins or looses or ties
void didPlayerWin(int inputOne, int inputTwo)
{
    if(inputOne == inputTwo) //If player and AI input is the same, tie
    {
        cout << " Tie" << endl;
    }
    else if(inputTwo == (inputOne + 1)%5 || inputTwo == (inputOne + 3)%5) //If player chooses input that wins to AI choice (following pattern), say that player wins
    {
        cout << " Player One won" << endl;
    }
    else //otherwise player looses, tell player
    {
        cout << " Player Two won" << endl;
    }
    return; //Return
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

//Function to show the menu: All positions are options except last which is reserved for quit number
void displayMenu(string options[], int arraySize)
{
    //Display instructions
    for(int i = 0; i < arraySize; i++)
    {
        cout << ">- [" << i+1 << "] " << options[i] << endl;
    }
    cout << endl << ">- Please pick a number to procede" << endl;
    return;
}
