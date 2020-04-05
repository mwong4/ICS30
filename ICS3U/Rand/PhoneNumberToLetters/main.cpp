#include <iostream>
#include <vector> //For vectors

#include <cstdlib> //For string to int conversion
#include <windows.h> //For custom key input

//TO DO

//reset loop

using namespace std;

const char CHARS[28] = {'1', 'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m','n','o','v','q','r','s','t','u','v','w','x','y','z', '0'};

int showIter(int); //returns the number of iterations
int startingPos(int); //returns the position in array to start from
void recurOutput(int, int, vector<int>, vector<char>); //This recursive function outputs all values

int main()
{
    string inputValue = ""; //This is for user input
    int numSize = 0; //this is for the size of the phone number input
    int tempNum = 0; //This is a temp integer
    vector<int> phoneNum; //This is the phone number
    vector<char> prevChain; //This represents the chain preceding the digit (in recur function)
    string tempString = ""; //This is a temporary string value

    while(inputValue != "exit") //loop untill exit line
    {
        numSize = 0;
        phoneNum.clear();
        prevChain.clear();

        cout << "Please enter your phone number. Type /exit/ to end program" << endl;
        cin >> inputValue; //Get user input

        if(inputValue != "exit") //if not exit line
        {
            //Break up input
            for(int i = (inputValue.size() - 1); i >= 0; i --)
            {
                //get character at the back
                tempString = inputValue.at(i);
                tempNum = std::atoi (tempString.c_str());
                //add to vector
                phoneNum.insert(phoneNum.begin(), tempNum);
            }
            numSize = (inputValue.size()); //increase size

            //Output number
            cout << "number: ";
            for(int i = 0; i < numSize; i++)
            {
                cout << phoneNum[i];
            }
            cout << endl << "size: " << numSize << endl;

            recurOutput(0, numSize, phoneNum, prevChain);
        }

        cout << endl;
        system("pause");
        system("CLS");
    }

    return 0;
}

//returns the number of iterations
int showIter(int _input)
{
    if(_input == 1 || _input == 0)
    {
        return 1; //if number 1, iterate 1 times
    }
    else if((_input > 1 && _input < 7) || _input == 8)
    {
        return 3; //else if numbers 2-6, 8, iterate 3 times
    }
    else
    {
        return 4; //otherwise if number 7, 9, iterate 4 times
    }
}

//returns the position in array to start from
int startingPos(int _input)
{
    //return respective starting numbers
    if(_input == 1)
    {
        return 0;
    }
    else if(_input == 0)
    {
        return 27;
    }
    else if(_input > 1 && _input < 7)
    {
        return (1 + 3*(_input - 2));
    }
    else if(_input == 7)
    {
        return 16;
    }
    else if(_input == 8)
    {
        return 20;
    }
    else if(_input == 9)
    {
        return 23;
    }
}

//This recursive function outputs all values
void recurOutput(int _currentPos, int _limit, vector<int> _phoneNumber, vector<char> _prevChain)
{
    if(_currentPos != _limit) //if the limit is not reached
    {
        int startingPosition = startingPos(_phoneNumber[_currentPos]); //Get array starting positions
        for(int i = 0; i < showIter(_phoneNumber[_currentPos]); i++) //run a for loop for every digit in phone number
        {
            if((GetKeyState('E') & 0x8000))
            {
                cout << endl;
                system("PAUSE"); //If failsafe key is pressed, pause program
            }

            if( i != 0) //spacing
            {
                for(int j = 0; j < _currentPos; j++)
                { //more spacing
                    cout << _prevChain[j]; //For spacing
                }
            }
            cout << CHARS[startingPosition + i]; //output value from const array
            if(_currentPos == _limit - 1) cout << " "; //if this is the ending digit, end line

            _prevChain.push_back(CHARS[startingPosition + i]);

            recurOutput(_currentPos + 1, _limit, _phoneNumber, _prevChain); //call recurive function again

            _prevChain.pop_back();
        }
    }

    return; //otherwise, return and end specific itteration
}
