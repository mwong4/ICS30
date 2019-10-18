/*
>- Author: Max Wong
>- Date: Oct 3, 2019
>- Updated: Oct 9, 2019
>- Purpose: To write code that can convert bases
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
*/

//Defining Libraries
#include <iostream>
#include <math.h> //For floor function
#include <string> //for conversions to string

#include <string.h>
#include <stdio.h> //For converting string to array
#include<limits> //For error trapping

//Defining namespace
using namespace std;

//Declre all function prototypes
int toBaseTen(string, float);
void fromBaseTen(int, float);
int getAnswer(); //Function used to get the players response as an integer (with error trapping)
string getString(); //This function gets a string that fits the constraint

int main()
{
    int targetNumber = 0; //This is the number being converted;
    float baseNumber = 0; //This value is your base value
    float secondBase = 0; //The intended ending base number
    int tempInt = 0; //A temporary variable that stores an integer
    string inputString = "";

    do
    {
        //Let player choose their operation
        cout << ">- Please select a number between 3" << endl << ">- 1) Any base to Decimal" << endl << ">- 2) Decimal to any base" << endl << ">- 3) Any base to any base" << endl << ">- 4) To quit" << endl << endl;
        targetNumber = getAnswer(); //Get input

        if(targetNumber == 1)
        {
            //Get player input for conversion value
            cout << ">- Hello, please enter the number you would like to covert that is of /any/ base value" << endl;
            inputString = getString();
            //Get player input for base value
            cout << ">- Now, define your base" << endl;
            baseNumber = getAnswer();
            //Convert the value to base 10
            tempInt  = toBaseTen(inputString, baseNumber);

            cout << "Answer: " << tempInt << endl; //Output answer
        }
        else if(targetNumber == 2)
        {
            //Get player input for base 10 value
            cout << ">- Hello, please enter your base 10 value" << endl;
            targetNumber = getAnswer();
            //Get input for new base value
            cout << ">- Now, define your base" << endl;
            baseNumber = getAnswer();
            //COnvert
            fromBaseTen(targetNumber, baseNumber);
            targetNumber = 0; //Reset variable to prevent premature quit
        }
        else if(targetNumber == 3)
        {
            //Get player input for value to be converted
            cout << ">- Hello, please enter the number you want to convert" << endl;
            inputString = getString();
            //Get input for original base
            cout << ">- Now, define your starting base" << endl;
            baseNumber = getAnswer();
            //Get input for new base
            cout << ">- Now, define your ending base" << endl;
            secondBase = getAnswer();
            //Convert value to base ten before converting from base 10 to new base
            tempInt = toBaseTen(inputString, baseNumber);
            fromBaseTen(tempInt, secondBase);
            //Reset value to prevent premature quit
            targetNumber = 0;
        }
        else
        {
            //Set value that breaks out of loop, ends program
            cout << ">- Quitting..." << endl;
            targetNumber = 20;
        }
        system("Pause"); //Get any input before clearing the console
        system("CLS");
    }while(targetNumber < 4);
    return 0; //Quit
}

int toBaseTen(string inputValue, float baseNumber)
{
    float targetNumber = 0; //A number that acts as the number to be converted
    int answerNumber = 0;
    string tempString = "";

    //Run the loop to the size of the number to be converted
    for(int i = (inputValue.size() - 1); i >= 0; i --)
    {
        //Find the character/digit, starting from right to left. Save it into a temporary string
        tempString = inputValue.at(i);

        //If the valeus are hexadecimal, find the equivalent decimal value
        if(tempString == "A")
        {
            targetNumber = 10;
        }
        else if(tempString == "B")
        {
            targetNumber = 11;
        }
        else if(tempString == "C")
        {
            targetNumber = 12;
        }
        else if(tempString == "D")
        {
            targetNumber = 13;
        }
        else if(tempString == "E")
        {
            targetNumber = 14;
        }
        else if(tempString == "F")
        {
            targetNumber = 15;
        }
        else
        {
            //convert string to float
            targetNumber = std::atoi (tempString.c_str());
        }
        answerNumber += targetNumber * pow(baseNumber, inputValue.size()-i-1); //Comvert it (float) to base 10 and add to answer
    }
    return answerNumber;
}

void fromBaseTen(int targetNumber, float baseNumber)
{
    float tempFloat = 0; //A temporary integer to convert to base greater than 9
    string answerString = ""; //This string saves your answer

    do
    {   //get the remainder and multiply it to the base
        tempFloat = (((targetNumber/baseNumber) - floor(targetNumber/baseNumber))*baseNumber);

        //If the found value is hexadecimal, convert it
        if(tempFloat == 10)
            { answerString.insert(0,"A");
            }
        else if(tempFloat == 11)
            { answerString.insert(0,"B");
            }
        else if(tempFloat == 12)
            { answerString.insert(0,"C");
            }
        else if(tempFloat == 13)
            { answerString.insert(0,"D");
            }
        else if(tempFloat == 14)
            { answerString.insert(0,"E");
            }
        else if(tempFloat == 15)
            { answerString.insert(0,"F");
            }
        else if(tempFloat > 15)
            { answerString.insert(0,"*");
            }
        else //Otherwise insert it into a string
            { answerString.insert(0, to_string(llround(tempFloat)));
            }
        //Update the number to be converted
        targetNumber = floor(targetNumber/baseNumber);

    }while(targetNumber > (baseNumber-1));

    //in the end, convert the last remaining value and insert into string
    tempFloat = targetNumber;
    answerString.insert(0, to_string(llround(tempFloat)));

    cout << "Final answer: " << answerString << endl;
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
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}

//This function gets a string that fits the constraint
string getString ()
{
    bool foundError; //This boolean is used to know if the value is not valid
    bool isNumber; //This boolean is used to know if the value is not a number
    string inputString = ""; //This string is what the user inputs
    string tempString = ""; //Just a temporary string used to store the chosen character

    do
    {
        //Start by assuming there is an error
        foundError = false;
        isNumber = false;
        cout << ">- Please enter your number" << endl;
        cin >> inputString;

        for(int i = 0; i < inputString.size(); i++)
        {
            tempString = inputString.at(i);
            cout << tempString;
            for(int j = 0; j < 10; j++)
            {
                if (tempString == to_string(j))
                {
                    isNumber = true;
                }
            }
            if(isNumber == false && tempString != "A" && tempString != "B" && tempString != "C" && tempString != "D" && tempString != "E" && tempString != "F")
            {
                foundError = true;
            }
        }
        if(foundError == true)
        {
            cout << ">- [ERROR] Please enter values that are 1-9, A-F" << endl;
        }
    }while(foundError == true);

    return inputString;
}
