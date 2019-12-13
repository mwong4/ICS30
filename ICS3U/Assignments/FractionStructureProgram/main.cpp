/*
>- Author: Max Wong
>- Date: Dec 13, 2019
>- Updated: Dec 13, 2019
>- Purpose: To write functions to manipulate fractions with structures
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
TO DO

-efficient reduction
*/

#include <iostream>
#include <tgmath.h> //For ceil and sqrt functions
#include<limits> //For error trapping
#include <conio.h> //For getch();

using namespace std;

struct Fraction{
    int numerator;
    int denominator;
};

void display(Fraction); //This function is used to display the fraction
void initialize(Fraction&, int, int); //This function is used to set the value of the fraction
Fraction add(Fraction, Fraction); //This function is to add two fractions together
Fraction sub(Fraction, Fraction); //This function is to subtract one fraction from another
Fraction mul(Fraction, Fraction); //This function is to multiply two fractions
Fraction div(Fraction, Fraction); //This function is to divide two fractions
void compare(Fraction, Fraction); //This function is to compare two fractions

Fraction reduce(Fraction);
void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number
int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)
void tapAny(); //Better system pause system

int main()
{
    //Declare the fraction structures and initialize them
    Fraction fracOne, fracTwo, answer;
    initialize(fracOne, 1, 2);
    initialize(fracTwo, 2, 8);
    int getInput = 0; //This integer is used to get player's input
    //This array of strings show the possible options that can be picked and are displayed by the menu function
    string menuOptions[7] = {"Display", "Addition", "Subtraction", "Multiplication", "Division", "Compare", "Quit"};

    while(getInput != 6)
    { //Display menu and get player input
        displayMenu(menuOptions, 6);
        getInput = getAnswer(7, 1);

        if(getInput == 1)
        {
            display(fracOne);
            cout << " , ";
            display(fracTwo);
        }
        else if(getInput == 2)
        {
            answer = add(fracOne, fracTwo);
            cout << "# + # = ";
            display(answer);
        }
        else if(getInput == 3)
        {
            answer = sub(fracOne, fracTwo);
            cout << "# - # = ";
            display(answer);
        }
        else if(getInput == 4)
        {
            answer = mul(fracOne, fracTwo);
            cout << "# * # = ";
            display(answer);
        }
        else if(getInput == 5)
        {
            answer = div(fracOne, fracTwo);
            cout << "# / # = ";
            display(answer);
        }
        else if(getInput == 5)
        {
            compare(fracOne, fracTwo);
        }
        tapAny(); //Get player's input before wiping console and reseting
        system("CLS");
    }
    return 0;
}

//This function is used to display the fraction
void display(Fraction frac)
{
    cout << frac.numerator << "/" << frac.denominator;
    return;
}

//This function is used to set the value of the fraction
void initialize(Fraction& _frac, int _newNum, int _newDen)
{ //Set value of fraction to those sent to it
    _frac.numerator = _newNum;
    _frac.denominator = _newDen;
    return;
}
//This function is to add two fractions together
Fraction add(Fraction _fracOne, Fraction _fracTwo)
{
    Fraction answer; //Define a new fraction as the answer
    //multiply each fracion by the opposite denominator, then add to other fraction
    answer.numerator = _fracOne.numerator*_fracTwo.denominator + _fracTwo.numerator*_fracOne.denominator;
    answer.denominator = _fracOne.denominator*_fracTwo.denominator;
    //Reduce fraction to lowest multiple using the assigned function
    answer = reduce(answer);
    return answer; //Return answer
}

//This function is to subtract one fraction from another
Fraction sub(Fraction _fracOne, Fraction _fracTwo)
{
    Fraction answer; //Define a new fraction as the answer
    //multiply each fracion by the opposite denominator, then add to other fraction
    answer.numerator = _fracOne.numerator*_fracTwo.denominator - _fracTwo.numerator*_fracOne.denominator;
    answer.denominator = _fracOne.denominator*_fracTwo.denominator;

    if(answer.denominator < 0)
    { //case 1: if numerator is positive but denominator is negative, multiply both by -1 to convert numerator to negative and denominator to positive
      //case 2: if numerator is negative but denominator is negative, multiply both by -1 to convert numerator to negative and positive to positive
      //This section detects these cases and fixed them below
        answer.numerator *= -1;
        answer.denominator *= -1;
    }
    //Reduce fraction to lowest multiple using the assigned function
    answer = reduce(answer);
    return answer; //Return answer
}

//This function is to multiply two fractions
Fraction mul(Fraction _fracOne, Fraction _fracTwo)
{
    Fraction answer; //Define a new fraction as the answer
    answer.numerator = _fracOne.numerator*_fracTwo.numerator; //multiply the numerators
    answer.denominator = _fracOne.denominator*_fracTwo.denominator; //multiply the denominator
    return answer; //Return answer fraction
}

//This function is to divide two fractions
Fraction div(Fraction _fracOne, Fraction _fracTwo)
{
    Fraction answer; //Define a new fraction as the answer
    answer.numerator = _fracOne.numerator*_fracTwo.denominator; //multiply the numerators
    answer.denominator = _fracOne.denominator*_fracTwo.numerator; //multiply the denominator
    return answer; //Return answer fraction
}

//This function is to compare two fractions
void compare(Fraction _fracOne, Fraction _fracTwo)
{
    display(_fracOne);
    if(_fracOne.numerator/_fracOne.denominator == _fracTwo.numerator/_fracTwo.denominator)
    {
        cout << " = ";
    }
    else if(_fracOne.numerator/_fracOne.denominator > _fracTwo.numerator/_fracTwo.denominator)
    {
        cout << " > ";
    }
    else
    {
        cout << " < ";
    }
    display(_fracTwo);
    return;
}

Fraction reduce(Fraction _frac)
{
    for(int i = 2; i < ceil(sqrt(_frac.denominator)); i++)
    { //Go through all possible prime factors
        if(_frac.numerator % i == 0 && _frac.denominator % i == 0)
        { //And check to see if they are indeed factors. If they are, reduce the fraction by that prime factor
            _frac.numerator /= i;
            _frac.denominator /= i;
        }
    }
    return _frac; //Return fraction when done
}

//Displays the menu
void displayMenu(string options[], int arraySize)
{
    cout << endl << ">- Please enter a direct command. Below are the primary listed commands." << endl;
    //Display instructions (using assistance of string array)
    for(int i = 0; i < arraySize; i++)
    {
        cout << ">- [" << i+1 << "] " << options[i] << endl;
    }
    return;
}

//Error trapping funcion that only accepts integers
int getAnswer (int limitMax, int limitMin)
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
            cout << ">- ERROR: Please enter a valid input number" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if(playerInput > limitMax || playerInput < limitMin ) //Otherwise, print an error message
        {
            cout << ">- ERROR: Please enter a number between " << limitMin << " and " << limitMax << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}

 //Better system pause system
void tapAny()
{
    cout << endl << ">- [Input anything to continue]" << endl;
    getch(); //Get any player input before continuing
}

