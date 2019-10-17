#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str = "Hello World";
    int stringSize = str.size();

    for(int i = 0; i < str.size(); i++)
    {
        cout << stringSize << " - 1 - " << i << endl;
        cout << i << ")  " << str.at(stringSize - i - 1) << endl;
    }

    return 0;
}
