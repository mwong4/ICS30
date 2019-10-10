/*
>- Author: Max Wong
>- Date: Oct 3, 2019
>- Updated: Oct 9, 2019
>- Purpose: To write code that can convert bases
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-

TODO
Error trapping
Up to hexadeciaml
*/

//Defining Libraries
#include <iostream>
#include <math.h> //For floor function
#include <string> //for conversions to string

#include <string.h>
#include <stdio.h> //For converting string to array

//Defining namespace
using namespace std;

//Declre all function prototypes
int toBaseTen(int, float);
void fromBaseTen(float, float);

int main()
{
    float targetNumber = 0; //This is the number being converted;
    float baseNumber = 0; //This value is your base value
    float secondBase = 0; //The intended ending base number
    int tempInt = 0; //A temporary variable that stores an integer

    cout << ">- Please select a number between 3" << endl << ">- 1) Any base to Decimal" << endl << ">- 2) Decimal to any base" << endl << ">- 3) Any base to any base" << endl;
    cin >> targetNumber;

    if(targetNumber == 1)
    {
        //Get player input
        cout << ">- Hello, please enter your /any/ base value" << endl;
        cin >> tempInt;

        cout << ">- Now, define your base" << endl;
        cin >> baseNumber;
        tempInt  = toBaseTen(tempInt, baseNumber);

        cout << "Answer: " << tempInt << endl; //Output answer
    }
    else if(targetNumber == 2)
    {
        cout << ">- Hello, please enter your base 10 value" << endl;
        cin >> targetNumber;

        cout << ">- Now, define your base" << endl;
        cin >> baseNumber;
        fromBaseTen(targetNumber, baseNumber);
    }
    else
    {
        cout << ">- Hello, please enter the number you want to convert" << endl;
        cin >> targetNumber;

        cout << ">- Now, define your starting base" << endl;
        cin >> baseNumber;

        cout << ">- Now, define your ending base" << endl;
        cin >> secondBase;

        tempInt = toBaseTen(targetNumber, baseNumber);
        fromBaseTen(tempInt, secondBase);
    }

    return 0;
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
    int tempInt = 0; //A temporary integer to convert to base greater than 9
    string answerString = ""; //This string saves your answer

    do
    {
        tempInt = (((targetNumber/baseNumber) - floor(targetNumber/baseNumber))*baseNumber);

        switch(tempInt)
        {
            case 10:
                answerString.insert(0,"A");
                break;
            case 11:
                answerString.insert(0,"B");
                break;
            case 12:
                answerString.insert(0,"C");
                break;
            case 13:
                answerString.insert(0,"D");
                break;
            case 14:
                answerString.insert(0,"E");
                break;
            case 15:
                answerString.insert(0,"F");
                break;
            default:
                answerString.insert(0, to_string(tempInt));
                break;
        }

        targetNumber = floor(targetNumber/baseNumber);
    }while(targetNumber > (baseNumber-1));

    tempInt = targetNumber;
    answerString.insert(0, to_string(tempInt));

    cout << "Final answer: " << answerString << endl;
}
