#include <iostream>
#include <tgmath.h> //For floor function

using namespace std;

//This function is used to find the greatest common denominator between two numbers
findGCD(int _numOne, int _numTwo)
{
    int remainder = 0; //This integer is used to store the remainder temporarily from each mod.
    if(_numTwo > _numOne)
    { //To avoid an error, if num2 is greater than num1, swap them
        remainder = _numOne;
        _numOne = _numTwo;
        _numTwo = remainder;
    }
    cout << _numOne << " , " << _numTwo << endl;
    while(_numOne % _numTwo != 0) //Run Euclidean's Algorithm to find the greatest common denominator
    {
        remainder = _numOne % _numTwo; //get remainder of num1 mod num2
        _numOne = _numTwo; //Set num1 as num2
        _numTwo = remainder; //Set num2 as remainder
    }
    return _numTwo; //When done, return num2
}

int main()
{
cout << findGCD(2,8) << endl;
    return 0;
}
