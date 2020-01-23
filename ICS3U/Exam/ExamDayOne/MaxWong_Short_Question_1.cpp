/*
>- Author: Max Wong
>- Date: Jan 21, 2020
>- Updated: Jan 21, 2020
>- Purpose: Write a program that will ask the user for an integer and display all the perfect squares
less than that integer. (This does not need to be done using a function.)
*/

#include <iostream>
#include<limits>     //For error trapping

using namespace std;

int getAnswer(); //Function used to get the players response as an integer (with error trapping)

int main()
{
    int userInput; //This is an input integer from the user
    cout << "Please enter an integer" << endl;
    userInput = getAnswer();//Get input from user

    for(int i = 1; i*i < userInput; i++)
    { //Go through 1 to ... untill the squares are greater than the input number
            cout << "found: " << i*i << endl;
    }
    return 0;
}

//Function used to get the players response as an integer (with error trapping)
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
