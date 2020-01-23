/*
>- Author: Max Wong
>- Date: Jan 22, 2020
>- Updated: Jan 22, 2020
>- Purpose: To write a program to convert integer numbers to roman numerals
*/

#include <iostream>
#include<limits>     //For error trapping
#include <string>    //For inserting strings
#include <cstring>   //For string length
#include <math.h>    //This is for rounding
#include <stdio.h>   //For ceil function

using namespace std;

struct UserData
{
    int inputNumber; //This is the user's number input
    string romanNumeral; //this is the user's input in roman numerals
};

void resetStruct(UserData&); //This is used to reset the struct at the start
void convertNumber(UserData&, string[]); //This function is used to conver the number from decimal to roman numeral
int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)

int main()
{
    UserData myData; //Initializing the user's data
    string onesNumerals[9] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}; //This array of strings is to represent 1-9 (ones) in roman numerals
    resetStruct(myData); //Call function to reset struct

    cout << "Hello, please input your integer number" << endl;
    myData.inputNumber = getAnswer(100, 1); //Get input from user

    convertNumber(myData, onesNumerals);//Call function to conver int to roman numeral

    cout << "Your number in numerals is: " << myData.romanNumeral << endl;
    return 0;
}

void resetStruct(UserData& _data)
{
    _data.romanNumeral = ""; //Set string to empty
    return;
}

void convertNumber(UserData& _data, string onesNumerals[])
{
    while(_data.inputNumber > 0)
    {
        if(_data.inputNumber == 100)
        { //If number is 100
            _data.romanNumeral.insert(_data.romanNumeral.length(), "C"); //Insert C to denote 100
            _data.inputNumber -= 100; //Update number
        }
        else if(_data.inputNumber > 90)
        { //If over 90
            _data.romanNumeral.insert(_data.romanNumeral.length(), "XC"); //Insert XC to represent 90s
            _data.inputNumber -= 90; //Update number
        }
        else if(_data.inputNumber > 60)
        { //If over 60
            _data.romanNumeral.insert(_data.romanNumeral.length(), "L"); //Insert L for over 60s
            for(int i = 0; i < ceil(_data.inputNumber  / 10) - 6; i++)
            { //For every 10 over 60, add an X
                _data.romanNumeral.insert(_data.romanNumeral.length(), "X"); //Insert X
                _data.inputNumber -= 10; //Update number
            }
            _data.inputNumber -= 50; //Update that it is over 60
        }
        else if(_data.inputNumber > 50)
        { //If over 50
            _data.romanNumeral.insert(_data.romanNumeral.length(), "L"); //Insert L to show 50s
            _data.inputNumber -= 50; //Update number
        }
        else if(_data.inputNumber > 40)
        { //If over 40s
            _data.romanNumeral.insert(_data.romanNumeral.length(), "XL"); //Insert XL to denote 40s
            _data.inputNumber -= 40; //Update number
        }
        else if(_data.inputNumber > 10)
        { //If over 10
            for(int i = 0; i < ceil(_data.inputNumber  / 10); i++)
            { //For every 10 less than 40 but greater than 10, add an X
                _data.romanNumeral.insert(_data.romanNumeral.length(), "X"); //Find ones column and insert into string
                _data.inputNumber -= 10; //Update number
            }
        }
        else
        { //Otherwise
            _data.romanNumeral.insert(_data.romanNumeral.length(), onesNumerals[_data.inputNumber % 10 - 1]); //Find ones column and insert into string
            _data.inputNumber = 0; //Update number
        }
        cout << "number " << _data.inputNumber << " numeral " << _data.romanNumeral << endl; //Print debugging messages
    }

    return;
}

int getAnswer (int _maxLimit, int _minLimit)
{
    int playerInput; //This variable is used to get the player's input
    bool findingInput; //This bool determines if the loop continues running
    do
    {
        findingInput = false; //By default, the loop will end
        cout << "    >- Your input: "; //Get player input
        cin >> playerInput;
        if(cin.fail())//Check to see if player entered a "bad" input type
        {
            cin.clear(); //Clear all flags
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore incorrect symbols
            cout << "  >- Please enter a valid input number" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if(playerInput > _maxLimit || playerInput < _minLimit ) //Otherwise, print an error message
        {
            cout << "  >- Please enter a number between " << _minLimit << " and " << _maxLimit << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }
    while(findingInput);
    return playerInput;//Otherwise input is good, return input
}


