/*
>- Author: Max Wong
>- Date: Sep 1, 2019
>- Updated: Jan 5, 2020
>- Purpose: To write a game for a summative project.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 1.3.0]
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [TO DO]

    ////////////////////////////// Goals for today

>- If defcon reaches 1, loose game

>- Random Aircraft Spawn

>- Scan aircraft
    >- Tag them different colors

>- Advance Events

>- Restricted placement system
    >-Fill map?
    >- Russia
    >- Ocean

>- Commenting


    ////////////////////////////// Goal for tmrw

>- !!!!!!!!! Check with Mr. M on while(true)
*/

//Declaring all used libraries
#include <iostream>  //For basic input output
#include <windows.h> // WinApi header(red text)
#include<limits>     //For error trapping
#include <fstream>   //For the map saving
#include <conio.h>   //For getch();
#include <tgmath.h>  //For rounding
#include <stdio.h>    //For NULL (srand)
#include <stdlib.h>   //For srand, rand
#include <time.h>     //For time


//Declaring used namespaces
using namespace std;

//Delcaring used structures
struct gameInfo //This struct holds the core game data
{
    float baseCost; //This is the price of the buildings
    int currentYear; //Year counter
    float defcon;
    char gameMap [199][55];//This is the double array that houses the whole map
};

struct playerData //This struct holds the data for each player
{
    string playerName;
    float currentGDP; //The US GDP
    float currentIncome; //The % funding for the department
    float currentBalance; //The military budget, how much funding in dollars
};

//Delcaring function prototypes

void display(char); //This function is for displaying a single character
void setSpot(char&, char); //This function is to set a specific spot in the map
gameInfo goThroughMap(gameInfo, char, bool); //This function is to go through every spot in the map. It can use other functions to set it all or display it
gameInfo getMap(gameInfo); //This function is used to find each line in the map txt file
gameInfo saveMap(std::string, gameInfo, int); //This function is used to extract each character in a map file line

playerData endTurn(playerData, float, float&, float&, string[], string[]); //This function is in charge of updating the player data for the next turn
void defconCounter(string[], float); //This function is to display the defcon state
void worldEvent(float&, string[]); //This function is to display the world events

gameInfo chooseBuilding(gameInfo, playerData, string[], string[], float&); //This function is for player to choose their building
gameInfo buildingMode(gameInfo, playerData, string[], char, float&); //This function is for the general mode of building
gameInfo keyboardMode(gameInfo, int&, int&, char&, char); //This function is for placing base using keyboard
gameInfo coordinateMode(gameInfo, int&, int&, char&, char); //This function is for placing base using a coordinate system
gameInfo updatePosition(gameInfo, int, int, bool, int&, int&, char&, char); //This function is for updating the position of the base

int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)
void displayMenu(string[], int, playerData, int, bool); //Function to show the menu: All positions are options except last which is reserved for quit number
void displayColorText(string, bool, int); //This function is used to display Color text
void anyInput(); //This is an integrated version of getch(); and a message
string getName(); //This function is used to get the player's name, disguised as the start menu
bool getConfirmation(); //This function is to get a boolean response from the player

int main()
{
    srand (time(NULL)); //Randomize seed according to time
    //Declaring all variables

    //Declare and initialize game data -> specifically the map
    gameInfo gameData; //This struct represents the important information for the whole game
    gameData.currentYear = 1945; //Set the starting year to 1945
    gameData.baseCost = 0.1; //Set the starting cost of buildings to 0.1 billion dollars
    gameData.defcon = 5;
    gameData = getMap(gameData); //Initialize the value of the map array

    playerData usa; //This struct represents the important information for player usa
    //Set default values (initialize)
    usa.currentGDP = 2000; //The stating US GDP is 2 trillion
    usa.currentIncome = 0.01; //The starting military funding is 0.01%
    usa.currentBalance = 0.5; //The current military balance is 500 million dollars
    usa.playerName = getName(); //Initialize name by using the loading screen

    string primaryOptions[3] = {"Enter building mode","|| Finish Turn >>", "Quit"}; //This array represents the optiosn available in the main menu
    string buildingOptions[3] = {"InterContinental Balistic Missile Launch Facility", "Advance Warning Complex", "Quit"}; //This represents the available options for buildings
    string buildModeOptions[4] = {"Place using keyboard", "Place using coordinate", "Confirm place", "Cancel/Exit build mode"}; //These are the menu options for build mode
    //These are the five states of DEFCON advance warning
    string defconOptions[5]= {"CRITICAL|| Nuclear War Imminent","SEVERE|| Armed Forces Ready to Deploy in 6 hours","SUBSTANTIAL|| Air Force Mobilizes in 15 Minutes","MODERATE|| Increase Security Readiness","LOW|| Normal Peacetime Readiness"};
    //World events that may or may not change your income/funding
    string worldEvents[10] = {"Funding is re-directed to Boost the Economy","New Governemnt Against-Military","Anti-War Protests are Widespread","Sovites Become More Agresive","New US Government is Pro-Military","Public Opinion Swings Pro-Military","NATO Military Exercise Occurs in Western Europe","Warsaw Pact Meet For Annual Military Sumit","Refugees Continue to Flee Eastern Europe","Civil War Occurs in South America"};

    int menuInput = 1; //This int represents the input taken from user

    while(menuInput != 3)//While player does not choose to quit
    {
        gameData = goThroughMap(gameData, ' ', false); //Display map
        displayMenu(primaryOptions, 3, usa, gameData.currentYear, true); //Display all menu options
        menuInput = getAnswer(3,1); //Get player input

        if(menuInput == 1)
        {
            gameData = chooseBuilding(gameData, usa, buildingOptions, buildModeOptions, usa.currentBalance);
        }
        else if(menuInput == 2)
        { //Go to end turn function
            gameData.currentYear ++;//Update year
            usa = endTurn(usa, 0, gameData.baseCost, gameData.defcon, defconOptions, worldEvents); //Calls function to update income
        }
        else
        { //Quit game
            cout << "    >- Quitting..." << endl << ">- [Please press any key to continue]" << endl;
            anyInput();//Get any input before continuing
        }
        system("CLS"); //Cleans console
    }
    return 0;
}

//This function is for displaying a single character
void display(char _mapSpot)
{
    if(_mapSpot == '@')
    {
        displayColorText("@", false, 14); //yellow
    }
    else if(_mapSpot == '#')
    {
        displayColorText("#", false, 2); //Dark green
    }
    else if(_mapSpot == '!')
    {
        displayColorText("!", false, 4); //Red
    }
    else if(_mapSpot == '?')
    {
        displayColorText("?", false, 9); //Blue
    }
    else if(_mapSpot == '&')
    {
        displayColorText("&", false, 10); //Light green
    }
    else
    {
        cout << _mapSpot;
    }
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

//This function is in charge of updating the player data for the next turn
playerData endTurn(playerData _data, float _budgetChange, float& _baseCost, float& _defcon, string _defconOptions[], string _worldEvents[])
{
    float randomValue; //This number is randomly generated
    system("CLS"); //Clear console first

    _defcon -= 0.05; //Increase defcon naturally
    defconCounter(_defconOptions, _defcon); //Call function to display defcon information

    worldEvent(_data.currentIncome, _worldEvents); //Call function to display current world issues


    randomValue = (rand()%5+1)/100.0; //Get the random increase or decrease of the GDP
    if(rand() % 5 == 0 && randomValue < 3 )
    {
        //In decrease (less likely), display percent and update GDP
        cout << "    >- Economy decreased by -> " << randomValue*100 << "%" << endl;
        _data.currentGDP -= _data.currentGDP*randomValue;
    }
    else
    {
        //In increase (more likely), display percent and update GDP
        cout << "    >- Economy increased by -> " << randomValue*100 << "%" << endl;
        _data.currentGDP += _data.currentGDP*randomValue;
    }
    //Show new GDP
    cout << "    >- GDP is Now: " << _data.currentGDP << " billion dollars" << endl;

    //Change income percent if government changes it
    _data.currentIncome += _budgetChange;

    //Update the income of the department
    _data.currentBalance += (_data.currentGDP*_data.currentIncome)/100.0;
    cout << "    >- Current Department Anual Budget: " << _data.currentBalance << " billion dollars" << endl;


    randomValue = (rand()%3+7)/100.0; //Get the random increase in inflation
    _baseCost += _baseCost*randomValue; //Increase price of buildings

    anyInput();//Get any input before continuing
    return _data;
}

//This function is to display the defcon state
void defconCounter(string _defconOptions[], float _defcon)
{
    int defconLevel; //This integer represents the rounded defcon level
    defconLevel = round(_defcon);

    cout << "    >- DEFCON: [";
    if(defconLevel == 1)
    {
        displayColorText("1", false, 4);
    }
    else if(defconLevel == 2)
    {
        displayColorText("2", false, 12);
    }
    else if(defconLevel == 3)
    {
        displayColorText("3", false, 14);
    }
    else if(defconLevel == 4)
    {
        displayColorText("4", false, 9);
    }
    else if(defconLevel == 5)
    {
        displayColorText("5", false, 10);
    }
    else
    {
        //Trigger end game screen
    }
    cout << "]" << endl;

    cout << "    >- " << _defconOptions[defconLevel-1] << endl << endl;
    return;
}

//This function is to display the world events
void worldEvent(float& _budgetPercent, string _worldEvents[])
{
    int randomInt; //This represents a random value generated by the program
    float randomFloat; //This represents a random value henerated for change in income budget
    randomInt = (rand()%50); //Get the random event

    cout << endl << endl << "    ===========================================" << endl << "    >- Major International Events Summary (M.I.E.S) -< " << endl;

    if(randomInt - 37 > 0)
    {
        cout << "        + no major events" << endl;
    }
    else if(randomInt - 29 > 0)
    {
        cout << "        + ";
        cout << _worldEvents[(randomInt - 28) % 4 + 6] << endl; //Show world event
    }
    else if(randomInt - 8 > 0)
    {
        cout << "        + ";
        cout << _worldEvents[(randomInt - 7) % 3 + 3] << endl; //Show world event
        cout << "        + Increase US Military Spending by ";
        randomFloat = ((rand()%5+1)/100.0);//Get the random increase in inflation
        cout << randomFloat*100 << "%" << endl; //Display change
        _budgetPercent += randomFloat; //Increase funding
    }
    else
    {
        cout << "        + ";
        cout << _worldEvents[(randomInt + 1) % 3] << endl; //Show world event
        cout << "        + Decrease US Military Spending by ";
        randomFloat = ((rand()%2+1)/100.0);//Get the random decrease in inflation
        cout << randomFloat*100 << "%" << endl; //Display change
        if(_budgetPercent > 0.03) //Make sure you dont have negative funding
        {
            _budgetPercent -= randomFloat; //Decrease funding
        }
    }
    cout << endl << endl << "    ===========================================" << endl;
    return;
}

//This function is for player to choose their building
gameInfo chooseBuilding(gameInfo _gameData, playerData _playerInfo, string _buildingOptions[], string _buildModeOptions[], float& _budget)
{
    int inputValue; //This is used to get the input of the player

    //Output message
    cout << endl << endl << "    ===================================" << endl << "    >- What would you like to build?" << endl;
    displayMenu(_buildingOptions, 3, _playerInfo, _gameData.currentYear, false); //Display all buidling options
    cout << "    >- Each building cost: [" << _gameData.baseCost << "] billion dollars" << endl;

    if(_budget < _gameData.baseCost)
    { //If you do not have enough money, tell player
        displayColorText( "    >- You do not have the funds to build anything| Returning to menu now", true, 4);
    }

    inputValue = getAnswer(3,1); //Get player's input

    if(inputValue != 3 && _budget > _gameData.baseCost)
    {
        system("CLS"); //Wipe console
        if(inputValue == 1)
        { //Call build mode function
            _gameData = buildingMode(_gameData, _playerInfo, _buildModeOptions, '@', _budget);
        }
        else
        { //Call build mode function
            _gameData = buildingMode(_gameData, _playerInfo, _buildModeOptions, '#', _budget);
        }
    }
    return _gameData; //Otherwise, return to main
}

//This function is for the general mode of building
gameInfo buildingMode(gameInfo _gameData, playerData _playerInfo, string _menuOptions[], char _building, float& _budget)
{
    int menuInput = 1; //Integer used to get input from player

    char savedChar = _gameData.gameMap[100][20]; //This represents the temporary character saved
    int currentX = 100; //This represents the current x position of the base
    int currentY = 20; //This represents the current y position of the base

    setSpot(_gameData.gameMap[currentX][currentY], _building); //Set initial spot of the base on the map

    while(menuInput != 4) //Kepp loop running unless quit option is chosen
    {
        _gameData = goThroughMap(_gameData, ' ', false); //Display map
        displayMenu(_menuOptions, 4, _playerInfo, _gameData.currentYear, true); //Display options
        menuInput = getAnswer(4,1); //Get player input

        if(menuInput == 1)
        {
            displayColorText("    >- Use WASD  or Arrow keys to move", true, 4); //Display instructions
            _gameData = keyboardMode(_gameData, currentX, currentY, savedChar, _building); //Call function to place using keyboard
        }
        else if(menuInput == 2)
        {
            _gameData = coordinateMode(_gameData, currentX, currentY, savedChar, _building);  //Call function to place using coordinates
        }
        else if(menuInput == 3)
        {
            cout << endl << "    >- Do you want to confirm this spot to place your item? The change is ";
            displayColorText("permanent", true, 4); //Display message
            if(getConfirmation()) //If player confirms yes to placement, save and exit function
            {
                menuInput = 4; //Trigger quit option
                _budget -= _gameData.baseCost; //Use up money
                if(_building == '@')
                { //If building built is missile silo
                    _gameData.defcon -= 0.1; //Decrease Defcon (increase level)
                }
            }
        }
        else
        {
            cout << endl << "    >- Are you sure you want to quit build mode?";
            if(getConfirmation()) //If player confirms yes to placement, save and exit function
            {
                setSpot(_gameData.gameMap[currentX][currentY], savedChar); //Set spot of map back to saved character before exiting
            }
        }
        system("CLS");
    }
    return _gameData;
}

//This function is for placing base using keyboard
gameInfo keyboardMode(gameInfo _gameData, int& _currentX, int& _currentY, char& _savedChar, char _building)
{
    while(true) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Check this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {
        if((GetKeyState('W') & 0x8000) || (GetKeyState(VK_UP) & 0x8000))
        {
            if((_currentY - 1) >= 5) //Check to see if new position is legal
            {
                _gameData = updatePosition(_gameData, 0, -1, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
        }
        //Else if specific key is pressed:
        else if((GetKeyState('S') & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000))
        {
            if((_currentY + 1) <= 45) //Check to see if new position is legal
            {
                _gameData = updatePosition(_gameData, 0, 1, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
        }
        //Else if specific key is pressed:
        else if((GetKeyState('A') & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000))
        {
            if((_currentX - 1) >= 0) //Check to see if new position is legal
            {
                _gameData = updatePosition(_gameData, -1, 0, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
        }
        //Else if specific key is pressed:
        else if((GetKeyState('D') & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000))
        {
            if((_currentX + 1) <= 199) //Check to see if new position is legal
            {
                _gameData = updatePosition(_gameData, 1, 0, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
        }
        //Else if escape is pressed, exit
        else if((GetKeyState(VK_ESCAPE) & 0x8000))
        {
            system("CLS"); //Wipe console
            return _gameData;
        }
    }
}

//This function is for placing base using a coordinate system
gameInfo coordinateMode(gameInfo _gameData, int& _currentX, int& _currentY, char& _savedChar, char _building)
{
    int tempX; //x position input chosen by player
    int tempY; //y position input chosen by player

    cout << endl << "    >- Please input your x-position between 3 - 198 " << endl;
    tempX = getAnswer(198, 3);

    cout << "    >- Please input your y-position between 3 - 43 " << endl;
    tempY = getAnswer(43, 3);

    _gameData = updatePosition(_gameData, -_currentX + tempX, -_currentY + tempY, false, _currentX, _currentY, _savedChar, _building);
    return _gameData;
}

//This function is for updating the position of the base
gameInfo updatePosition(gameInfo _gameData, int _xChange, int _yChange, bool _usingKeyboard, int& _currentX, int& _currentY, char& _savedChar, char _building)
{
    _gameData.gameMap[_currentX][_currentY] = _savedChar; //Replace current position with the saved character
    _savedChar = _gameData.gameMap[_currentX + _xChange][_currentY + _yChange]; //Save the character of the future value
    _gameData.gameMap[_currentX + _xChange][_currentY + _yChange] = _building; //Replace the future spot with an @ symbol
    _currentX = _currentX + _xChange; //Update current position
    _currentY = _currentY + _yChange;

    if(_usingKeyboard)
    {
        system("CLS"); //Wipe console
        _gameData = goThroughMap(_gameData, ' ', false); //Display map
        displayColorText("    >- Press escape to exit keyboard mode", true, 4); //Output warning/directions on how to exit
    }
    return _gameData; //return
}

//Error trapping funcion that only accepts integers
int getAnswer (int _maxLimit, int _minLimit)
{
    int playerInput; //This variable is used to get the player's input
    bool findingInput; //This bool determines if the loop continues running
    do
    {
        findingInput = false; //By default, the loop will end
        cout << "    >- Your input: "; //Get player input
        cin >> playerInput;
        if(cin.fail())//Check to see if player entered a "bad" input type
        {
            cin.clear(); //Clear all flags
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore incorrect symbols
            displayColorText("  ==================================================", true, 4);
            displayColorText("  >- Please enter a valid input number", true, 12);
            displayColorText("  ==================================================", true, 4);
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if(playerInput > _maxLimit || playerInput < _minLimit ) //Otherwise, print an error message
        {
            displayColorText("  ==================================================", true, 4);
            cout << "  >- Please enter a number between " << _minLimit << " and " << _maxLimit << endl;
            displayColorText("  ==================================================", true, 4);
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}

//Displays the menu
void displayMenu(string _options[], int _arraySize, playerData _data, int _year, bool showInfo)
{
    //Display UI
    cout << "    >- Please enter a direct command. Below are the primary listed commands.                                                  ";
    if(showInfo)
    {
        cout << "[January 1, " << _year << "] <> Current Department Balance: " << _data.currentBalance<< " billion dollars";
    }
    cout << endl;
    //Display instructions
    for(int i = 0; i < _arraySize; i++)
    {
        cout << "    >- [" << i+1 << "] " << _options[i] << endl;
    }
    return;
}

//Displays text in Color
void displayColorText(string _inputOne, bool _returnTrue, int color)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //HANDLE and hCOnsole are using the windows.h lbrary to color individual letters

    SetConsoleTextAttribute(hConsole, color); //Set color to Color
    cout << _inputOne;
    SetConsoleTextAttribute(hConsole, 15); //Set color to white again
    if(_returnTrue)
    {
        cout << endl;
    }
}

//This is an integrated version of getch(); and a message
void anyInput()
{
    cout << "    >- [Press Any Key To Continue]" << endl;
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

    cout << "    >- -UNSC User Management System-" << endl << "    ================================" << endl << "    ________________________________" << endl;
    cout << "    UNSC TacOS  v.337" <<  endl << "    (S) 2294 FLEETCOM" << endl << "    =======================" <<  endl << "    |  User Log:" << endl;
    cout << "    |  >> Administrator (UNSC ID 8384-C)" << endl << "    |  >>> " << "unknown.IDENTIFY_userGroup" << endl << endl;
    cout << "    ________________________________" << endl << "    ================================" << endl << endl << "    >- Please enter your pin and ID" << endl << endl;

    cout << "    >- ID: ";
    cin >> userID;
    cout << "    >- PIN: ";

    //Fake username and password system. Converts all letters into *'s
    ch = _getch();
    while(ch != 13)
    {
        randInput.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout << endl << "    >- \Acess Granted." << endl << "    >- Welcome " << userID << endl;
    anyInput();

    return userID;
}

//This function is to get a boolean response from the player
bool getConfirmation()
{
    int input; //This integer is to get the player's input
    cout << "    >- Type [1] to answer YES. Type [2] to answer NO " << endl; //Output message
    input = getAnswer(2,1); //Get answer from user
    if(input == 1) //If they answer yes, return true
    {
        return true;
    }
    return false; //Otherwise, return false
}
