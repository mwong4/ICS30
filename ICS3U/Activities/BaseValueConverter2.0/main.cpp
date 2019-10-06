/*
>- Author: Max Wong
>- Date: Oct 3, 2019
>- Updated: Oct 3, 2019
>- Purpose: To write code that can convert bases
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
*/

#include <iostream>
#include <math.h> //For floor function
#include <sstream>

using namespace std;

int main()
{
    float targetNumber; //This is the number being converted;
    float baseNumber; //This value is your base value
    float answerNumber; //This value is the answer -> the coverted value
    float counter = 0; //This variable is a counter for the while loop that converts the values;

    float inputNumber; //This variable us used as an input for base something to base 10


    cout << ">- Hello, please enter your base 10 value" << endl;
    cin >> targetNumber;

    cout << ">- Now, define your base" << endl;
    cin >> baseNumber;

    do
    {
        answerNumber += (((targetNumber/baseNumber) - floor(targetNumber/baseNumber))*baseNumber)/* *pow(10, counter)*/;
        targetNumber = floor(targetNumber/baseNumber);
        counter ++;
    }while(targetNumber > (baseNumber-1));
    answerNumber += targetNumber * pow(10, (counter));

    cout << "Final answer: " << answerNumber << endl;



    /*
    cout << ">- Hello, please enter your /any/ base value" << endl;
    cin >> targetNumber;

    cout << ">- Now, define your base" << endl;
    cin >> inputNumber;

    do
    {
        targetNumber = (inputNumber % 10);
        cout << targetNumber << endl;
    }while(inputNumber > 0);
    */

    return 0;
}
