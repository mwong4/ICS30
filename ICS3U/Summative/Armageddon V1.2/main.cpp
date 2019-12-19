/*
>- Author: Max Wong
>- Date: Sep 1, 2019
>- Updated: Dec 19, 2019
>- Purpose: To write a game for a summative project.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 1.1.7]
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [TO DO]
>- Efficiency
*/

//Declaring all used libraries
#include <iostream>
#include <windows.h>   // WinApi header(red text)
#include<limits>    //For error trapping
#include <fstream> //For the map saving


//Declaring used namespaces
using namespace std;

//Delcaring used structures
struct gameInfo //This struct holds the core game data
{
    int currentYear = 1945; //Year is 1945
    char gameMap [199][55];//This is the double array that houses the whole map
};

struct playerData //This struct holds the data for each player
{
    float currentGDP = 2000000; //The stating US GDP is 2 trillion
    float currentIncome = 0.001; //The starting military funding is 0.001%
    float currentBalance = 0.5; //The current military balance is 500 millsion dollars
};

//Delcaring function prototypes

void display(char); //This function is for displaying a single character
void setSpot(char&, char); //This function is to set a specific spot in the map
gameInfo goThroughMap(gameInfo, char, bool); //This function is to go through every spot in the map. It can use other functions to set it all or display it
gameInfo getMap(gameInfo); //This function is used to find each line in the map txt file
gameInfo saveMap(std::string, gameInfo, int); //This function is used to extract each character in a map file line

float getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)
void displayMenu(string[], int, gameInfo); //Function to show the menu: All positions are options except last which is reserved for quit number
void displayRedText(string, bool); //This function is used to display red text

int main()
{
    //Declaring all variables

    //Declare and initialize game data -> specifically the map
    gameInfo myGameInfo;
    myGameInfo = getMap(myGameInfo);
    myGameInfo = goThroughMap(myGameInfo, ' ', false);




    return 0;
}

//This function is for displaying a single character
void display(char _mapSpot)
{
    cout << _mapSpot;
    return;
}

//This function is to set a specific spot in the map
void setSpot(char& _spot, char _newValue)
{
    _spot = _newValue;
    return;
}

//This function is to set completely clean off the map at the start of the game
gameInfo goThroughMap(gameInfo _gameData, char _clearValue, bool _setMap)
{
    for(int i = 0; i < 55; i++)
    {
        for(int j = 0; j < 199; j++)
        {
            if(_setMap)
            {
                setSpot(_gameData.gameMap[j][i], _clearValue);
            }
            else
            {
                display(_gameData.gameMap[j][i]);
            }
        }
        if(!_setMap)
        {
            cout << endl;
        }
    }
    return _gameData;
}

//This function is used to find each line in the map txt file
gameInfo getMap(gameInfo _gameData)
{
    std::string line;
    ifstream file_("MapFile.txt");

    int currentRow = 0;

    if(file_.is_open())
    {
        while(getline(file_,line)) //This function uses the builtin function: getline
        {
            _gameData = saveMap(line, _gameData, currentRow); //It then references the saveMapFile function in order to save it into a doubel array.
            currentRow += 1;
        }
        file_.close();
    }
    return _gameData;
}

//This function is used to extract each character in a map file line
gameInfo saveMap(std::string _line, gameInfo _gameData, int _currentRow)
{
    for(std::string::size_type i = 0; i < _line.size(); ++i) //Running through every character
    {
        setSpot(_gameData.gameMap[i][_currentRow], _line[i]);
    }
    return _gameData;
}


//Error trapping funcion that only accepts integers
float getAnswer (int _maxLimit, int _minLimit)
{
    int playerInput; //This variable is used to get the player's input
    bool findingInput; //This bool determines if the loop continues running
    do
    {
        findingInput = false; //By default, the loop will end
        cout << "         >- Your input: "; //Get player input
        cin >> playerInput;
        if(cin.fail())//Check to see if player entered a "bad" input type
        {
            cin.clear(); //Clear all flags
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore incorrect symbols
            displayRedText("  ==================================================", true);
            displayRedText("  >- Please enter a valid input number", true);
            displayRedText("  ==================================================", true);
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if(playerInput > _maxLimit || playerInput < _minLimit ) //Otherwise, print an error message
        {
            displayRedText("  ==================================================", true);
            cout << "  >- Please enter a number between " << _minLimit << " and " << _maxLimit << endl;
            displayRedText("  ==================================================", true);
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}

//Displays the menu
void displayMenu(string _options[], int _arraySize, playerData _data, int _year)
{
    //Display UI
    cout << "         >- Please enter a direct command. Below are the primary listed commands.                                                      ";
    cout << "[January 1, " << _year << "] <> Current Department Balance:" << _data.currentBalance<< " billion dollars" << endl;
    //Display instructions
    for(int i = 0; i < _arraySize; i++)
    {
        cout << "         >- [" << i+1 << "] " << _options[i] << endl;
    }
    return;
}

//Displays text in red
void displayRedText(string _inputOne, bool _returnTrue)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //HANDLE and hCOnsole are using the windows.h lbrary to color individual letters

    SetConsoleTextAttribute(hConsole, 12); //Set color to red
    cout << _inputOne;
    SetConsoleTextAttribute(hConsole, 15); //Set color to red
    if(_returnTrue)
    {
        cout << endl;
    }
}
