#include <iostream>

using namespace std;

int main()
{
    int n;
    int year = 2019;
    int day = 2;

    cout << "enter now" << endl;
    cin >> n;

    while(year != 2019-n)
    {
        cout << "Day" << day << " Year" << year << endl;
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            day = (day + 2) % 7;
        }
        else
        {
            day = (day + 1) % 7;
        }
        year --;
    }

    if(day == 1)
    {
        cout << "sat" << endl;
    }
    else if(day == 2)
    {
        cout << "fri" << endl;
    }
    else if(day == 3)
    {
        cout << "thu" << endl;
    }
    else if(day == 4)
    {
        cout << "wed" << endl;
    }
    else if(day == 5)
    {
        cout << "tue" << endl;
    }
    else if(day == 6)
    {
        cout << "mon" << endl;
    }
    else
    {
        cout << "sun" << endl;
    }

    cout << day;
}
