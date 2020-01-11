/*
>- Author: Max Wong
>- Date: Sep 1, 2019
>- Updated: Jan 11, 2020
>- Purpose: To write a game for a summative project.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 1.5.3]
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [TO DO]

    ////////////////////////////// Goals for today

    >- Advance reactions in scan mode [In progress]
        >- Setting up new sam sites
        >- Make attack options

    ////////////////////////////// Goal for tomorrow

    >- Restricted placement system
        >-Fill map?
        >- Russia
        >- Ocean

    >- National Security Bar
        >- Make other things affect this bar
        >- More nuclear silos increase it
        >- Sam sites, radar stations increase it
        >- enemy planes in north west hemisphere that are not dealt with will increase it

    >- UFO array can't be in struct bug
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
struct Event
{
    int year; //The year at which the event occurs
    string note; //The message that will be displayed
    float effect; //This int represents the impact of the event on your income
};

struct Building
{
    int xPos; //Represents the y position of the building
    int yPos; //Represents the x position of the building
    char savedCharOne; //represents the saved char at the origin of the label
    char savedCharTwo; //represents the saved char beside the first one
};

struct UFO //This struct holds the core data for each UFO spawned in the game
{
    int identity; //This is just for decor, a random 4 digit number
    string tag; //This r  epresents if it is friendly or enemy
    string origin; //This represents where if came from (country)
    string type; //This represents what the ship is
    char symbol; //This is the symbol representing it on the map
    char savedChar; //This represents the char of the original spot of the object
    int xPos; //This represents the x position of the object
    int yPos; //This represents the y position of the object
};

struct PlayerData //This struct holds the data for each player
{
    string playerName;
    float currentGDP; //The US GDP
    float currentIncome; //The % funding for the department
    float currentBalance; //The military budget, how much funding in dollars
    int radarCount; //This keeps track of how many radar's there is
    Building radarData[100]; //This represents the data of each radar
    Building tempLabel[20]; //These are temporary labels in the scan mode just to know what target it which
    int samCount; //This keeps track of how many SAM sites there is
    Building samData[100]; //This represents the data of each SAM site
};

struct GameInfo //This struct holds the core game data
{
    int ufoCount;
    float baseCost; //This is the price of the buildings
    int currentYear; //Year counter
    float defcon; //This is the world tension counter. If it reaches 1, everyone dies
    char gameMap [199][55];//This is the double array that houses the whole map
};

//Delcaring function prototypes
void display(char); //This function is for displaying a single character
void setSpot(char&, char); //This function is to set a specific spot in the map
void goThroughMap(GameInfo&, char, bool); //This function is to go through every spot in the map. It can use other functions to set it all or display it
void getMap(GameInfo&, bool); //This function is used to find each line in the map txt file
void saveMap(std::string, GameInfo&, int); //This function is used to extract each character in a map file line

void endTurn(PlayerData&, float, float&, float&, string[], string[], Event[], int); //This function is in charge of updating the player data for the next turn
void defconCounter(string[], float); //This function is to display the defcon state
void worldEvent(float&, string[], Event[], int); //This function is to display the world events
bool gameOverScreen(GameInfo); //This function is for ending the game
void resetGame(GameInfo&); //This function is for resting game info
void resetPlayer(PlayerData&); //This function is for reseting a player
void setBigEvents(Event[]); //This function is in charge of initializing the large advance events
void checkBigEvents(Event[], int); //This function is called to check for matching advance events to output

void chooseBuilding(GameInfo&, PlayerData&, string[], string[]); //This function is for player to choose their building
void buildingMode(GameInfo&, PlayerData&, string[], char); //This function is for the general mode of building
void keyboardMode(GameInfo&, int&, int&, char&, char); //This function is for placing base using keyboard
void coordinateMode(GameInfo&, int&, int&, char&, char); //This function is for placing base using a coordinate system
void updatePosition(GameInfo&, int, int, bool, int&, int&, char&, char); //This function is for updating the position of the base

int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)
void displayMenu(string[], int, PlayerData, int, bool); //Function to show the menu: All positions are options except last which is reserved for quit number
void displayColorText(string, bool, int); //This function is used to display Color text
void anyInput(); //This is an integrated version of getch(); and a message
string getName(); //This function is used to get the player's name, disguised as the start menu
bool getConfirmation(); //This function is to get a boolean response from the player

void spawnUFO(UFO[], int, string[], string[], char[], GameInfo&); //This function is in charge of spawning all unscanned planes
void setUFO(UFO&, string[], string[], char[], char[199][55]); //This function is in charge of setting the information on the plane
void resetUFOs(UFO[]); //This resets the position of the ufo's
void scanMode(UFO[], GameInfo&, PlayerData&, string[]); //This function is used for all interactions between player and UFO's including a special UI place
void ufoMenu(UFO[], int, GameInfo); //This function is a specialized function to display the ufo scan mode menu. It will be replaced wtih a more versitile menu function later
void ufoScanAll(UFO[], int, PlayerData&, GameInfo&, int); //This function is for actually getting each and everyplane to scan it's surroundings
void ufoScanInd(UFO, int, Building[], GameInfo&, int); //This function is for scanning -> each individual ufo
void placeLabel(PlayerData&, GameInfo&, UFO, int); //This is for placing a label beside a ufo tag
void clearLabel(PlayerData&, GameInfo&); //This is for clearing all labels after exiting scan mode
bool scanRadius(UFO, Building, int); //This function is purely for returning true or false depending on if an object is within the radius

void actionMenu(string[], UFO, Building[], PlayerData); //This function is used to display the possible actions against ufo's

int main()
{
    srand (time(NULL)); //Randomize seed according to time
    //Declaring all variables

    //Declare and initialize game data and playerData
    GameInfo gameData; //This struct represents the important information for the whole game
    PlayerData usa; //This struct represents the important information for player usa
    UFO ufosOnMap[20]; //This is an array containing the information on every ufo on the map
    Event advanceEvents[11]; //These are the big 11 events that happen throughout the 20th century


    //Calling function to reset all (Game and Player) data and UFO data and events data
    resetGame(gameData);
    resetPlayer(usa);
    resetUFOs(ufosOnMap);
    setBigEvents(advanceEvents);

    string primaryOptions[4] = {"Enter building mode","|| Finish Turn >>", "Scan all available UFOs", "Quit"}; //This array represents the optiosn available in the main menu
    string buildingOptions[4] = {"InterContinental Balistic Missile Launch Facility", "Advance Warning Complex [Range: 7]", "Surface to Air Missile Defense Station [Range 10]", "Quit"}; //This represents the available options for buildings
    string buildModeOptions[4] = {"Place using keyboard", "Place using coordinate", "Confirm place", "Cancel/Exit build mode"}; //These are the menu options for build mode
    //These are the five states of DEFCON advance warning
    string defconOptions[5]= {"CRITICAL|| Nuclear War Imminent","SEVERE|| Armed Forces Ready to Deploy in 6 hours","SUBSTANTIAL|| Air Force Mobilizes in 15 Minutes","MODERATE|| Increase Security Readiness","LOW|| Normal Peacetime Readiness"};
    //World events that may or may not change your income/funding
    string worldEvents[10] = {"Funding is re-directed to Boost the Economy","New Governemnt Against-Military","Anti-War Protests are Widespread","Sovites Become More Agresive","New US Government is Pro-Military","Public Opinion Swings Pro-Military","NATO Military Exercise Occurs in Western Europe","Warsaw Pact Meet For Annual Military Sumit","Refugees Continue to Flee Eastern Europe","Civil War Occurs in South America"};

    //String arrays for UFO's
    string origin[13] = {"Soviet","Chinese","South Korea","Sweden","Switzerland","Egypt","Saudi Arabie","Austria", "West Germany", "United States of America", "Canada", "France", "United Kingdom"}; //The origins of enemy and neutral planes
    string type[4] = {"Military","Nuclear","Cargo","Passenger"}; //These represent the possible plane types in the game
    string actionOptions[4] = {"Deploy the airforce, force the aircraft to land", "Radio ufo and order it to land", "Leave the ufo alone", "Set DEFCON to [1], launch all nuclear missiles in a first strike"}; //All options in interaction with ufo's and the world
    char symbols[2] = {'^', '!'}; //Symbols of possible enemy planes

    int menuInput = 1; //This int represents the input taken from user
    while(menuInput != 4)//While player does not choose to quit
    {
        goThroughMap(gameData, ' ', false); //Display map
        displayMenu(primaryOptions, 4, usa, gameData.currentYear, true); //Display all menu options
        menuInput = getAnswer(4,1); //Get player input

        if(menuInput == 1)
        { //If player one enters 1, enter function to choose building and buidl mode
            chooseBuilding(gameData, usa, buildingOptions, buildModeOptions);
        }
        else if(menuInput == 2)
        {
            //Go to end turn function
            if(gameData.defcon - 0.05 <= 1)
            {
                //If gameover trigger is detected
                if(gameOverScreen(gameData))
                {
                    return 0;
                }
                else
                {
                    //Calling function to reset all (Game and Player) data and UFO data
                    resetGame(gameData);
                    resetPlayer(usa);
                    resetUFOs(ufosOnMap);
                }
            }
            else
            {
                gameData.currentYear ++;//Update year
                endTurn(usa, 0, gameData.baseCost, gameData.defcon, defconOptions, worldEvents, advanceEvents, gameData.currentYear); //Calls function to update income

                if(gameData.currentYear % 2 == 0 && gameData.ufoCount < 20)
                {
                    //Caps ufos at 20 and makes sure that fo count is increased every 2 turns
                    gameData.ufoCount ++;
                }
                spawnUFO(ufosOnMap, gameData.ufoCount, origin, type, symbols, gameData); //Call function to spawn all the UFO's
            }
        }
        else if(menuInput == 3)
        {
            //Scan all ufo's
            scanMode(ufosOnMap, gameData, usa, actionOptions);
        }
        else
        {
            //Quit game
            cout << "    >- Are you sure you want to quit?" << endl;
            if(!getConfirmation())
            {
                //Make sure they want to quit
                menuInput = 0;
            }
        }
        system("CLS"); //Cleans console
    }
    cout << "    >- Quitting..." << endl;
    return 0;
}

//This function is for displaying a single character
void display(char _mapSpot)
{
    string tempString; //This string is here temporarily and simply to convert char to string
    if(_mapSpot == '@') //If place is missile silo
    {
        displayColorText("@", false, 6); //yellow color -14, 6
    }
    else if(_mapSpot == '$') //If place is missile silo
    {
        displayColorText("$", false, 6); //yellow color - 14, 6
    }
    else if(_mapSpot == '#') //If place is radar station
    {
        displayColorText("#", false, 2); //Dark green color
    }
    else if(_mapSpot == '!') //If place is enemy
    {
        displayColorText("!", false, 4); //Red color
    }
    else if(_mapSpot == '?') //If place is unknown
    {
        displayColorText("?", false, 9); //Blue color
    }
    else if(_mapSpot == '&') //If place is ally
    {
        displayColorText("&", false, 10); //Light green color
    }
    else if(_mapSpot == '^') //If place is neutral
    {
        displayColorText("^", false, 9); //Blue color
    }
    else if(_mapSpot == '1' || _mapSpot == '2' || _mapSpot == '3' || _mapSpot == '4' || _mapSpot == '5' || _mapSpot == '6' || _mapSpot == '7' || _mapSpot == '8' || _mapSpot == '9' || _mapSpot == '0') //If place is label
    {
        //Else if character is a number, highlight
        tempString = _mapSpot;
        displayColorText(tempString, false, 6); //Blue highlight
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
    _spot = _newValue; //Set referenced spot to input variable
    return;
}

//This function is to set completely clean off the map at the start of the game
void goThroughMap(GameInfo& _gameData, char _clearValue, bool _setMap)
{
    for(int i = 0; i < 55; i++) //Using double for loop, go through entire double array
    {
        for(int j = 0; j < 199; j++)
        {
            if(_setMap)
            { //If _setMap is true, set spot to sent char
                setSpot(_gameData.gameMap[j][i], _clearValue);
            }
            else
            { //Otherwise, output char
                display(_gameData.gameMap[j][i]);
            }
        }
        if(!_setMap)
        { //Skip a line when the line is finished
            cout << endl;
        }
    }
    return;
}

//This function is used to find each line in the map txt file
void getMap(GameInfo& _gameData, bool _saveFile)
{
    std::string line; //String line used to seperate the text file into lines
    ifstream mapFile_("MapFile.txt"); //This is the map file
    ifstream endFile_("NuclearEnding.txt"); //This is the game over file

    int currentRow = 0; //This integer keeps count of the row number for the saving in array

    if(mapFile_.is_open() && _saveFile) //If instricted to save the file
    {
        while(getline(mapFile_,line)) //This function uses the builtin function: getline
        {
            saveMap(line, _gameData, currentRow); //It then references the saveMapFile function in order to save it into a doubel array.
            currentRow += 1;
        }
        mapFile_.close(); //Close file
    }
    else if(endFile_.is_open() && !_saveFile) //Otherwise, if instructed to read out file
    {
        while(getline(endFile_,line)) //This function uses the builtin function: getline
        {
            cout << line << endl; //Find each line and print it out
        }
        endFile_.close(); //Close file
    }
    return;
}

//This function is used to extract each character in a map file line
void saveMap(std::string _line, GameInfo& _gameData, int _currentRow)
{
    for(std::string::size_type i = 0; i < _line.size(); ++i) //Running through every character
    {
        setSpot(_gameData.gameMap[i][_currentRow], _line[i]); //Save spot in double array with specific corresponding char and spot
    }
    return;
}

//This function is in charge of updating the player data for the next turn
void endTurn(PlayerData& _playerData, float _budgetChange, float& _baseCost, float& _defcon, string _defconOptions[], string _worldEvents[], Event _events[], int _year)
{
    float randomValue; //This number is randomly generated
    system("CLS"); //Clear console first
    Sleep(400); //Delay by 0.4 seconds

    _defcon -= 0.05; //Increase defcon naturally
    defconCounter(_defconOptions, _defcon); //Call function to display defcon information

    Sleep(400); //Delay by 0.4 second

    worldEvent(_playerData.currentIncome, _worldEvents, _events, _year); //Call function to display current world issues

    Sleep(400); //Delay by 0.4 second
    cout << endl << endl << "    ===========================================" << endl;

    randomValue = (rand()%5+1)/100.0; //Get the random increase or decrease of the GDP
    if(rand() % 5 == 0 && randomValue < 3 )
    {
        //In decrease (less likely), display percent and update GDP
        cout << "    >- Economy decreased by -> " << randomValue*100 << "%" << endl;
        _playerData.currentGDP -= _playerData.currentGDP*randomValue;
    }
    else
    {
        //In increase (more likely), display percent and update GDP
        cout << "    >- Economy increased by -> " << randomValue*100 << "%" << endl;
        _playerData.currentGDP += _playerData.currentGDP*randomValue;
    }
    //Show new GDP
    cout << "    >- GDP is Now: " << _playerData.currentGDP << " billion dollars" << endl;

    //Change income percent if government changes it
    _playerData.currentIncome += _budgetChange;

    //Update the income of the department
    cout <<_playerData.currentIncome << endl;
    _playerData.currentBalance += (_playerData.currentGDP*_playerData.currentIncome)/100.0;
    cout << "    >- Current Department Anual Budget: " << _playerData.currentBalance << " billion dollars" << endl;


    randomValue = (rand()%3+7)/100.0; //Get the random increase in inflation
    _baseCost += _baseCost*randomValue; //Increase price of buildings

    anyInput();//Get any input before continuing
    return;
}

//This function is to display the defcon state
void defconCounter(string _defconOptions[], float _defcon)
{
    int defconLevel; //This integer represents the rounded defcon level
    defconLevel = round(_defcon); //Round defcon level into the int

    cout << endl << endl << "    >- DEFCON: [";
    if(defconLevel == 1)
    {
        displayColorText("1", false, 4); //If rounded to 1, print in deep red
    }
    else if(defconLevel == 2)
    {
        displayColorText("2", false, 12); //If rounded to 2, print in deep orange
    }
    else if(defconLevel == 3)
    {
        displayColorText("3", false, 14); //If rounded to 3, print in deep yellow
    }
    else if(defconLevel == 4)
    {
        displayColorText("4", false, 9); //If rounded to 4, print in deep blue
    }
    else if(defconLevel == 5)
    {
        displayColorText("5", false, 10); //If rounded to 5, print in deep greem
    }
    cout << "]" << endl;

    cout << "    >- " << _defconOptions[defconLevel-1] << endl << endl; //cout the specefic defcon message for the rounded level
    return;
}

//This function is to display the world events
void worldEvent(float& _budgetPercent, string _worldEvents[], Event _events[], int _year)
{
    int randomInt; //This represents a random value generated by the program
    float randomFloat; //This represents a random value henerated for change in income budget
    randomInt = (rand()%50); //Get the random event

    cout << endl << endl << "    ===========================================" << endl << "    >- Major International Events Summary (M.I.E.S) -< " << endl;

    if(randomInt - 37 > 0) //If event numbergenerated is greater than 37
    {
        cout << "        + no major economic events" << endl;
    }
    else if(randomInt - 29 > 0) //If event numbergenerated is greater than 29
    {
        cout << "        + ";
        cout << _worldEvents[(randomInt - 28) % 4 + 6] << endl; //Show world event
    }
    else if(randomInt - 8 > 0) //If event numbergenerated is greater than 8
    {
        cout << "        + ";
        cout << _worldEvents[(randomInt - 7) % 3 + 3] << endl; //Show world event
        cout << "        + Increase US Military Spending by ";
        randomFloat = ((rand()%5+1)/100.0);//Get the random increase in inflation
        cout << randomFloat*100 << "%" << endl; //Display change
        _budgetPercent += randomFloat; //Increase funding
    }
    else //Otherwise
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

    checkBigEvents(_events, _year);//Check for any big events to display
    return;
}

//This function is for ending the game
bool gameOverScreen(GameInfo _data)
{
    system("CLS"); //Wipe consol
    getMap(_data, false); //Print game over screen
    cout << endl << endl << "            =========================================================================================================================" << endl;
    cout << "            >- GAMEOVER: The world has ended by nuclear war. At your hands, billions have died. There really is no winning is there?" << endl;
    cout << "            >- Maybe you can be the savior that this world needs, and change it for the better. Stay DETERMINED" << endl;
    cout << "               >- Would you like to play again?" << endl << "            ";
    if(getConfirmation()) //If they want to play again: return false
    {
        return false;
    }
    return true; //Else, return true
}

//This function is for resting game info
void resetGame(GameInfo& _data)
{
    _data.currentYear = 1945; //Set the starting year to 1945
    _data.baseCost = 0.1; //Set the starting cost of buildings to 0.1 billion dollars
    _data.defcon = 5; //Set defcon by default to 5
    getMap(_data, true); //Initialize the value of the map array //error
    _data.ufoCount = 0; //Set amount of ufo's in the sky to 0
    return;
}

//This function is for reseting a player
void resetPlayer(PlayerData& _data)
{
    _data.currentGDP = 2000; //The stating US GDP is 2 trillion
    _data.currentIncome = 0.01; //The starting military funding is 0.01%
    _data.currentBalance = 0.5; //The current military balance is 500 million dollars
    _data.playerName = getName(); //Initialize name by using the loading screen
    _data.radarCount = 0; //By default, set radar count to 0
    _data.samCount = 0; //By default, set radar count to 0
    return;
}

//This function is in charge of initializing the large advance events
void setBigEvents(Event _events[])
{
    string tempString; //This is a temporary string to try resolving the save string -> crash bug
    //Set event for 1946
    tempString = "The year is 1946. Only one year ago, the worlds largest war ended. Only one year ago, the Atmoic age was born";
    _events[0].year = 1946;
    _events[0].note = tempString;
    //Set event for 1950
    tempString = "1950: War ignites on the Korean peninsula as the North Korean army crosses the 38th parallel.";
    _events[1].year = 1950;
    _events[1].note = tempString;
    //Set event for 1955
    tempString = "1955: President Kenedy announces the end goal for the US space program, the moon.";
    _events[2].year = 1955;
    _events[2].note = tempString;
    //Set event for 1956
    tempString = "1956: Widespread fighting spreads across Budapest and the surrounding cities as Hungarian revolutionaries fight a Soviet national army.";
    _events[3].year = 1956;
    _events[3].note = tempString;
    //Set event for 1960
    tempString = "1960: An american U-2 recon plane is shot down over soviet airspace.";
    _events[4].year = 1960;
    _events[4].note = tempString;
    //Set event for 1962
    tempString = "1962: Nuclear missile silo's are discovered in soviet backed Cuba. US navy start a blockade.";
    _events[5].year = 1962;
    _events[5].note = tempString;
    //Set event for 1965
    tempString = "1965: The SDC organizes a large scale march on washington DC against intervention in Vietnam.";
    _events[6].year = 1965;
    _events[6].note = tempString;
    //Set event for 1979
    tempString = "1979: The Soviet Union military begins a military operation to support the communist government in Afghanistan.";
    _events[7].year = 1979;
    _events[7].note = tempString;
    //Set event for 1986
    tempString = "1986: Soviet submarine K-219 is sunk with it's full crew during a training exercise accident.";
    _events[8].year = 1986;
    _events[8].note = tempString;
    //Set event for 1986
    tempString = "1986: The Chernobyl nuclear power plant near the city of Pripyat has a nuclear meltdown.";
    _events[9].year = 1986;
    _events[9].note = tempString;
    //Set event for 1991
    tempString = "1991: The Berlin wall has fallen. After 40 years, the curtain between the west and the east has finally opened.";
    _events[10].year = 1991;
    _events[10].note = tempString;
    return;
}

//This function is called to check for matching advance events to output
void checkBigEvents(Event _events[], int _year)
{
    for(int i = 0; i < 11; i++ )
    {
        if(_events[i].year == _year)
        {
            cout <<"        + " << _events[i].note << endl;
        }
    }
    return;
}

//This function is for player to choose their building
void chooseBuilding(GameInfo& _gameData, PlayerData& _playerInfo, string _buildingOptions[], string _buildModeOptions[])
{
    int inputValue; //This is used to get the input of the player

    //Output message
    cout << endl << endl << "    ===================================" << endl << "    >- What would you like to build?" << endl;
    displayMenu(_buildingOptions, 4, _playerInfo, _gameData.currentYear, false); //Display all buidling options
    cout << "    >- Each building cost: [" << _gameData.baseCost << "] billion dollars" << endl;

    if(_playerInfo.currentBalance < _gameData.baseCost)
    {
        //If you do not have enough money, tell player
        displayColorText( "    >- You do not have the funds to build anything| Returning to menu now", true, 4);
    }

    inputValue = getAnswer(4,1); //Get player's input

    if(inputValue != 4 && _playerInfo.currentBalance > _gameData.baseCost)
    {
        system("CLS"); //Wipe console
        if(inputValue == 1)
        {
            //Call build mode function for silo
            buildingMode(_gameData, _playerInfo, _buildModeOptions, '@');
        }
        else if(inputValue == 2)
        {
            //Call build mode function radar
            buildingMode(_gameData, _playerInfo, _buildModeOptions, '#');
        }
        else if(inputValue == 3)
        {
            //Call build mode function SAM site
            buildingMode(_gameData, _playerInfo, _buildModeOptions, '$');
        }
    }
    return; //Otherwise, return to main
}

//This function is for the general mode of building
void buildingMode(GameInfo& _gameData, PlayerData& _playerInfo, string _menuOptions[], char _building)
{
    int menuInput = 1; //Integer used to get input from player

    char savedChar = _gameData.gameMap[100][20]; //This represents the temporary character saved
    int currentX = 100; //This represents the current x position of the base
    int currentY = 20; //This represents the current y position of the base

    setSpot(_gameData.gameMap[currentX][currentY], _building); //Set initial spot of the base on the map

    while(menuInput != 4) //Kepp loop running unless quit option is chosen
    {
        goThroughMap(_gameData, ' ', false); //Display map
        displayMenu(_menuOptions, 4, _playerInfo, _gameData.currentYear, true); //Display options
        menuInput = getAnswer(4,1); //Get player input

        if(menuInput == 1)
        {
            displayColorText("    >- Use WASD  or Arrow keys to move", true, 4); //Display instructions
            keyboardMode(_gameData, currentX, currentY, savedChar, _building); //Call function to place using keyboard
        }
        else if(menuInput == 2)
        {
            coordinateMode(_gameData, currentX, currentY, savedChar, _building);  //Call function to place using coordinates
        }
        else if(menuInput == 3)
        {
            cout << endl << "    >- Do you want to confirm this spot to place your item? The change is ";
            displayColorText("permanent", true, 4); //Display message
            if(getConfirmation()) //If player confirms yes to placement, save and exit function
            {
                menuInput = 4; //Trigger quit option
                _playerInfo.currentIncome -= _gameData.baseCost; //Use up money
                if(_building == '@')
                {
                    //If building built is missile silo
                    _gameData.defcon -= 0.1; //Decrease Defcon (increase level)
                }
                else if(_building == '#')
                { //if player chose to build a radar station
                    _playerInfo.radarData[_playerInfo.radarCount].xPos = currentX; //Save the position of the radar - x
                    _playerInfo.radarData[_playerInfo.radarCount].yPos = currentY; //Save the position fo the radar - y
                    _playerInfo.radarCount ++; //Update the fact that +1 radar has been added
                }
                else if(_building == '$')
                { //If player chose to build a sam site
                    _playerInfo.samData[_playerInfo.samCount].xPos = currentX; //Save the position of the sam - x
                    _playerInfo.samData[_playerInfo.samCount].yPos = currentY; //Save the position fo the sam - y
                    _playerInfo.samCount ++; //Update the fact that +1 sam has been added
                    _gameData.defcon -= 0.05; //Decrease Defcon (increase level)
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
    return;
}

//This function is for placing base using keyboard
void keyboardMode(GameInfo& _gameData, int& _currentX, int& _currentY, char& _savedChar, char _building)
{
    //If escape is pressed, exit
    while((!(GetKeyState(VK_ESCAPE) & 0x8000)))
    {
        if((GetKeyState('W') & 0x8000) || (GetKeyState(VK_UP) & 0x8000))
        {
            if((_currentY - 1) >= 5) //Check to see if new position is legal
            {
                updatePosition(_gameData, 0, -1, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
        }
        //Else if specific key is pressed:
        else if((GetKeyState('S') & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000))
        {
            if((_currentY + 1) <= 45) //Check to see if new position is legal
            {
                updatePosition(_gameData, 0, 1, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
        }
        //Else if specific key is pressed:
        else if((GetKeyState('A') & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000))
        {
            if((_currentX - 1) >= 0) //Check to see if new position is legal
            {
                updatePosition(_gameData, -1, 0, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
        }
        //Else if specific key is pressed:
        else if((GetKeyState('D') & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000))
        {
            if((_currentX + 1) <= 199) //Check to see if new position is legal
            {
                updatePosition(_gameData, 1, 0, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
        }
    }
    system("CLS"); //Wipe console
    return;
}

//This function is for placing base using a coordinate system
void coordinateMode(GameInfo& _gameData, int& _currentX, int& _currentY, char& _savedChar, char _building)
{
    int tempX; //x position input chosen by player
    int tempY; //y position input chosen by player

    cout << endl << "    >- Please input your x-position between 3 - 198 " << endl;
    tempX = getAnswer(198, 3); //Show range on x-axis. Get input

    cout << "    >- Please input your y-position between 3 - 43 " << endl;
    tempY = getAnswer(43, 3); //Show range in y axis. Get input

    updatePosition(_gameData, -_currentX + tempX, -_currentY + tempY, false, _currentX, _currentY, _savedChar, _building); //Set new position of the building
    return;
}

//This function is for updating the position of the base
void updatePosition(GameInfo& _gameData, int _xChange, int _yChange, bool _usingKeyboard, int& _currentX, int& _currentY, char& _savedChar, char _building)
{
    _gameData.gameMap[_currentX][_currentY] = _savedChar; //Replace current position with the saved character
    _savedChar = _gameData.gameMap[_currentX + _xChange][_currentY + _yChange]; //Save the character of the future value
    _gameData.gameMap[_currentX + _xChange][_currentY + _yChange] = _building; //Replace the future spot with an @ symbol
    _currentX = _currentX + _xChange; //Update current position
    _currentY = _currentY + _yChange;

    if(_usingKeyboard)
    {
        system("CLS"); //Wipe console
        goThroughMap(_gameData, ' ', false); //Display map
        displayColorText("    >- Press escape to exit keyboard mode", true, 4); //Output warning/directions on how to exit
    }
    return; //return
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
    }
    while(findingInput);
    return playerInput;//Otherwise input is good, return input
}

//Displays the menu
void displayMenu(string _options[], int _arraySize, PlayerData _data, int _year, bool showInfo)
{
    //Display UI
    cout << "    >- Please enter a direct command. Below are the primary listed commands.                                                  ";
    if(showInfo)
    {
        cout << "[January 1, " << _year << "] <> Current Department Balance: " << _data.currentBalance<< " billion dollars";
    }
    cout << endl;
    //Display instructions
    for(int i = 0; i < _arraySize; i++) //For every option, display with number indicator
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
    { //If instructed, skip a line
        cout << endl;
    }
}

//This is an integrated version of getch(); and a message
void anyInput()
{
    cout << "    >- [Press Any Key To Continue]" << endl;
    getch(); //Get any input before continuing and returning
    return;
}

//This function is used to get the player's name, disguised as the start menu
string getName()
{
    //Defining the variables
    string userID = "unknown"; //This represents the username
    string randInput = ""; //This represents the password inputted by the user
    char ch; //This is used to get each individual input

    system("CLS"); //Wiping consol
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
    cout << endl << "    >- \Acess Granted." << endl << "    >- Welcome " << userID << endl; //Show user information before continuing
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

//This function is in charge of spawning all unscanned planes
void spawnUFO(UFO _ufosData[], int _ufoCount, string _origin[], string _type[], char _symbol[], GameInfo& _gameData)
{
    for(int i = 0; i < _ufoCount; i++) //Spawn all planes
    {
        setUFO(_ufosData[i], _origin, _type, _symbol, _gameData.gameMap); //Call function to make a new plane
    }
    return;
}

//This function is in charge of setting the information on the plane
void setUFO(UFO& _ufoData, string _origin[], string _type[], char _symbol[], char _gameMap[199][55])
{
    int randValue; //This represents a random value
    randValue = rand() % 10; //Determine random number to find out what allegiance is the plane

    //Get rid of the previous ufo and reset it to (reuse it) for a new ufo
    setSpot(_gameMap[_ufoData.xPos][_ufoData.yPos], _ufoData.savedChar);

    _ufoData.identity = rand() % 9999; //Generate random identity

    if(randValue - 7 > 0)
    {
        _ufoData.tag = "Neutral"; //GIve tag as neutral
        _ufoData.origin = _origin[rand() % 11 + 2]; //Generate the random neutral origin country
        _ufoData.type = _type[rand()%2 + 2]; //Generate type -> neutral
        _ufoData.symbol = '^'; //Set symbol as neutral
    }
    else if(randValue - 3 > 0)
    {
        _ufoData.tag = "Friendly"; //Give tag as friendly
        _ufoData.origin = "NATO Ally"; //All friendly belong to NATO
        _ufoData.type = _type[rand()%2]; //Generate type -> Agressive
        _ufoData.symbol = '&'; //Set symbol as ally
    }
    else
    {
        _ufoData.tag = "Enemy"; //Give tag as enemy
        _ufoData.origin = _origin[(rand() % 3) % 2]; //Generate the random enemy origin country
        randValue = (rand()%7 + 2) % 4; //Generate the type of plane -> Neutral or Enemy?
        _ufoData.type = _type[randValue]; //Take integer and set the type of the plane
        if(randValue == 1 || randValue == 2) //Give custom symbol depending of if plane is neutral enemy or agressive enemy
        {
            _ufoData.symbol = '!'; //Agressive
        }
        else
        {
            _ufoData.symbol = '^'; //Neutral
        }
    }
    _ufoData.xPos = rand()%198; //Get the random x position
    _ufoData.yPos = rand()%47 + 3; //Get the random y position
    setSpot(_ufoData.savedChar, _gameMap[_ufoData.xPos][_ufoData.yPos]); //Save the character on the map of the UFO before updating map

    //Now that ufo data is saved, update map data
    setSpot(_gameMap[_ufoData.xPos][_ufoData.yPos], '?');

    return;
}

//This resets the position of the ufo's
void resetUFOs(UFO _ufos[])
{
    for(int i = 0; i < 20; i++) //For every ufo
    {
        _ufos[i].xPos = 0; //Reset x position to 0
        _ufos[i].yPos = 0; //Reset y position to 0
    }
    return;
}

//This function is used for all interactions between player and UFO's including a special UI place
void scanMode(UFO _ufos[], GameInfo& _gameData, PlayerData& _playerData, string _actionOptions[])
{
    int inputValue = 0;
    ufoScanAll(_ufos, _gameData.ufoCount, _playerData, _gameData, 7); //Scan all the possible ufo's

    while(inputValue <= _gameData.ufoCount)
    {
        system("CLS"); //wipe consol
        goThroughMap(_gameData, ' ', false); //Display map
        ufoMenu(_ufos, _gameData.ufoCount, _gameData); //Call function to display menu
        inputValue = getAnswer(_gameData.ufoCount+1, 1); //Get player's input
        cout << endl; //Skip a space

        if(inputValue == _gameData.ufoCount + 1)
        {
            clearLabel(_playerData, _gameData);
        }
        else //If the input si valid
        {
            if(_gameData.gameMap[_ufos[inputValue - 1].xPos][_ufos[inputValue - 1].yPos] == '?')
            { //If the spot of the ufo selected is still undetected, show unscan version of information
                cout << "    >- |IDENTITY| -- unknown" << endl; //Show that everything (all info) is unknown until scanned
                cout << "    >- |TAG| ------- unknown" << endl;
                cout << "    >- |ORIGINS| --- unknown.country" << endl;
                cout << "    >- |SYMBOL| ---- ?" << endl;
            }
            else
            { //Otherwise, the ufo has been scanned, show available information
                cout << "    >- |IDENTITY| -- " << _ufos[inputValue - 1].type << "." << _ufos[inputValue - 1].identity << endl;
                cout << "    >- |TAG| ------- " << _ufos[inputValue - 1].tag << endl;
                cout << "    >- |ORIGINS| --- " << _ufos[inputValue - 1].origin << ".country" << endl;
                cout << "    >- |SYMBOL| ---- " << _ufos[inputValue - 1].symbol << endl;
            }
            cout << endl; //Skip a space
            actionMenu(_actionOptions, _ufos[inputValue-1], _playerData.samData, _playerData);
        }
        anyInput(); //Get any getch before continuing
    }
    system("CLS");
    return;
}

//This function is a specialized function to display the ufo scan mode menu. It will be replaced wtih a more versitile menu function later
void ufoMenu(UFO _ufos[], int _limit, GameInfo _gameData)
{
    for(int i = 0; i < _limit; i++)
    {
        cout << "    >- [" << i+1 << "] ";

        if(i < 9)
        { //If the number is 1 digit
            cout << " "; //Add an extra space
        }

        //For every UFO, find the tag and save it to the array
        if(_ufos[i].tag == "Enemy" && _gameData.gameMap[_ufos[i].xPos][_ufos[i].yPos] != '?')
        { //If tag found is enemy
            displayColorText(_ufos[i].tag, true, 12); //Color tag as red
        }
        else if(_ufos[i].tag == "Friendly" && _gameData.gameMap[_ufos[i].xPos][_ufos[i].yPos] != '?')
        { //If tag found is green
            displayColorText(_ufos[i].tag, true, 10); //
        }
        else if(_gameData.gameMap[_ufos[i].xPos][_ufos[i].yPos] != '?')
        { //otherwise, just show tag if neutral
            cout << _ufos[i].tag << endl;
            //displayColorText(_ufos[i].tag, true, 9);
        }
        else
        { //If unknown, say that tag is unknown
            cout << "Unknown" << endl;
            //displayColorText("Unknown", true, 9);
        }
    }
    cout << "    >- [" << _limit + 1 << "]  To Exit Scan Mode" << endl; //Show option to exit scan mode

    if(_limit == 0)
    {
        //If there are no UFO's, notify player
        cout << "    >- Sorry, no UFO's detected" << endl;
    }
    return;
}

//This function is for actually getting each plane to scan it's surroundings
void ufoScanAll(UFO _ufos[], int _limit, PlayerData& _playerData, GameInfo& _gameData, int _radius)
{
    for(int i = 0; i < _limit; i++)
    {
        //For every UFO, scan for surrounding radar stations
        ufoScanInd( _ufos[i], _playerData.radarCount, _playerData.radarData, _gameData, _radius);
        placeLabel(_playerData, _gameData, _ufos[i], i);
    }
    return;
}

//This function is for scanning -> each individual ufo
void ufoScanInd(UFO _ufo, int _buildingCount, Building _buildObject[], GameInfo& _gameData, int _radius)
{
    for(int i = 0; i < _buildingCount; i++) //For every radar station
    {
        if(scanRadius(_ufo, _buildObject[i], _radius))
        { //Have plane check to see if a radar station is in range. If yes:
            setSpot(_gameData.gameMap[_ufo.xPos][_ufo.yPos], _ufo.symbol); //Set spot on map to symbol (reveal information)
        }
    }
    return;
}

//This is for placing a label beside a ufo tag
void placeLabel(PlayerData& _playerData, GameInfo& _gameData, UFO _ufo, int _ufoNumber)
{
    char tempChar; //This is a temporary character to be used to convert the _ufoNumber to char
    if(_ufo.xPos - 2 >= 0 && _gameData.gameMap[_ufo.xPos - 1][_ufo.yPos] != '!' && _gameData.gameMap[_ufo.xPos - 1][_ufo.yPos] != '@' && _gameData.gameMap[_ufo.xPos - 1][_ufo.yPos] != '#' && _gameData.gameMap[_ufo.xPos - 1][_ufo.yPos] != '^' && _gameData.gameMap[_ufo.xPos - 1][_ufo.yPos] != '&' && _gameData.gameMap[_ufo.xPos - 1][_ufo.yPos] != '?' && _gameData.gameMap[_ufo.xPos - 1][_ufo.yPos] != '$' && _gameData.gameMap[_ufo.xPos - 2][_ufo.yPos] != '!' && _gameData.gameMap[_ufo.xPos - 2][_ufo.yPos] != '@' && _gameData.gameMap[_ufo.xPos - 2][_ufo.yPos] != '#' && _gameData.gameMap[_ufo.xPos - 2][_ufo.yPos] != '^' && _gameData.gameMap[_ufo.xPos - 2][_ufo.yPos] != '&' && _gameData.gameMap[_ufo.xPos - 2][_ufo.yPos] != '?' && _gameData.gameMap[_ufo.xPos - 2][_ufo.yPos] != '$')
    {
        //Check to make sure the label won't be out of the map or that the label will cover something 1 point to the left of it
        _playerData.tempLabel[_ufoNumber].xPos = _ufo.xPos - 2; //Save the label's new x position
        _playerData.tempLabel[_ufoNumber].yPos = _ufo.yPos; //Save the label's new y position
    }
    else if(_ufo.xPos + 2 <= 198 && _gameData.gameMap[_ufo.xPos + 1][_ufo.yPos] != '!' && _gameData.gameMap[_ufo.xPos + 1][_ufo.yPos] != '@' && _gameData.gameMap[_ufo.xPos + 1][_ufo.yPos] != '#' && _gameData.gameMap[_ufo.xPos + 1][_ufo.yPos] != '^' && _gameData.gameMap[_ufo.xPos + 1][_ufo.yPos] != '&' && _gameData.gameMap[_ufo.xPos + 1][_ufo.yPos] != '?' && _gameData.gameMap[_ufo.xPos + 1][_ufo.yPos] != '$' && _gameData.gameMap[_ufo.xPos + 2][_ufo.yPos] != '!' && _gameData.gameMap[_ufo.xPos + 2][_ufo.yPos] != '@' && _gameData.gameMap[_ufo.xPos + 2][_ufo.yPos] != '#' && _gameData.gameMap[_ufo.xPos + 2][_ufo.yPos] != '^' && _gameData.gameMap[_ufo.xPos + 2][_ufo.yPos] != '&' && _gameData.gameMap[_ufo.xPos + 2][_ufo.yPos] != '?' && _gameData.gameMap[_ufo.xPos + 2][_ufo.yPos] != '$')
    {
        //Check to make sure the label won't be out of the map or that the label will cover something 1 point to the right of it
        _playerData.tempLabel[_ufoNumber].xPos = _ufo.xPos + 1; //Save the label's new x position
        _playerData.tempLabel[_ufoNumber].yPos = _ufo.yPos; //Save the label's new y position
    }
    else
    {
        //In the small likelyhood of reaching this point:
        _playerData.tempLabel[_ufoNumber].xPos = _ufo.xPos; //Save the label's new x position
        _playerData.tempLabel[_ufoNumber].yPos = _ufo.yPos + 1; //Save the label's new y position
    }
    //Save the char on the map 'behind' the label and adjacent to the origins of the label position
    _playerData.tempLabel[_ufoNumber].savedCharOne = _gameData.gameMap[_playerData.tempLabel[_ufoNumber].xPos][_playerData.tempLabel[_ufoNumber].yPos];
    _playerData.tempLabel[_ufoNumber].savedCharTwo = _gameData.gameMap[_playerData.tempLabel[_ufoNumber].xPos + 1][_playerData.tempLabel[_ufoNumber].yPos];


    //Save the first digit
    tempChar = '0' + ((_ufoNumber + 1) % 10); //Convert int to char
    //Save the first digit of the _ufoNumber to the map
    setSpot(_gameData.gameMap[_playerData.tempLabel[_ufoNumber].xPos + 1][_playerData.tempLabel[_ufoNumber].yPos], tempChar);

    //Save the second digit
    tempChar = '0' + ((_ufoNumber + 1 - ((_ufoNumber + 1) % 10))/10); //Convert int to char
    //Save the second digit of the _ufoNumber to the map
    setSpot(_gameData.gameMap[_playerData.tempLabel[_ufoNumber].xPos][_playerData.tempLabel[_ufoNumber].yPos], tempChar);

    return;
}

//This is for clearing all labels after exiting scan mode
void clearLabel(PlayerData& _playerData, GameInfo& _gameData)
{
    for(int i = 0; i < _gameData.ufoCount; i++)
    { //Go through every possible ufo labels and replace them with their saved char's
        setSpot(_gameData.gameMap[_playerData.tempLabel[i].xPos][_playerData.tempLabel[i].yPos], _playerData.tempLabel[i].savedCharOne);
        setSpot(_gameData.gameMap[_playerData.tempLabel[i].xPos + 1][_playerData.tempLabel[i].yPos], _playerData.tempLabel[i].savedCharTwo);
    }
    return;
}

//This function is purely for returning true or false depending on if an object is within the radius
bool scanRadius(UFO _ufo, Building _buildObject, int _radius)
{
    if(_ufo.xPos - _buildObject.xPos < _radius && _ufo.xPos - _buildObject.xPos > -_radius && _ufo.yPos - _buildObject.yPos < _radius && _ufo.yPos - _buildObject.yPos > -_radius)
    { //Have plane check to see if a radar station is in range. If yes:
        return true;
    }
    return false;
}

//This function is used to display the possible actions against ufo's
void actionMenu(string _actionOption[], UFO _ufo, Building _buildObject[], PlayerData _playerData)
{
    int userInput; //this is an integer used to get player input
    bool tempBool = false; //Temporary boolean that is true when sam site is in range

    displayMenu(_actionOption, 4, _playerData, 1945, false);
    for(int i = 0;  i < _playerData.samCount; i++)
    {
        if(scanRadius(_ufo, _buildObject[i], 10))
        {
            tempBool = true; //Found a sam site, set to true
        }
    }
    if(tempBool)
    {
        cout << "    >- [5] local SAM site in range. Launch intercepter missile." << endl;
    }

    userInput = getAnswer(5, 1);

    if(userInput == 1)
    {

    }

    return;
}
