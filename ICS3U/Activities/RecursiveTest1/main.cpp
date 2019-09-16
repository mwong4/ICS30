#include <iostream>
#include <cstdlib>

using namespace std;

//Prototype function to get largest value
void greatestValue(int, int[]);

int main()
{
    //Define Array
    int arraySize;

    //Get Array Size
    cout << "Please define array size" << endl;
    cin >> arraySize;

    //Initialize Array
    int numberArray[arraySize + 1];

    //Set Array to random values
    srand(arraySize);
    for(int i = 0; i < arraySize + 1; i++)
    {
        numberArray[i] = rand() % 10;
        srand(rand() & 10);
    }

    numberArray[0] = 0;

    //Read Array
    for(int i = 0; i < arraySize + 1; i++)
    {
        cout << numberArray[i] << " ";
    }
    cout << endl;

    //Call function
    greatestValue(arraySize, numberArray);

    //Print out largest number
    cout << numberArray[0];

    return 0;
}

//Function to find the largest number
void greatestValue (int arraySize, int numberArray[])
{
    //If item in array is larger than saved largest value, save value
    if(numberArray[arraySize] > numberArray[0]) numberArray[0] = numberArray[arraySize];
    //If all values in the array are compared, return
    if(arraySize <= 1) return;

    //Otherwise, move onto next array item and call same function
    arraySize -= 1;
    greatestValue(arraySize, numberArray);
}

