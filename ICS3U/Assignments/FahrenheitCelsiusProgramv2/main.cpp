/*
>- Author: Max Wong
>- Date: Sep 16, 2019
>- Updated: Sep 17, 2019
>- Purpose: write a Fahrenheit-Celsius converter with MORE!
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

#include <windows.h>   // WinApi header

using namespace std;

int main()
{
    //Defining the variables
    string inputCommand = ""; //This string is used as the main input method
    float savedFloat = 0; //This float is the main variable used for conversion
    bool enteringNumber = false; //This boolean ensures that error trapping will loop you back
    bool enableNumSystem = false; //TO allow a different GUI setup

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //HANDLE and hCOnsole are using the windows.h lbrary to color individual letters


    while(inputCommand != "/q" )
    {
        //Get player to choose which conversion to use
        cout << ">- Hello, please choose /c or /f to convert to Celsius or Fahrenheit" << endl;

        //Different GUI choice
        if(enableNumSystem)
        {
            cout << endl << ">- Type (1) for Fahrenheit -> Celsius" << endl << ">- Type (2) for Celsius -> Fahrenheit" << endl;
        }

        cout << ">- Type /u to change UI settings and /q to quit" << endl;
        cin >> inputCommand;

        //If player wants to fonvert to Celsius
        if(inputCommand == "/c" || inputCommand == "1")
        {
            enteringNumber = true;
            while(enteringNumber){
                //Get player input
                cout << endl << ">- Please enter your degrees in Fahrenheit" << endl;
                cin >> savedFloat;

                //Call function to check if value is a float or int
                if(cin.fail())
                {
                    cin.clear();
                    cout << ">- [Press Any Key to Continue]" << endl;
                    cin.ignore(9);

                    SetConsoleTextAttribute(hConsole, 12);
                    //Print Error message
                    cout << ">- Error, please enter a decimal value" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else
                {
                    //Now convert and output
                    cout << "In Celsius: " << ((savedFloat - 32) * 5)/9 << endl;
                    enteringNumber = false;
                    inputCommand = "/c";
                }
            }
        }

        //If player wants to fonvert to Fahrenheit
        else if(inputCommand == "/f" || inputCommand == "2")
        {
            enteringNumber = true;
            while(enteringNumber){
                cout << endl << ">- Please enter your degrees in Celsius" << endl;
                cin >> savedFloat;

                //Call function to check if value is a float or int
                if(cin.fail())
                {
                    cin.clear();
                    cout << ">- [Press Any Key to Continue]" << endl;
                    cin.ignore(9); //Clear errors

                    SetConsoleTextAttribute(hConsole, 12);
                    //Print Error message
                    cout << ">- Error, please enter a decimal value" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else
                {
                    //Now convert and output
                    cout << "In Farenheit: " << (savedFloat * 9)/5 + 32 << endl;
                    cout << endl << ">- Also, why would you ever want to use inferior Imperial system?" << endl;
                    inputCommand = "/f";
                    enteringNumber = false;
                }
            }
        }
        if(inputCommand == "/u")
        {
            enableNumSystem = !enableNumSystem;
        }
        else if(inputCommand != "/c" && inputCommand != "/f" && inputCommand != "/q" && inputCommand != "/u")
        {
            SetConsoleTextAttribute(hConsole, 12);
            //Print Error message
            cout << ">- Error, please input a valid response" << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }

        //Get input before continuing
        cout << endl << "[Press any key to continue]" << endl;
        getch();
        system("CLS");
    }
    return 0;
}
