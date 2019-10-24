/*
>- Author: Max Wong
>- Date: Sep 25, 2019
>- Updated: Sep 27, 2019
>- Purpose: To write a slot machine simulator
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
*/

//Declare used libraries
#include <iostream>
#include<limits> //For error trapping

//Declaring using namespace
using namespace std;

//Delcaring structures
struct PlayerData
{
    int payoutCounter[3] = {0,0,0}; //These variables keep count of when the slot machines will give a payout
    int coinsCount; //This variable keeps track of remaining coins
    int currentPlays = 0; //This variable keeps track of how many tiems the player has played
};

//declaring functions
int getAnswer(); //Function used to get the players response as an integer (with error trapping)
PlayerData runSlotMachine(int, int, int, PlayerData); //This function acts as all three slot machines, being preset by each call for different settings

int main()
{
    PlayerData marthaData; //Delcaring structure in the loop

    do
    {
        marthaData.currentPlays = 0;
        system("CLS"); //Whipe console

        cout << ">- Please enter how many quarters Martha has (between 0 and 1000 inclusively)" << endl;
        marthaData.coinsCount = getAnswer(); //Get the player's inputs

        //Get slot machine input
        cout << endl << ">- Please enter the case situation for each slot machine" << endl << ">- Machine one: ";
        marthaData.payoutCounter[0] = getAnswer(); //Call the function to get the first slot machine preset
        cout << ">- Machine 2: ";
        marthaData.payoutCounter[1] = getAnswer(); //Call the function to get the second slot machine preset
        cout << ">- Machine 3: ";
        marthaData.payoutCounter[2] = getAnswer(); //Call the function to get the third slot machine preset

        while(marthaData.coinsCount > 0)
        {
            marthaData = runSlotMachine(0, 35, 30, marthaData); //Call the function to run machine 1
            marthaData = runSlotMachine(1, 100, 60, marthaData); //Call function to run machine 2
            marthaData = runSlotMachine(2, 10, 9, marthaData); //Call function to run machine 3
        }
        //Display how many tries martha has been able to try using the counter variable
        cout << endl << ">- Martha plays " << marthaData.currentPlays << " times" << endl;

        //Ask if the player would like to play again
        cout << ">- Would martha like to try again? Press 1 to continue" << endl;
        marthaData.coinsCount = getAnswer();

    }while(marthaData.coinsCount == 1);

    return 0;
}

//Get player input. Check to see if there is an error
int getAnswer ()
{
    int playerInput; //This variable is used to get the player's input
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
            cout << endl << ">- [Error], please enter an integer value!" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if( playerInput < 0 || playerInput > 1000) //Else if player input is not between 1 to 3, pritn error message
        {
            cout << endl << ">- [Error], please enter an value between 1 and 100!" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}

//This function acts as all three slot machines, being preset by each call for different settings
PlayerData runSlotMachine(int currentMachine, int payoutWhen, int payoutQuantity, PlayerData marthaData)
{
    if(marthaData.coinsCount > 0) //Check if player has coins. If yes, run section below
    {
        marthaData.payoutCounter[currentMachine] ++; //Martha has played once
        if(marthaData.payoutCounter[currentMachine] == payoutWhen) //If the machine reaches 10 tries, payout 9 coins and reset payout counter
        {
            marthaData.payoutCounter[currentMachine] = 0;
            marthaData.coinsCount += payoutQuantity;
        }
        marthaData.coinsCount --; //Take one coin away for playing
        marthaData.currentPlays ++; //The player has played once
    }
    return marthaData;
}
