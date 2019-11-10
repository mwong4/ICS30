/*
>- Author: Max Wong
>- Date: Oct 30, 2019
>- Updated: Oct 30, 2019
>- Purpose: To determine the composition of prime numbers in an inputted number
*/

//Define libraries
#include <iostream>
#include <tgmath.h>
//For error trapping
#include<limits>
#include <windows.h>   // WinApi header

//Defins using namespace
using namespace std;

//Define function prototypes
int determinePrime(int);//This function determines the smallest prime multiple of the input number
float getAnswer(); //Function used to get the players response as an integer (with error trapping)

int main()
{
    int inputNumber = 2; //The input number to be decompossed
    int returnedValue; //A temporary number that stores the output

    while(inputNumber == 2)
    {
        system("CLS"); //Clear console
        cout << ">- Please input an integer" << endl;
        inputNumber = getAnswer(); //Get input

        cout << ">- composition:" << endl;

        while(inputNumber > 1)
        {
            returnedValue = determinePrime(inputNumber); //Call function and get multiple
            inputNumber /= returnedValue; //Update input number

            if(returnedValue == 1) //If function tells main to end program, output before ending program
            {
                cout << inputNumber;
                inputNumber = 1;
            }
            else //Otherwise, output and loop
            {
                cout << returnedValue << ", ";
            }
        }
        cout << endl << ">- end" << endl;
        inputNumber = 0;

        cout << endl << ">- Would you like to play again? Press 2 to loop" << endl;
        inputNumber = getAnswer();
    }

    return 0;
}

//This function determines the smallest prime multiple of the input number
int determinePrime(int inputNumber)
{
    //Go through every possible prime number multiple
    for(int i = 2; i <= ceil(sqrt(inputNumber)); i++)
    {
        if(inputNumber % i == 0) //Once multiple found (division without remainder)
        {
            return i; //Return multiple
        }
    }
    return 1; //Otherwise, return 1 to signal end
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
        else if(playerInput < 2)
        {
            cout << ">- [Error], please enter a number greater than 1" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}
