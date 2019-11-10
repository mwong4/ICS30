/*
>- Author: Max Wong
>- Date: Oct 28, 2019
>- Updated: Oct 28, 2019
>- Purpose: To determine if a number is prime
*/

//Declaring used libraries
#include <iostream>
#include <tgmath.h>

//Declaring namespace
using namespace std;

//Function that determines if the number is prime or not
bool determineIfPrime(int);

int main()
{
    //Declare the variables
    int inputNumber; //this is the input value

    cout << ">- Please input an integer" << endl;
    cin >> inputNumber; //Get player input

    //Check to see if the valeu is prime or not, and return to user
    if(determineIfPrime(inputNumber))
    {
        cout << ">- This number is prime" << endl;
    }
    else
    {
        cout << ">- This number is not prime" << endl;
    }

    return 0;
}

//Function that determines if the number is prime or not
bool determineIfPrime(int inputNumber)
{
    //If the number is 1, return false
    if(inputNumber == 1)
    {
        return false;
    }

    //Run through all numbers up to and excluding 1 and the input number
    for(int i = 2; i < ceil(sqrt(inputNumber)); i++)
    {
        //If the division is clean (no remainder), number is not prime
        if(inputNumber % i == 0)
        {
            //In the case the number is not prime, return false
            return false;
        }
    }
    //Otherwise, the number passes the test and is prime
    return true;
}
