/*
>- Author: Max Wong
>- Date: Sep 1, 2019
>- Updated: Jan 3, 2020
>- Purpose: To write a game for a summative project.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 1.1.9]
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [TO DO]
>- Efficiency
    //Fix all !! parts
        //Fix struct bug
        //Get placement done
    //Commenting
    //Get rid of set values in structs
*/

//Declaring all used libraries
#include <iostream>
#include <windows.h>   // WinApi header(red text)
#include<limits>    //For error trapping
#include <fstream> //For the map saving
#include <conio.h> //For getch();


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
    string playerName;
    float currentGDP = 2000; //The stating US GDP is 2 trillion
    float currentIncome = 0.01; //The starting military funding is 0.001%
    float currentBalance = 0.5; //The current military balance is 500 millsion dollars
};

//Delcaring function prototypes

void display(char); //This function is for displaying a single character
void setSpot(char&, char); //This function is to set a specific spot in the map
gameInfo goThroughMap(gameInfo, char, bool); //This function is to go through every spot in the map. It can use other functions to set it all or display it
gameInfo getMap(gameInfo); //This function is used to find each line in the map txt file
gameInfo saveMap(std::string, gameInfo, int); //This function is used to extract each character in a map file line

playerData endTurn(playerData, float); //This function is in charge of updating the player data for the next turn

int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)
void displayMenu(string[], int, playerData, int); //Function to show the menu: All positions are options except last which is reserved for quit number
void displayRedText(string, bool); //This function is used to display red text
void anyInput(); //This is an integrated version of getch(); and a message
string getName(); //This function is used to get the player's name, disguised as the start menu

int main()
{
    //Declaring all variables

    //Declare and initialize game data -> specifically the map
    gameInfo gameData; //This struct represents the important information for the whole game
    //gameData = getMap(gameData);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Fix This

    playerData usa; //This struct represents the important information for player usa
    usa.playerName = getName(); //Initialize it

    gameData = goThroughMap(gameData, ' ', false); //Read out whole map
    string primaryOptions[3] = {"create a new base","|| Finish Turn >>", "quit"}; //This array represents the optiosn available in the main menu

    int menuInput = 1; //This int represents the input taken from user

    while(menuInput != 3)//While player does not choose to quit
    {
        gameData = goThroughMap(gameData, ' ', false); //Display map
        displayMenu(primaryOptions, 3, usa, gameData.currentYear); //Display all menu options
        menuInput = getAnswer(3,1); //Get player input

        if(menuInput == 1)
        {
            //Go to place base function
            //!!!!!!!!!!!!!!!!!!!! Get this done
        }
        else if(menuInput == 2)
        { //Go to end turn function
            gameData.currentYear ++;//Update year
            usa = endTurn(usa, 0); //Calls function to update income
        }
        else
        { //Quit game
            cout << ">- Quitting..." << endl << ">- [Please press any key to continue]" << endl;
            anyInput();//Get any input before continuing
        }
        system("CLS"); //Cleans console
    }
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
    cout << "hello";
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

playerData endTurn(playerData _data, float _budgetChange) //This function is in charge of updating the player data for the next turn
{
    float randomValue; //This number is randomly generated
    system("CLS"); //Clear console first

    randomValue = (rand()%4+1)/100.0; //Get the random increase or decrease of the GDP
    if(rand() % 5 == 0 && randomValue < 3 )
    {
        //In decrease (less likely), display percent and update GDP
        cout << "         >- Economy decreased by -> " << randomValue*100 << "%" << endl;
        _data.currentGDP -= _data.currentGDP*randomValue;
    }
    else
    {
        //In increase (more likely), display percent and update GDP
        cout << "         >- Economy increased by -> " << randomValue*100 << "%" << endl;
        _data.currentGDP += _data.currentGDP*randomValue;
    }
    //Show new GDP
    cout << "         >- GDP is Now:" << _data.currentGDP << " billion" << endl;

    //Change income percent if government changes it
    _data.currentIncome += _budgetChange;

    //Update the income of the department
    _data.currentBalance += (_data.currentGDP*_data.currentIncome)/100.0;
    cout << "         >- Current Department Anual Budget: " << _data.currentBalance << " billion dollars" << endl;

    anyInput();//Get any input before continuing
    return _data;
}


//Error trapping funcion that only accepts integers
int getAnswer (int _maxLimit, int _minLimit)
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
    cout << "[January 1, " << _year << "] <> Current Department Balance: " << _data.currentBalance<< " billion dollars" << endl;
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

//This is an integrated version of getch(); and a message
void anyInput()
{
    cout << ">- [Press Any Key To Continue]" << endl;
    getch();
    return;
}

//This function is used to get the player's name, disguised as the start menu
string getName()
{
    //Defining the variables
    string userID = "unknown"; //This represents the username
    string randInput = ""; //This represents the password inputted by the user
    char ch; //This is used to get each individual input

    cout << ">- -UNSC User Management System-" << endl << "================================" << endl << "________________________________" << endl;
    cout << "UNSC TacOS  v.337" <<  endl << "(S) 2294 FLEETCOM" << endl << "=======================" <<  endl << "|  User Log:" << endl;
    cout << "|  >> Administrator (UNSC ID 8384-C)" << endl << "|  >>> " << "unknown.IDENTIFY_userGroup" << endl << endl;
    cout << "________________________________" << endl << "================================" << endl << endl << ">- Please enter your pin and ID" << endl << endl;

    cout << ">- ID: ";
    cin >> userID;
    cout << ">- PIN: ";

    //Fake username and password system. Converts all letters into *'s
    ch = _getch();
    while(ch != 13)
    {
        randInput.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout << endl << ">- \Acess Granted." << endl << ">- Welcome " << userID << endl;
    anyInput();

    return userID;
}
