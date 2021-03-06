/*
>- Author: Max Wong
>- Date: Nov 22, 2019
>- Updated: Nov 29, 2019
>- Purpose: To write functions to manipulate arrays
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
*/

//Declaring used libraries
#include <iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<limits> //For error trapping
#include <conio.h> //For getch();
#include <tgmath.h> //For floor function


//Declaring used namespace
using namespace std;

//Declaring functions used
void resetValues(int[], int); //This function resets the values to 0
void randomizeValues(int[]); //This function randomizes the values in the function
void outputValues(int[], bool); //This function outputs the values to the console
float getAverage(int[]); //This function get's the average of all values in the array
int getSmallest(int[], int); //This function determines what is the smallest value in the array
void determineSmallestPosition(int[], int[], int); //This function determines the position of the smallest value in the array
void replacePosition(int[], int, int); //Thsis fuction replaces a specific position in the array with a value
void swapValues(int[], int, int); //This function swaps the values of two positions in the array
void orderValues(int[], int[]); //This function swaps the values of two positions in the array
float determineMedium(int[], int[], int[]); //This function is to determine what is the medium value

void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number
int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)
void getInput(); //Better system pause system

const int ARRAYSIZE = 9; //This sets the array size for the whole program

int main()
{
    int myValues[ARRAYSIZE]; //Initiate main array
    int lowestValuesPosition[ARRAYSIZE]; //Initiate array that stores all lowest value positions;
    int determineMediumArray[ARRAYSIZE]; //This array is to determine help in determining the medium of the array
    int replacementPosition; //this int is used to determine the position in the array to be edited
    int replacementValue; //This int is to store what value is to be replaced in the array, corresponding to the integer above

    int arrayPositionOne; //This stores the first position to be swapped
    int arrayPositionTwo; //This stores the second position to be swapped

    int inputValue = 0;
    randomizeValues(myValues); //Call randomize function to initiate

    //This array of strings holds the value of all options displayed in the menu function
    string menuOptions[11] = {"set all values to 0", "set all values at random", "output all values in array", "get average of all values", "get smallest value", "get position of smallest value", "edit array", "swap two positions in array", "order values", "Get Medium", "to quit" };

    srand (time(NULL)); //Randomize seed according to time

    while(inputValue < 11)
    {
        displayMenu(menuOptions, 11); //Display the menu
        inputValue = getAnswer(11, 1); //Get player input

        if(inputValue == 1)
        {
            resetValues(myValues, 0); //Call reset function
        }
        else if(inputValue == 2)
        {
            randomizeValues(myValues); //Call randomize function
            cout << "randomized" << endl;
        }
        else if(inputValue == 3)
        {
            system("CLS"); //Wipe console
            outputValues(myValues, true); //Call output function
        }
        else if(inputValue == 4)
        {
            cout << "total average: " << getAverage(myValues) << endl; //Output avergae using total/average function
        }
        else if(inputValue == 5)
        {
            //Call determine smallest value function
            cout << "Smallest value in the array: " << getSmallest(myValues, ARRAYSIZE) << endl; //output found value
        }
        else if(inputValue == 6)
        {
            determineSmallestPosition(myValues, lowestValuesPosition, ARRAYSIZE); //Call determine smallest value function
            outputValues(lowestValuesPosition, false); //ouput array again
        }
        else if(inputValue == 7)
        {
            cout << endl << "Please enter the position (0 to " << ARRAYSIZE-1 << ") you would like to replace." << endl;
            replacementPosition = getAnswer(ARRAYSIZE-1, 0); //Get first player input

            cout << "Please enter the value with wich the position is to be replaced with" << endl;
            replacementValue = getAnswer(10000, -10000); //Get second player input

            replacePosition(myValues, replacementPosition, replacementValue); //Thsis fuction replaces a specific position in the array with a value
        }
        else if(inputValue == 8)
        {
            cout << endl << "Please enter the first position (0-" << ARRAYSIZE-1 << ") you would like to swap." << endl;
            arrayPositionOne = getAnswer(ARRAYSIZE-1, 0); //get first player input

            cout << "Please enter the second position (0-" << ARRAYSIZE-1 << ") you would like to swap" << endl;
            arrayPositionTwo = getAnswer(ARRAYSIZE-1, 0); //get second player input

            swapValues(myValues, arrayPositionOne, arrayPositionTwo); //Swap the values of the two positions chosen above
        }
        else if(inputValue == 9)
        {
            orderValues(myValues, lowestValuesPosition); //Call function to order array
            cout << ">- ordered" << endl;//Tell user that values have been ordered
        }
        else if(inputValue == 10)
        {
            cout << ">- Medium: " << determineMedium(myValues, determineMediumArray, lowestValuesPosition) << endl;
        }
        getInput();
        system("CLS"); //Wipe console
    }
    return 0;
}

 //This function resets the values to 0
void resetValues(int myValues[], int setValue)
{
    //Have a foor loop go through all values in the array and set them to 0
    for(int i = 0; i < ARRAYSIZE; i++)
    {
        myValues[i] = setValue;
    }
    return;
}

 //This function randomizes the values in the function
void randomizeValues(int myValues[])
{
    int randomValue; //This value is a randomly generared number
    //Have the for loop go through the whole aray and set all values to a random value
    for(int i = 0; i < ARRAYSIZE; i++)
    {
        myValues[i] = rand()%20;
        randomValue = rand() % 2;
        if(randomValue == 0)
        {
            myValues[i] *= -1;
        }
    }
    return;
}

 //This function outputs the values to the console
void outputValues(int myValues[], bool displayPosition)
{
    //Have the for loop go through the whole array and read out the values to console
    for(int i = 0; i < ARRAYSIZE; i++)
    {
        if(myValues[i] != 54321) //Output value only if it is not "empty". 54321 represents the value of null with my array
        {
            cout << "position: ";
            if(displayPosition) //If displayOption is true, display position
            {
                cout << i;
            }
            cout << " = " << myValues[i] << endl;
        }
    }
    return;
}

 //This function get's the average of all values in the array
float getAverage(int myValues[])
{
    float totalValue = 0; //Initiate a varaibel that will hold the total
    for(int i = 0; i < ARRAYSIZE; i++)
    {
        //Go through all values in the array and add it to the total varuable
        totalValue += myValues[i];
    }
    //Return average (total/# of array positions)
    return totalValue/ARRAYSIZE;
}

 //This function determines what is the smallest value in the array
int getSmallest(int myValues[], int arraySize)
{
    int smallestValue = 100000; //Variable used to temporarily store the largest variable
    for(int i = 0; i < arraySize; i++)
    {
        //Go through the array and if a new greater value is found, save into temporary variable
        if(myValues[i] < smallestValue)
        {
            smallestValue = myValues[i]; //save current smallest found value
        }
    }
    return smallestValue;
}

 //This function determines the position of the smallest value in the array
void determineSmallestPosition(int myValues[], int lowestValuesPosition[], int arraySize)
{
    resetValues(lowestValuesPosition, 54321); //reset all values in lowest value position array to 54321 (my null value)
    int counter = 0; //Set counter to 0
    int smallestValue = getSmallest(myValues, arraySize); //get the smallest value
    for(int i = 0; i < arraySize; i++) //running through all the positions in the array
    {
        if(myValues[i] == smallestValue) //If the value of the position in the array is the smallest value
        {
            lowestValuesPosition[counter] = i; //save that position into the smallest value position array
            counter ++; //Increase counter by 1;
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
    int tempInt; //This is an integer that temporarily stores an integer value
    tempInt = myValues[positionOne]; //Get the value of the first position
    myValues[positionOne] = myValues[positionTwo]; //assign the value of first to second position
    myValues[positionTwo] = tempInt; //Assign second position to first position
    return;
}

 //This function swaps the values of two positions in the array
void orderValues(int myValues[], int smallestPosition[])
{
    int smallestValue; //This integer stores the smallest value
    int counter = -1; //This is to check if there are more than one of the found smallest number
    for(int i = ARRAYSIZE-1; i > 0; i--) //Run a for loop for all positions in the array
    {
        do //The loop below, summarized, will find all of the smallest value first within the limit, which is gradually decreasing. It will then assign the smallest
        { //value into the array at the end, backfilling over time. If there is a duplicate of a value, the code will NOT try and find all the smallest value positions again.
            counter ++; //Every time we loop, we add one to counter
            if(counter == 0) //If we are running the loop for the first time, find the smallest value and all the positions
            {
                smallestValue = getSmallest(myValues, i+1); //assign the smallest value
                determineSmallestPosition(myValues, smallestPosition,  i+1); //determine the smallest value position
            }
            swapValues(myValues, smallestPosition[counter], i); //swap the position of the first smallest value and the i position. Reassign array
        }while(smallestPosition[counter + 1] == smallestValue); //If the smallest value has a duplicate, loop, but skip finding the next duplicates
        counter = -1;//Reset variable
    }
    return; //when finished, return;
}

 //This function is to determine what is the medium value
float determineMedium(int myValues[], int secondArray[], int smallestPosition[])
{
    int midle;
    for(int i = 0; i < ARRAYSIZE; i++)
    { //Go through every value in the secondary array and set to match the values of the first array
        replacePosition( secondArray, i, myValues[i]);
    }
    orderValues(secondArray, smallestPosition);

    if(ARRAYSIZE % 2 == 0)
    {
        return (secondArray[ARRAYSIZE/2-1] + secondArray[ARRAYSIZE/2])/2.0;
    }
    else
    {
        midle = floor(ARRAYSIZE/2.0);
        return secondArray[midle];
    }
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
void getInput()
{
    cout << endl << ">- [Input anything to continue]" << endl;
    getch(); //Get any player input before continuing
}
