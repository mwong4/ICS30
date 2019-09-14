/*
>- Author: Max Wong
>- Date: Sep 13, 2019
>- Updated: Sep 13, 2019
>- Purpose: write a Fahrenheit-Celsius converter
*/

//Defining libraries
#include <iostream>
#include <conio.h>

//For error trapping
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <string>

using namespace std;

//Function used for error trapping
bool stringChecker(string);

int main()
{
    //Defining the variables
    string inputCommand = ""; //This string is used as the main input method
    float savedFloat = 0; //This float is the main variable used for conversion
    bool enteringNumber = false; //This boolean ensures that error trapping will loop you back
    bool enableNumSystem = false; //TO allow a different GUI setup

    while(inputCommand != "/q" )
    {
        //Get player to choose which conversion to use
        cout << ">- Hello, please choose /c or /f to convert to Celsius or Fahrenheit" << endl;

        //Different GUI choice
        if(enableNumSystem) cout << endl << ">- Type (1) for Fahrenheit -> Celsius" << endl << ">- Type (2) for Celsius -> Fahrenheit" << endl;

        cout << ">- Type /u to change UI settings and /q to quit" << endl;
        cin >> inputCommand;

        //If player wants to fonvert to Celsius
        if(inputCommand == "/c" || inputCommand == "1")
        {
            enteringNumber = true;
            while(enteringNumber){
                //Get player input
                cout << endl << ">- Please enter your degrees in Fahrenheit" << endl;
                cin >> inputCommand;

                //Call function to check if value is a float or int
                if(stringChecker(inputCommand))
                {
                    //Convert input string to float value
                    savedFloat =::atof(inputCommand.c_str());

                    //Now convert and output
                    cout << "In Celsius: " << ((savedFloat - 32) * 5)/9 << endl;
                    enteringNumber = false;
                    inputCommand = "/c";
                }
                else
                {
                    //Print Error message
                    cout << ">- Error, please enter a decimal value" << endl;
                }
            }
        }

        //If player wants to fonvert to Fahrenheit
        if(inputCommand == "/f" || inputCommand == "2")
        {
            enteringNumber = true;
            while(enteringNumber){
                cout << endl << ">- Please enter your degrees in Celsius" << endl;
                cin >> inputCommand;

                //Call function to check if value is a float or int
                if(stringChecker(inputCommand))
                {
                    //Convert input string to float value
                    savedFloat =::atof(inputCommand.c_str());

                    //Now convert and output
                    cout << "In Farenheit: " << (savedFloat * 9)/5 + 32 << endl;
                    cout << endl << ">- Also, why would you ever want to use inferior Imperial system?" << endl;
                    inputCommand = "/f";
                    enteringNumber = false;
                }
                else
                {
                    //Print Error message
                    cout << ">- Error, please enter a decimal value" << endl;
                }
            }
        }
        if(inputCommand == "/u")
        {
            enableNumSystem = !enableNumSystem;
        }
        else if(inputCommand != "/c" && inputCommand != "/f" && inputCommand != "/q" && inputCommand != "/u")
        {
            //Print Error message
            cout << ">- Error, please input a valid response" << endl;
        }

        //Get input before continuing
        cout << endl << "[Press any key to continue]" << endl;
        getch();
        system("CLS");
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
