/*
>- Author: Max Wong
>- Date: Sep 17, 2019
>- Updated: Oct 24, 2019
>- Purpose: write a Fahrenheit-Celsius that has focus on using functions and menus!
*/

//Defining libraries
#include <iostream>
#include <conio.h>

//For error trapping
#include<limits>
#include <windows.h>   // WinApi header

using namespace std;

float toCelsius(float); //This function converts Fahrenheit to Celsius
float toFahrenheit(float); //This function converts Celsius to Fahrenheit
float getAnswer(); //Function used to get the players response as an integer (with error trapping)

int main()
{
    //Defining the variables
    int inputNumber = 0; //This integer is used for the players menu input
    float savedTemp;

    while(inputNumber != 3 )
    {
        cout << endl << ">- Type (1) for Fahrenheit -> Celsius" << endl << ">- Type (2) for Celsius -> Fahrenheit" << endl;
        cout << ">- Type (3+) to quit" << endl;
        inputNumber = getAnswer();

        if(inputNumber == 1)
        {
            //Get input
            savedTemp = getAnswer();
            //Now convert and output
            savedTemp = toFahrenheit(savedTemp);
            cout << "In Celsius: ~" << savedTemp << endl;
        }
        else if(inputNumber == 2)
        {
            //Get input
            savedTemp = getAnswer();
            //Now convert and output
            savedTemp = toCelsius(savedTemp);
            cout << "In Fahrenheit: ~" << savedTemp << endl;
        }
        else
        {
            inputNumber = 3;
        }

        //Get input before continuing
        cout << endl << "[Press any key to continue]" << endl;
        getch();
        system("CLS");
    }
    return 0;
}

//This function converts Fahrenheit to Celsius
float toCelsius(float originalTempature)
{
    return (originalTempature * 9.0)/5.0 + 32.0;
}

//This function converts Celsius to Fahrenheit
float toFahrenheit(float originalTempature)
{
    return ((originalTempature - 32.0) * 5.0)/9.0;
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
