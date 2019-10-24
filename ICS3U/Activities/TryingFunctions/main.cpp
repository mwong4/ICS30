#include <iostream>

using namespace std;

int addThreeNumbers (int, int, int);

int main()
{
    int firstValue, secondValue, thirdValue;

    cout << ">- Please enter your first value" << endl;
    cin >> firstValue;

    cout << ">- Please enter your second value" << endl;
    cin >> secondValue;

    cout << ">- Please enter your third value" << endl;
    cin >> thirdValue;

    cout << endl << ">- You have " << addThreeNumbers(firstValue,secondValue,thirdValue) << " crows. Please hide them." << endl;
    return 0;
}

int addThreeNumbers (int firstNumber, int secondNumber, int thirdNumber)
{
    return firstNumber + secondNumber + thirdNumber;
}
