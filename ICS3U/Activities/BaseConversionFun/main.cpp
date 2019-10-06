#include <iostream>
#include <math.h>

using namespace std;

int main()
{

    int number[4];
    int baseNumber;
    float answer, partialAnswer, remainder, targetNumber;
    int playerResponse;
    int randomValue = rand() % 2;

    answer = 0;
    baseNumber = 0;
    //Convert to base 10
    if(randomValue == 0)
    {
        randomValue = rand() % 2;
        if(randomValue == 0)
        {
            baseNumber = rand() % 16;
            cout << ">- Please convert ";
            for(int i = 0; i < 4; i++)
            {
                number[i] = rand() % baseNumber;
                if(number[i] == 10 ) cout << "A";
                if(number[i] == 11 ) cout << "B";
                if(number[i] == 12 ) cout << "C";
                if(number[i] == 13 ) cout << "D";
                if(number[i] == 14 ) cout << "E";
                if(number[i] == 15 ) cout << "F";
                else cout << number[i];
            }
            cout << " To base 10" << endl;

        }
        else
        {
            baseNumber = rand() % 10;
            cout << ">- Please convert ";
            for(int i = 0; i < 4; i++)
            {
                number[i] = rand() % baseNumber;
                cout << number[i];
            }
            cout << " To base 10" << endl;
        }
                    for(int i = 0; i < 4; i++)
            {
                answer += number[i] * (baseNumber ^ i);
            }

            cout << ">- Answer: ";
            cin >> playerResponse;
            if(playerResponse == answer) cout << ">- Good, the Answer is: " << answer << endl;
            else cout << ">- Bad, the Answer is: " << answer << endl;
    }
    else
    {
        cout << ">- Convert ";
        for(int i = 0; i < 4; i++)
        {
            number[i] = rand() % 10;
            cout << number[i];
        }
            baseNumber = (rand() % 20) + 1;
        cout << " to base " << baseNumber << endl;

        for(int i = 0; i < 4; i++)
        {
            targetNumber = (targetNumber* 10) + number[i];
        }

        for(int i = 0; i < 30; i++)
        {
            partialAnswer = ((targetNumber / baseNumber) - floor(targetNumber / baseNumber))*baseNumber;
            answer += partialAnswer*baseNumber*(10 ^ i);
            targetNumber = floorI((targetNumber / baseNumber));
            if(targetNumber <= baseNumber)
            {
                i = 30;
            }
        }


    }
    return 0;
}
