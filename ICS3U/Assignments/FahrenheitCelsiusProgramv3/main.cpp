/*
>- Author: Max Wong
>- Date: Sep 17, 2019
>- Updated: Sep 17, 2019
>- Purpose: write a Fahrenheit-Celsius that has focus on using switch statements!
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
    int savedFloat = 0; //This float is the main variable used for conversion
    bool enteringNumber = false; //This boolean ensures that error trapping will loop you back

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //HANDLE and hCOnsole are using the windows.h lbrary to color individual letters

    while(savedFloat != 3 )
    {
        cout << endl << ">- Type (1) for Fahrenheit -> Celsius" << endl << ">- Type (2) for Celsius -> Fahrenheit" << endl;
        cout << ">- Type (3) to quit" << endl;
        cin >> savedFloat;

        switch (savedFloat)
        {
            case 1:
                enteringNumber = true;
                while(enteringNumber)
                {
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
                        cout << ">- Error, please enter a whole number" << endl;
                        SetConsoleTextAttribute(hConsole, 15);
                    }
                    else
                    {
                        //Now convert and output
                        cout << "In Celsius: ~" << ((savedFloat - 32) * 5)/9 << endl;
                        enteringNumber = false;
                        savedFloat = 1;
                    }
                }
                break;

            case 2:
                enteringNumber = true;
                while(enteringNumber)
                    {
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
                        cout << ">- Error, please enter a whole number" << endl;
                        SetConsoleTextAttribute(hConsole, 15);
                    }
                    else
                    {
                        //Now convert and output
                        cout << "In Farenheit: ~" << (savedFloat * 9)/5 + 32 << endl;
                        cout << endl << ">- Also, why would you ever want to use inferior Imperial system?" << endl;
                        savedFloat = 2;
                        enteringNumber = false;
                    }
                }
                break;

            default:
                if(savedFloat > 3 && savedFloat <= 0)
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    //Print Error message
                    cout << ">- Error, please input a valid response" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
        }

        //Get input before continuing
        cout << endl << "[Press any key to continue]" << endl;
        getch();
        system("CLS");
    }
    return 0;
}
