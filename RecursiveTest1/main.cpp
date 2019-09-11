#include <iostream>
#include <cstdlib>

using namespace std;


void arrangeValues(int, int[]);

int main()
{
    int arraySize;
    cout << "Please define array size" << endl;
    cin >> arraySize;

    arraySize -= 1;

    int numberArray[arraySize];

    for(int i = 0; i < arraySize; i++)
    {
        numberArray[i] = rand() % 10;
    }

    return 0;
}

void arrangeValues (int arraySize, int numberArray[])
{
    if(numberArray[arraySize] >= numberArray[arraySize -1])
    {
        arrayValues(arraySize - 1, numberArray[]);
        return;
    }
    if(e)
}
