#include <iostream>
#include <string>

using namespace std;

string getString(); //This function gets a string that fits the constraint

int main()
{
    /*
    string str = "123456789";
    string tempString = "";
    int stringSize = str.size();

    for(int i = 0; i < str.size(); i++)
    {
        cout << str.at(i) << endl;
        cout <<  to_string(i) << endl;

        //tempString = str.at(i);
        if(tempString == to_string(i))
       {
           cout << "cool" << endl;
       }
    }
    */

    string hi;

    hi = getString();

    return 0;
}

string getString ()
{
    bool foundError; //This boolean is used to know if the value is not valid
    bool isNumber; //This boolean is used to know if the value is not a number
    string inputString = ""; //This string is what the user inputs
    string tempString = ""; //Just a temporary string used to store the chosen character

    do
    {
        //Start by assuming there is an error
        foundError = false;
        isNumber = false;
        cout << ">- Please enter your number" << endl;
        cin >> inputString;

        for(int i = 0; i < inputString.size(); i++)
        {
            tempString = inputString.at(i);
            cout << tempString;
            for(int j = 0; j < 10; j++)
            {
                if (tempString == to_string(j))
                {
                    isNumber = true;
                }
            }
            if(isNumber == false && tempString != "A" && tempString != "B" && tempString != "C" && tempString != "D" && tempString != "E" && tempString != "F")
            {
                foundError = true;
            }
        }
        if(foundError == true)
        {
            cout << ">- [ERROR] Please enter values that are 1-9, A-F" << endl;
        }
        cout << "foundError " << foundError << endl;
    }while(foundError == true);

    return inputString;
}

