/*
>- Author: Max Wong
>- Date: Jan 19, 2020
>- Updated: Jan 19, 2020
>- Purpose: Write a program that will display all the multiples of 5 between 100 and 200 inclusive.
*/

#include <iostream>

using namespace std;

int main()
{
    //This program goes through a cycle 20 times
    for(int i = 0; i < 21; i++)
    {   //Prints out i multiplied to 5 (for multiple of 5) added to 100 (to go from 100 to 200)
        cout << i*5 + 100 << endl;
    }
    return 0;
}
