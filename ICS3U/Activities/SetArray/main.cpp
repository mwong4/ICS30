/*
>- Author: Max Wong
>- Date: Nov 22, 2019
>- Updated: Nov 22, 2019
>- Purpose: To write functions to manipulate arrays
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++

TO DO List:
 Make more efficient
 Check requirements
 Commenting
 Getch; implementation
*/

//Declaring used libraries
#include <iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//For error trapping
#include<limits>

//Declaring used namespace
using namespace std;

//Declaring functions used
void resetValues(int[], int, int); //This function resets the values to 0
void randomizeValues(int[], int); //This function randomizes the values in the function
void outputValues(int[], int); //This function outputs the values to the console
float getAverage(int[], int); //This function get's the average of all values in the array
int getSmallest(int[], int); //This function determines what is the smallest value in the array
void determineSmallestPosition(int[], int, int[]); //This function determines the position of the smallest value in the array
void replacePosition(int[], int, int); //Thsis fuction replaces a specific position in the array with a value
void swapValues(int[], int, int); //This function swaps the values of two positions in the array
void orderValues(int[]); //This function swaps the values of two positions in the array

void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number
int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)

int main()
{
    int myValues[10]; //Initiate main array
    int lowestValuesPosition[10]; //Initiate array that stores all lowest value positions;
    int replacementPosition;
    int replacementValue;
    int randomValue = -5/*0*/;

    string menuOptions[10] = {"set all values to 0", "set all values at random", "output all values in array", "get average of all values", "get smallest value", "get position of smallest value", "edit array", "swap two positions in array", "order values", "to quit"};

    srand (time(NULL)); //Randomize seed according to time

    while(randomValue < 10)
    {
        system("CLS"); //Wipe console
        outputValues(myValues, 10); //Call output function
        displayMenu(menuOptions, 10); //Display the menu
        //randomValue = getAnswer(10, 1); //Get player input

        randomValue += 7;

        if(randomValue == 1)
        {
            resetValues(myValues, 10, 0); //Call reset function
        }
        else if(randomValue == 2)
        {
            randomizeValues(myValues, 10); //Call randomize function
            cout << "randomized" << endl;
        }
        else if(randomValue == 3)
        {
            system("CLS"); //Wipe console
            outputValues(myValues, 10); //Call output function
        }
        else if(randomValue == 4)
        {
            cout << "total average: " << getAverage(myValues, 10) << endl; //Output avergae using total/average function
            system("PAUSE");
        }
        else if(randomValue == 5)
        {
            randomValue = getSmallest(myValues, 10); //Call determine smallest value function
            cout << "Smallest value in the array: " << randomValue << endl;
            system("PAUSE");
            randomValue = 5;
        }
        else if(randomValue == 6)
        {
            determineSmallestPosition(myValues, 10, lowestValuesPosition); //Call determine smallest value function
            outputValues(lowestValuesPosition, 10);
            system("PAUSE");
        }
        else if(randomValue == 7)
        {
            cout << endl << "Please enter the position (0-9) you would like to replace." << endl;
            replacementPosition = getAnswer(9, 1);

            cout << "Please enter the value with wich the position is to be replaced with" << endl;
            replacementValue = getAnswer(9, 1);

            replacePosition(myValues, replacementPosition, replacementValue); //Thsis fuction replaces a specific position in the array with a value
            outputValues(myValues, 10); //Call output function
            system("PAUSE");
        }
        else if(randomValue == 8)
        {
            cout << endl << "Please enter the first position (0-9) you would like to swap." << endl;
            replacementPosition = getAnswer(9, 0);

            cout << "Please enter the second position (0-9) you would like to swap" << endl;
            replacementValue = getAnswer(9, 0);

            swapValues(myValues, replacementPosition, replacementValue);
        }
        else if(randomValue == 9)
        {
            orderValues(myValues);
        }
    }
    return 0;
}

 //This function resets the values to 0
void resetValues(int myValues[], int arraySize, int setValue)
{
    //Have a foor loop go through all values in the array and set them to 0
    for(int i = 0; i < arraySize; i++)
    {
        myValues[i] = setValue;
    }
    return;
}

 //This function randomizes the values in the function
void randomizeValues(int myValues[], int arraySize)
{
    //Have the for loop go through the whole aray and set all values to a random value
    for(int i = 0; i < arraySize; i++)
    {
        myValues[i] = rand()%10;
    }
    return;
}

 //This function outputs the values to the console
void outputValues(int myValues[], int arraySize)
{
    //Have the for loop go through the whole array and read out the values to console
    for(int i = 0; i < arraySize; i++)
    {
        if(myValues[i] != 20) //Output value only if it is not "empty". 20 represents the value of null with my array
        {
            cout << "position: " << i << " = " << myValues[i] << endl;
        }
    }
    return;
}

 //This function get's the average of all values in the array
float getAverage(int myValues[], int arraySize)
{
    float totalValue = 0; //Initiate a varaibel that will hold the total
    for(int i = 0; i < arraySize; i++)
    {
        //Go through all values in the array and add it to the total varuable
        totalValue += myValues[i];
    }
    //Return average (total/# of array positions)
    return totalValue/arraySize;
}

 //This function determines what is the smallest value in the array
int getSmallest(int myValues[], int arraySize)
{
    int smallestValue = 10; //Variable used to temporarily store the largest variable
    for(int i = 0; i < arraySize; i++)
    {
        //Go through the array and if a new greater value is found, save into temporary variable
        if(myValues[i] < smallestValue)
        {
            smallestValue = myValues[i];
            if(smallestValue == 0)
            {
                return smallestValue;
            }
        }
    }
    return smallestValue;
}

 //This function determines the position of the smallest value in the array
void determineSmallestPosition(int myValues[], int arraySize, int lowestValuesPosition[])
{
    resetValues(lowestValuesPosition, 10, 20);
    int counter = 0;
    int smallestValue = getSmallest(myValues, arraySize);
    for(int i = 0; i < arraySize; i++)
    {
        if(myValues[i] == smallestValue)
        {
            lowestValuesPosition[counter] = i;
            counter ++;
        }
    }
    return;
}

 //Thsis fuction replaces a specific position in the array with a value
void replacePosition(int myValues[], int position, int value)
{
    //Set value in position to new input value. Then, return.
    myValues[position] = value;
    return;
}

 //This function swaps the values of two positions in the array
void swapValues(int myValues[], int positionOne, int positionTwo)
{
    int tempInt;

    tempInt = myValues[positionOne];
    myValues[positionOne] = myValues[positionTwo];
    myValues[positionTwo] = tempInt;
    return;
}

 //This function swaps the values of two positions in the array
void orderValues(int myValues[])
{
    int smallestValue;
    int valuePosition;
    int myListArray[10];
    for(int i = 9; i > 0; i--)
    {
        smallestValue = getSmallest(myValues, i+1);
        determineSmallestPosition(myValues, i+1, myListArray);
        valuePosition = myListArray[0];
        swapValues(myValues, valuePosition, i);
    }
    return;
}

//Displays the menu
void displayMenu(string options[], int arraySize)
{
    cout << endl << ">- Please enter a direct command. Below are the primary listed commands." << endl;
    //Display instructions
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
            cout << ">- Please enter a valid input number" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if(playerInput > limitMax || playerInput < limitMin ) //Otherwise, print an error message
        {
            cout << ">- Please enter a number between " << limitMin << " and " << limitMax << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}
