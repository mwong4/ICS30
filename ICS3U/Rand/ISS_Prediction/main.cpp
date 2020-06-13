#include <iostream>

using namespace std;

int main()
{
    //declare variables
    int currentDate = 0;
    int currentTime = 0;
    int lastPassoverDay = 0;
    int lastPassoverTime = 0;
    int input;

    //get inputs
    cout << "Please input most recent ISS passover" << endl;
    cin >> currentDate;
    cout << "In 24 hour time, what is the current time?" << endl;
    cin >> currentTime;
    cout << "Please input current date" << endl;
    cin >> lastPassoverDay;
    cout << "In 24 hour time, at what time did the passover occur?" << endl;
    cin >> lastPassoverTime;


    //calculate
    cout << "==========================================" << endl;
    if((((currentDate*24) + currentTime)-((lastPassoverDay*24) + lastPassoverTime))%72 == 0)
    {
        cout << "The ISS is currently above Ottawa" << endl;
    }
    else
    {
        cout << "The ISS will be over Ottawa in " << (((currentDate*24) + currentTime)-((lastPassoverDay*24) + lastPassoverTime))%72 << " days" << endl;
    }

    return 0;
}
