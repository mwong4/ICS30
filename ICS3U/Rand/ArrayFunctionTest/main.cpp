#include <iostream>

using namespace std;

//prototype
int modArrayPos(int);

int main()
{
    //This is the array
    int arrayThing[3] = {1, 2, 3};

    //Call function to modify array
    arrayThing[0] = modArrayPos(arrayThing[0]);

    //Display first value of array
    cout << "pos 1: " << arrayThing[0] << endl;
    return 0;
}

int modArrayPos(int arrayPos)
{
    arrayPos = 10;
    return arrayPos;
}
