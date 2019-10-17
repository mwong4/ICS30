/*
>- Author: Max Wong
>- Date: Oct 3, 2019
>- Updated: Oct 9, 2019
>- Purpose: To write code that can convert bases
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- TODO
    //Up to hexadeciaml
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
int toBaseTen(int, float);
void fromBaseTen(float, float);
int getAnswer(); //Function used to get the players response as an integer (with error trapping)

int main()
{
    float targetNumber = 0; //This is the number being converted;
    float baseNumber = 0; //This value is your base value
    float secondBase = 0; //The intended ending base number
    int tempInt = 0; //A temporary variable that stores an integer

    do
    {
        //Let player choose their operation
        cout << ">- Please select a number between 3" << endl << ">- 1) Any base to Decimal" << endl << ">- 2) Decimal to any base" << endl << ">- 3) Any base to any base" << endl << ">- 4) To quit" << endl << endl;
        targetNumber = getAnswer(); //Get input

        if(targetNumber == 1)
        {
            //Get player input for conversion value
            cout << ">- Hello, please enter your /any/ base value" << endl;
            tempInt = getAnswer();
            //Get player input for base value
            cout << ">- Now, define your base" << endl;
            baseNumber = getAnswer();
            //Convert the value to base 10
            tempInt  = toBaseTen(tempInt, baseNumber);

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
            targetNumber = getAnswer();
            //Get input for original base
            cout << ">- Now, define your starting base" << endl;
            baseNumber = getAnswer();
            //Get input for new base
            cout << ">- Now, define your ending base" << endl;
            secondBase = getAnswer();
            //Convert value to base ten before converting from base 10 to new base
            tempInt = toBaseTen(targetNumber, baseNumber);
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

int toBaseTen(int tempInt, float baseNumber)
{
    float targetNumber = 0; //A number that acts as the number to be converted
    int answerNumber = 0;

    //Run for loop 100000 times
    for(int i = 0; i < 100000; i ++)
    {
        //Get the single digit
        targetNumber =  tempInt % 10;
        answerNumber += targetNumber * pow(baseNumber, i); //Comvert it to base 10
        tempInt = floor(tempInt/10); //update the target number to one digit less

        if(tempInt  <= 0) //If the input is 0, close loop
        {
            i = 100001;
        }
    }
    return answerNumber;
}

void fromBaseTen(float targetNumber, float baseNumber)
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
            { answerString.insert(0, to_string(tempFloat));
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
