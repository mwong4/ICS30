#include <iostream>

using namespace std;

int factorialFunction(int, int);

int main()
{
    int factorialSize;
    int result = 1;

    cin >> factorialSize;
    result = factorialFunction(factorialSize, result);
    cout << result << endl;
}

int factorialFunction(int factorialSize, int result)
{
    result = result * (factorialSize);
    if((factorialSize - 1) == 1)
    {
        return result;
    }
    else
    {
        factorialFunction(factorialSize - 1, result);
    }
}

/*
    Enter a result and a size. multiply the result, which starts at one to the size. Than, if the next value to be multiplied (size - 1)
    if less than 0, return the result as the function is finished. If the next value is not 1, call the same function again, but reduce the size by one.
    To summarize, the function will repetitively multiply the size and the size -1 until size becomes 2, in whihc case it will multiply one last time,
    then return the result.
*/
