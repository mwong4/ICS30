#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int randomX;
    int randomY;

    long int programRuns;
    long double inCircleCounter = 0;

    cout << ">- Input runs" << endl;
    cin >> programRuns;

    for(int i = 0; i <= programRuns; i++)
    {
        randomX = rand() % 100 - 50;
        randomY = rand() % 100 - 50;

        if(sqrt((randomX*randomX) + (randomY * randomY)) <= 50)
        {
            inCircleCounter ++;
        }
        if(i%10000 == 0)
        {
             cout << "pi = " << ((inCircleCounter * 1.0)/ programRuns)*4 << endl;
        }
    }

    cout << "pi = " << ((inCircleCounter * 1.0)/ programRuns)*4 << endl;
    cout << ((inCircleCounter * 1.0)/ programRuns) << endl;
    cout << inCircleCounter << endl;
    cout << programRuns << endl;


    return 0;
}
