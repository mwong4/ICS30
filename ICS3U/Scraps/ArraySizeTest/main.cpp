#include <iostream>
#include <array>

using namespace std;

int main()
{
    string myOptions[6] = {"Scissors", "Paper", "Rock", "Lizard", "Spock", "To Quit"};

    cout << sizeof(myOptions)/24 << endl;

    for(int i = 0; i < sizeof(myOptions)/24; i++)
    {
        cout << ">- [" << i+1 << "] " << myOptions[i] << endl;
    }
    return 0;
}
