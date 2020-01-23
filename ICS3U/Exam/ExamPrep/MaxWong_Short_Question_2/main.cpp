/*
>- Author: Max Wong
>- Date: Jan 19, 2020
>- Updated: Jan 19, 2020
>- Purpose: Write a program that will:
            - Use main( ) to ask the user for three values
            - Call a function that returns the average of those three values.
            - Use main( ) to display that average to the user.
*/

#include <iostream>
#include<limits>     //For error trapping

using namespace std;

int getAnswer(); //Function used to get the players response as an integer (with error trapping)
float getAverage(int, int, int); //This function returns the average of three ints

int main()
{
    int numOne; //This is the first input from the user
    int numTwo; //This is the second input from the user
    int numThree; //This is the third input from the user

    //Get all values from user
    cout << "Please enter your 3 values" << endl;
    numOne = getAnswer(); //Initialize numOne
    numTwo = getAnswer(); //Initialize numTwo
    numThree = getAnswer(); //Initialize numThree

    cout << "Your avergae is:" << getAverage(numOne, numTwo, numThree) << endl;

    return 0;
}

int getAnswer ()
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
    }
    while(findingInput);
    return playerInput;//Otherwise input is good, return input
}

//This function returns the average of three ints
float getAverage(int _numOne, int _numTwo, int _numThree)
{
    return (_numOne + _numTwo + _numThree) / 3.0; //This gets and returns the average
}
