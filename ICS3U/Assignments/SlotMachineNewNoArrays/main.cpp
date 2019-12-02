/*
>- Author: Max Wong
>- Date: Sep 25, 2019
>- Updated: Dec 2, 2019
>- Purpose: To write a slot machine simulator using references
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
*/

//Declare used libraries
#include <iostream>
#include<limits> //For error trapping

//Declaring using namespace
using namespace std;

//declaring functions
int getAnswer(); //Function used to get the players response as an integer (with error trapping)
void runSlotMachine(int, int, int&, int&, int&); //This function acts as all three slot machines, being preset by each call for different settings

int main()
{
    int payoutCounterOne = 0; //These variable holds the amount of times a slot machine is used to determine when to pay out
    int payoutCounterTwo = 0;
    int payoutCounterThree = 0;

    int coinsCount; //This variable keeps track of remaining coins
    int currentPlays = 0; //This variable keeps track of how many tiems the player has played

    do
    {
        currentPlays = 0;
        system("CLS"); //Whipe console

        cout << ">- Please enter how many quarters Martha has (between 0 and 1000 inclusively)" << endl;
        coinsCount = getAnswer(); //Get the player's inputs

        //Get slot machine input
        cout << endl << ">- Please enter the case situation for each slot machine" << endl << ">- Machine one: ";
        payoutCounterOne = getAnswer(); //Call the function to get the first slot machine preset
        cout << ">- Machine 2: ";
        payoutCounterTwo = getAnswer(); //Call the function to get the second slot machine preset
        cout << ">- Machine 3: ";
        payoutCounterThree = getAnswer(); //Call the function to get the third slot machine preset

        while(coinsCount > 0)
        {
            runSlotMachine(35, 30, payoutCounterOne, coinsCount, currentPlays); //Call the function to run machine 1
            runSlotMachine(100, 60, payoutCounterTwo, coinsCount, currentPlays); //Call function to run machine 2
            runSlotMachine(10, 9, payoutCounterThree, coinsCount, currentPlays); //Call function to run machine 3
        }
        //Display how many tries martha has been able to try using the counter variable
        cout << endl << ">- Martha plays " << currentPlays << " times" << endl;

        //Ask if the player would like to play again
        cout << ">- Would martha like to try again? Press 1 to continue" << endl;
        coinsCount = getAnswer();

    }while(coinsCount == 1);

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
void runSlotMachine(int _payoutWhen, int _payoutQuantity, int& _payoutCounter, int& _coinsCount, int& _currentPlays)
{
    if(_coinsCount > 0) //Check if player has coins. If yes, run section below
    {
        _payoutCounter ++; //Martha has played once
        if(_payoutCounter == _payoutWhen) //If the machine reaches 10 tries, payout 9 coins and reset payout counter
        {
            _payoutCounter = 0;
            _coinsCount += _payoutQuantity;
        }
        _coinsCount --; //Take one coin away for playing
        _currentPlays ++; //The player has played once
    }
    return;
}
