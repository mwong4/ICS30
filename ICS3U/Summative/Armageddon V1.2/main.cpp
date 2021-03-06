/*
>- Author: Max Wong
>- Date: Sep 1, 2019
>- Updated: May 9, 2020
>- Purpose: To write a game for a summative project.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 1.8.4]
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [Playtest Counter: 4]
>-
>- Thanks to the following people for play testing
    >- Thanks Mohammed Al-Anezi!
    >- Thanks Tieran Chan!
    >- Thanks Jacob Kim!
    >- Thanks Alain Xu
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
    string tag; //This represents if it is friendly or enemy
    string origin; //This represents where if came from (country)
    string type; //This represents what the ship is
    char symbol; //This is the symbol representing it on the map
    char savedChar; //This represents the char of the original spot of the object
    int xPos; //This represents the x position of the object
    int yPos; //This represents the y position of the object
    bool undetected; //If place is shot down, set bool to true
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

    bool buildTutorial; //This starts false because the user has not seen the build tutorial. Sets to true once they have
    bool scanTutorial; //This starts false because the user has not seen the scan tutorial. Sets to true once they have
};

struct GameInfo //This struct holds the core game data
{
    int ufoCount;
    float baseCost; //This is the price of the buildings
    int currentYear; //Year counter
    float defcon; //This is the world tension counter. If it reaches 1, everyone dies
    char gameMap [199][50];//This is the double array that houses the whole map
    bool endGame; //This bool determines if we should close the game or not
    float nationalSecurity; //This float represents the security of the nation. If it reaches 0, game ends
};

//Delcaring function prototypes
void display(char); //This function is for displaying a single character
void setSpot(char&, char); //This function is to set a specific spot in the map
void goThroughMap(GameInfo&, char, bool); //This function is to go through every spot in the map. It can use other functions to set it all or display it
void getMap(GameInfo&, int); //This function is used to find each line in the map txt file
void saveMap(std::string, GameInfo&, int); //This function is used to extract each character in a map file line

void endTurn(PlayerData&, float, string[], string[], Event[], GameInfo&, UFO[]); //This function is in charge of updating the player data for the next turn
void defconCounter(string[], float); //This function is to display the defcon state
void worldEvent(float&, string[], Event[], int); //This function is to display the world events
bool gameOverScreen(GameInfo, string); //This function is for ending the game
bool winGameScreen(GameInfo); //This function is called to show the user that they have "won"
void resetGame(GameInfo&); //This function is for resting game info
void resetPlayer(PlayerData&); //This function is for reseting a player
void setBigEvents(Event[]); //This function is in charge of initializing the large advance events
void checkBigEvents(Event[], int); //This function is called to check for matching advance events to output
void displaySecurity(float); //This function displays the national security of the nation

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
void setUFO(UFO&, string[], string[], char[], char[199][50]); //This function is in charge of setting the information on the plane
void resetUFOs(UFO[]); //This resets the position of the ufo's
void scanMode(UFO[], GameInfo&, PlayerData&, string[]); //This function is used for all interactions between player and UFO's including a special UI place
void ufoMenu(UFO[], int, GameInfo); //This function is a specialized function to display the ufo scan mode menu. It will be replaced wtih a more versitile menu function later
void ufoScanAll(UFO[], int, PlayerData&, GameInfo&, int); //This function is for actually getting each and everyplane to scan it's surroundings
void ufoScanInd(UFO, int, Building[], GameInfo&, int); //This function is for scanning -> each individual ufo
void placeLabel(PlayerData&, GameInfo&, UFO, int); //This is for placing a label beside a ufo tag
void clearLabel(PlayerData&, GameInfo&); //This is for clearing all labels after exiting scan mode
bool scanRadius(UFO, Building, int); //This function is purely for returning true or false depending on if an object is within the radius

void actionMenu(string[], UFO&, Building[], PlayerData, GameInfo&); //This function is used to display the possible actions against ufo's
void launchNukes(GameInfo&); //This is one of the game's endings, if you choose to launch all nukes
void launchSAM(int, GameInfo&, UFO&); //This will initiate the launch of a SAM against ufo's
bool inArea(int, int, int, int, int, int); //This function is in charge of finding out if a ufo is in a certain map area
void securityPenalty(GameInfo&, UFO[]); //This is for updating the penalty given to the player in secuirty every turn
void radioPlane(GameInfo&, UFO&); //This function is for the passive attack option of radioing the plane

void tutorial(GameInfo); //This function is shown to teach the game

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

    string primaryOptions[2] = {"Enter building mode", "Scan all available UFOs"}; //This array represents the optiosn available in the main menu
    string buildingOptions[4] = {"Nuclear Missile (ICBM)", "Radar Station (AWCC) [Range: 10]", "Interceptor Missile (SAMDS) [Range 15]", "Quit"}; //This represents the available options for buildings
    string buildModeOptions[4] = {"Place using keyboard", "Place using coordinate", "Confirm place", "Cancel/Exit build mode"}; //These are the menu options for build mode
    //These are the five states of DEFCON advance warning
    string defconOptions[5]= {"CRITICAL|| Nuclear War Imminent","SEVERE|| Armed Forces Ready to Deploy in 6 hours","SUBSTANTIAL|| Air Force Mobilizes in 15 Minutes","MODERATE|| Increase Security Readiness","LOW|| Normal Peacetime Readiness"};
    //World events that may or may not change your income/funding
    string worldEvents[10] = {"Funding is re-directed to Boost the Economy","New Governemnt Against-Military","Anti-War Protests are Widespread","Sovietss Become More Aggresive","New US Government is Pro-Military","Public Opinion Swings Pro-Military","NATO Military Exercise Occurs in Western Europe","Warsaw Pact Meet For Annual Military Sumit","Refugees Continue to Flee Eastern Europe","Civil War Occurs in South America"};

    //String arrays for UFO's
    string origin[13] = {"Soviet","Chinese","South Korea","Sweden","Switzerland","Egypt","Saudi Arabie","Austria", "West Germany", "United States of America", "Canada", "France", "United Kingdom"}; //The origins of enemy and neutral planes
    string type[4] = {"Military","Nuclear","Cargo","Passenger"}; //These represent the possible plane types in the game
    string actionOptions[3] = {"Radio ufo and order it to land", "Leave the ufo alone", "Set DEFCON to [1], launch all nuclear missiles in a first strike"}; //All options in interaction with ufo's and the world
    char symbols[2] = {'^', '!'}; //Symbols of possible enemy planes

    int menuInput = 1; //This int represents the input taken from user
    string gameOverMessage = ""; //This is a message that will be displayed by the game over screen

    //Offer the user the tutorial
    cout << endl << "    >- Would you like to view the tutorial?" << endl;
    if(getConfirmation())
    { //If user says yes
        tutorial(gameData); //Call function to display tutorial
    }
    else
    { //Otherwise
        usa.scanTutorial = true; //Set the tutorial off
        usa.buildTutorial = true; //Set the tutorial off
    }

    while(menuInput != 4)//While player does not choose to quit
    {
        if(!gameData.endGame) //If game has not ended yet
        {
            goThroughMap(gameData, ' ', false); //Display map
            displayMenu(primaryOptions, 2, usa, gameData.currentYear, true); //Display all menu options
            cout << "    >- [3] "; //Display number 3
            displayColorText("|| Finish Turn >>", true, 10); //Display end turn in green color
            cout << "    >- [4] "; //Display number 4
            displayColorText("Quit Game", true, 4); //Display quit game in red
            menuInput = getAnswer(4,1); //Get player input
        }
        else //Otherwise, initiate ending/game over
        {
            menuInput = 3;
        }

        if(menuInput == 1)
        { //If player one enters 1, enter function to choose building and buidl mode
            chooseBuilding(gameData, usa, buildingOptions, buildModeOptions);
        }
        else if(menuInput == 2)
        {
            //Scan all ufo's
            scanMode(ufosOnMap, gameData, usa, actionOptions);
        }
        else if(menuInput == 3)
        {
            //Go to end game function
            if(gameData.defcon - 0.05 <= 1 || gameData.nationalSecurity <= 0.4)
            { //If game over condition is detected
                system("CLS"); //Wipe console
                if(gameData.nationalSecurity <= 0.4) //If gameover was triggered by national security, let player know
                { //If the person lost by national security, let user know by setting this output char and sending it to the function
                    gameOverMessage = "By letting National Security drop too low, you have convinced the soviets to launch a first strike";
                }

                if(gameOverScreen(gameData, gameOverMessage))
                { //If quit trigger is detected
                    return 0; //Close program
                }
                else
                { //Calling function to reset all (Game and Player) data and UFO data
                    resetGame(gameData);
                    resetPlayer(usa);
                    resetUFOs(ufosOnMap);
                    gameOverMessage = ""; //Reset game over screen message
                }
            }
            else if(gameData.nationalSecurity >= 10)
            { //Otherwise, if winning condition is met
                if(winGameScreen(gameData))
                { //If quit trigger is detected
                    system("CLS"); //wipe console
                    cout << "    >- Quitting..." << endl;
                    anyInput(); //Get any input before continuing
                    return 0; //Close program
                }
                else
                { //Calling function to reset all (Game and Player) data and UFO data
                    resetGame(gameData);
                    resetPlayer(usa);
                    resetUFOs(ufosOnMap);
                }
            }
            else
            { //Otherwise, it's good, end turn funciton call
                gameData.currentYear ++;//Update year
                endTurn(usa, 0, defconOptions, worldEvents, advanceEvents, gameData, ufosOnMap); //Calls function to update income

                if(gameData.currentYear % 2 == 0 && gameData.ufoCount < 20)
                {
                    //Caps ufos at 20 and makes sure that fo count is increased every 2 turns
                    gameData.ufoCount ++;
                }
                spawnUFO(ufosOnMap, gameData.ufoCount, origin, type, symbols, gameData); //Call function to spawn all the UFO's
            }
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
    else if(_mapSpot == '$') //If place is a sam silo
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
    else if(_mapSpot == '*') //If place is destroyed, landed or fled
    {
        displayColorText("*", false, 8); //Grey color
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
    for(int i = 0; i < 50; i++) //Using double for loop, go through entire double array
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
void getMap(GameInfo& _gameData, int _selectFile)
{
    std::string line; //String line used to seperate the text file into lines
    ifstream mapFile_("MapFile.txt"); //This is the map file
    ifstream endFile_("NuclearEnding.txt"); //This is the game over file
    ifstream winFile_("winFile.txt"); //This is the game over file
    ifstream tutOne_("TutorialFrame - 1 General.txt"); //This is the first turorial page
    ifstream tutTwo_("TutorialFrame - 2 Loosing.txt"); //This is the second turorial page
    ifstream tutThree_("TutorialFrame - 3 General.txt"); //This is the second turorial page
    ifstream tutFour_("TutorialFrame - 4 Building.txt"); //This is the third turorial page
    ifstream tutFive_("TutorialFrame - 5 Scanning.txt"); //This is the fourth turorial page
    ifstream tutSix_("TutorialFrame - 6 EndTurn.txt"); //This is the fifth turorial page

    int currentRow = 0; //This integer keeps count of the row number for the saving in array

    if(mapFile_.is_open() && _selectFile == 1) //If instricted to save the file
    {
        while(getline(mapFile_,line)) //This function uses the builtin function: getline
        {
            saveMap(line, _gameData, currentRow); //It then references the saveMapFile function in order to save it into a doubel array.
            currentRow += 1;
        }
        mapFile_.close(); //Close file
    }
    else if(endFile_.is_open() && _selectFile == 2) //Otherwise, if instructed to read out file
    {
        while(getline(endFile_,line)) //This function uses the builtin function: getline
        {
            cout << line << endl; //Find each line and print it out
        }
        endFile_.close(); //Close file
    }
    else if(winFile_.is_open() && _selectFile == 3) //Otherwise, if instructed to read out file
    {
        while(getline(winFile_,line)) //This function uses the builtin function: getline
        {
            cout << line << endl; //Find each line and print it out
        }
        winFile_.close(); //Close file
    }
    else if(tutOne_.is_open() && _selectFile == 4) //Otherwise, if instructed to read out file
    {
        while(getline(tutOne_,line)) //This function uses the builtin function: getline
        {
            cout << line << endl; //Find each line and print it out
        }
        tutOne_.close(); //Close file
    }
    else if(tutTwo_.is_open() && _selectFile == 5) //Otherwise, if instructed to read out file
    {
        while(getline(tutTwo_,line)) //This function uses the builtin function: getline
        {
            cout << line << endl; //Find each line and print it out
        }
        tutTwo_.close(); //Close file
    }
    else if(tutThree_.is_open() && _selectFile == 6) //Otherwise, if instructed to read out file
    {
        while(getline(tutThree_,line)) //This function uses the builtin function: getline
        {
            cout << line << endl; //Find each line and print it out
        }
        tutThree_.close(); //Close file
    }
    else if(tutFour_.is_open() && _selectFile == 7) //Otherwise, if instructed to read out file
    {
        while(getline(tutFour_,line)) //This function uses the builtin function: getline
        {
            cout << line << endl; //Find each line and print it out
        }
        tutFour_.close(); //Close file
    }
    else if(tutFive_.is_open() && _selectFile == 8) //Otherwise, if instructed to read out file
    {
        while(getline(tutFive_,line)) //This function uses the builtin function: getline
        {
            cout << line << endl; //Find each line and print it out
        }
        tutFive_.close(); //Close file
    }
    else if(tutSix_.is_open() && _selectFile == 9) //Otherwise, if instructed to read out file
    {
        while(getline(tutSix_,line)) //This function uses the builtin function: getline
        {
            cout << line << endl; //Find each line and print it out
        }
        tutSix_.close(); //Close file
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
void endTurn(PlayerData& _playerData, float _budgetChange, string _defconOptions[], string _worldEvents[], Event _events[], GameInfo& _gameData, UFO _flyingObjects[])
{
    float randomValue; //This number is randomly generated
    system("CLS"); //Clear console first

    if(_gameData.currentYear == 1946)
    { //If on first year
        getMap(_gameData, 9); //Load building tutorial
    }
    Sleep(300); //Delay by 0.4 seconds

    _gameData.defcon -= 0.05; //Increase defcon naturally
    defconCounter(_defconOptions, _gameData.defcon); //Call function to display defcon information

    Sleep(300); //Delay by 0.4 second

    securityPenalty(_gameData, _flyingObjects); //Calculate and update security penalty
    displaySecurity(_gameData.nationalSecurity); //Call function to display national security

    Sleep(300); //Delay by 0.4 second

    worldEvent(_playerData.currentIncome, _worldEvents, _events, _gameData.currentYear); //Call function to display current world issues

    Sleep(300); //Delay by 0.4 second
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
    _playerData.currentBalance += (_playerData.currentGDP*_playerData.currentIncome)/100.0;
    cout << "    >- Current Department Anual Budget: " << _playerData.currentBalance << " billion dollars" << endl;


    randomValue = (rand()%4+16)/100.0; //Get the random increase in inflation
    _gameData.baseCost += _gameData.baseCost*randomValue; //Increase price of buildings

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
        randomFloat = ((rand()%2+1)/100.0);//Get the random increase in inflation
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
bool gameOverScreen(GameInfo _data, string savedMessage)
{
    getMap(_data, 2); //Print game over screen
    cout << endl << endl << "            =========================================================================================================================" << endl;
    cout << "            >- " << savedMessage << endl;
    cout << "            >- GAMEOVER: The world has ended by nuclear war. At your hands, billions have died. There really is no winning is there?" << endl;
    cout << "            >- Maybe you can be the savior that this world needs, and change it for the better. Stay DETERMINED" << endl;
    cout << "               >- Would you like to play again?" << endl << "            ";
    if(getConfirmation()) //If they want to play again: return false
    {
        system("CLS");
        return false;
    }
    return true; //Else, return true
}

//This function is called to show the user that they have "won"
bool winGameScreen(GameInfo _data)
{
    system("CLS"); //wipe console
    getMap(_data, 3); //Print game over screen
    cout << "    >- Would you like to play again?" << endl << "    ";
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
    getMap(_data, 1); //Initialize the value of the map array //error
    _data.ufoCount = 0; //Set amount of ufo's in the sky to 0
    _data.endGame = false; //Make sure to set the end of the game to false
    _data.nationalSecurity = 5;
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
    _data.buildTutorial = false; //Set intially to false
    _data.buildTutorial = false; //Set intially to false
    return;
}

//This function is in charge of initializing the large advance events
void setBigEvents(Event _events[])
{
    string tempString; //This is a temporary string to try resolving the save string -> crash bug
    //Set event for 1946
    tempString = "The year is 1946. Only one year ago, the worlds largest war ended. Only one year ago, the Atomic age was born";
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

//This function displays the national security of the nation
void displaySecurity(float _security)
{
    int colorCode = 0; //This int represents the color of the UI to represent the situation

    if(_security < 2)
    { //If situation is critical, set color to red
        colorCode = 4;
    }
    else
    { //Otherwise, set color to blue
        colorCode = 9;
    }

    cout << endl << endl << "    ===========================================" << endl;
    cout << "    >- "; //Display national security
    displayColorText("National Security", false, colorCode); //Display status with color clue indicators
    cout << ": ||";

    for(int i = 0; i < round(_security); i++)
    {
        displayColorText("#", false, colorCode); //# of # represents the secuirity value
    }
    for(int i = 0; i < round(10 - _security); i++)
    {
        cout << "-"; //# of - represents missing security value to optain maximum
    }
    cout << "|| [" << round(_security) << "]" << endl;
    return;
}

//This function is for player to choose their building
void chooseBuilding(GameInfo& _gameData, PlayerData& _playerInfo, string _buildingOptions[], string _buildModeOptions[])
{
    int inputValue; //This is used to get the input of the player

    system("CLS");
    if(!_playerInfo.buildTutorial)
    { //If on first year
        getMap(_gameData, 7); //Load building tutorial
        _playerInfo.buildTutorial = true; //Set to true
    }

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
                _playerInfo.currentBalance -= _gameData.baseCost; //Use up money
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

                if(_gameData.nationalSecurity < 10)
                { //If national security has not reaches max yet
                    _gameData.nationalSecurity += 0.2; // add some more
                }
            }
        }
        else
        {
            cout << endl << "    >- Are you sure you want to quit build mode?" << endl;
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
    bool hitRestriction = false; //This indicates when the person has hit a restricted direction
    //If escape is pressed, exit
    while((!(GetKeyState(VK_ESCAPE) & 0x8000)))
    {
        if((GetKeyState('W') & 0x8000) || (GetKeyState(VK_UP) & 0x8000))
        {
            if((_currentY - 2) >= 5 && !(inArea(198, 101, 27, 2, _currentX, _currentY-1))) //Check to see if new position is legal
            {
                hitRestriction = false; //Set hit restriction to false
                updatePosition(_gameData, 0, -2, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
            else if(!hitRestriction)
            {
                cout << "    >- This direction [^] is restricted. It is soviet controlled territory." << endl;
                hitRestriction = true;
            }
        }
        //Else if specific key is pressed:
        else if((GetKeyState('S') & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000))
        {
            if((_currentY + 2) <= 49 && !(inArea(198, 101, 27, 2, _currentX, _currentY + 1))) //Check to see if new position is legal
            {
                hitRestriction = false; //Set hit restriction to false
                updatePosition(_gameData, 0, 2, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
            else if(!hitRestriction)
            {
                cout << "    >- This direction [v] is restricted. It is soviet controlled territory." << endl;
                hitRestriction = true;
            }
        }
        //Else if specific key is pressed:
        else if((GetKeyState('A') & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000))
        {
            if((_currentX - 2) >= 0 && !(inArea(198, 101, 27, 2, _currentX - 2, _currentY))) //Check to see if new position is legal
            {
                hitRestriction = false; //Set hit restriction to false
                updatePosition(_gameData, -2, 0, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
            else if(!hitRestriction)
            {
                cout << "    >- This direction [<-] is restricted. It is soviet controlled territory." << endl;
                hitRestriction = true;
            }
        }
        //Else if specific key is pressed:
        else if((GetKeyState('D') & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000))
        {
            if((_currentX + 2) <= 199 && !(inArea(198, 101, 27, 2, _currentX + 2, _currentY))) //Check to see if new position is legal
            {
                hitRestriction = false; //Set hit restriction to false
                updatePosition(_gameData, 2, 0, true, _currentX, _currentY, _savedChar, _building); //Set spot of map back to saved character before exiting
            }
            else if(!hitRestriction)
            {
                cout << "    >- This direction [->] is restricted. It is soviet controlled territory." << endl;
                hitRestriction = true;
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
    tempY = getAnswer(47, 3); //Show range in y axis. Get input

    if(!(inArea(198, 101, 27, 1, tempX, tempY)))
    { //Check to see if player is trying to put bsae in soviet territory
         updatePosition(_gameData, -_currentX + tempX, -_currentY + tempY, false, _currentX, _currentY, _savedChar, _building); //Set new position of the building
    }
    else //Else, person is not permitted to place base here. Let player know
    {
         cout << endl << "    >- This area is a restricted Soviet and soviet alligned territory. Please choose another location" << endl;
         anyInput();
    }
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
    cout << "    >- Please pick a command.                                                                                             ";
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

    /*
    system("CLS"); //Wiping console
    cout << "    >- -UNSC User Management System-" << endl << "    ================================" << endl << "    ________________________________" << endl;
    cout << "    UNSC TacOS  v.337" <<  endl << "    (S) 2294 FLEETCOM" << endl << "    =======================" <<  endl << "    |  User Log:" << endl;
    cout << "    |  >> Administrator (UNSC ID 8384-C)" << endl << "    |  >>> " << "unknown.IDENTIFY_userGroup" << endl << endl;
    cout << "    ________________________________" << endl << "    ================================" << endl << endl;
    */
    cout << "    >- [version 1.8.2]" << endl;
    cout << "    >- Thanks to Thomas Maloley for teaching me how to program with C++" << endl << endl;
    cout << "    >- Thanks to the following people for play testing" << endl;
    cout << "        >- Thanks Mohammed Al-Anezi!" << endl;
    cout << "        >- Thanks Tieran Chan!" << endl;
    cout << "        >- Thanks Jacob Kim!" << endl;
    cout << "        >- Thanks Alain Xu" << endl;

    cout << endl << "    >- Please enter your pin and ID (HINT: You can put anything)" << endl << endl; //Print instructions

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
void setUFO(UFO& _ufoData, string _origin[], string _type[], char _symbol[], char _gameMap[199][50])
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
            _ufoData.symbol = '^'; //Neutral
        }
        else
        {
            _ufoData.symbol = '!'; //Agressive
        }
    }
    _ufoData.xPos = rand()%198; //Get the random x position
    _ufoData.yPos = rand()%45 + 3; //Get the random y position
    setSpot(_ufoData.savedChar, _gameMap[_ufoData.xPos][_ufoData.yPos]); //Save the character on the map of the UFO before updating map

    //Now that ufo data is saved, update map data
    setSpot(_gameMap[_ufoData.xPos][_ufoData.yPos], '?');

    //Set UFO to not destroyed
    _ufoData.undetected = false;

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
    int inputValue = 10;
    ufoScanAll(_ufos, _gameData.ufoCount, _playerData, _gameData, 10); //Scan all the possible ufo's

    while(inputValue != 0 && !_gameData.endGame)
    {
        system("CLS"); //wipe console

        if(!_playerData.scanTutorial)
        { //If on first year
            getMap(_gameData, 8); //Load Scanning tutorial
            _playerData.scanTutorial = true; //Set to true
        }

        goThroughMap(_gameData, ' ', false); //Display map
        ufoMenu(_ufos, _gameData.ufoCount, _gameData); //Call function to display menu
        inputValue = getAnswer(_gameData.ufoCount, 0); //Get player's input
        cout << endl; //Skip a space

        if(inputValue == 0)
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
            actionMenu(_actionOptions, _ufos[inputValue-1], _playerData.samData, _playerData, _gameData);
        }
        anyInput(); //Get any getch before continuing
    }
    system("CLS");
    return;
}

//This function is a specialized function to display the ufo scan mode menu. It will be replaced wtih a more versitile menu function later
void ufoMenu(UFO _ufos[], int _limit, GameInfo _gameData)
{
    cout << "    >- [" << 0 << "]  To Exit Scan Mode" << endl; //Show option to exit scan mode
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
void actionMenu(string _actionOption[], UFO& _ufo, Building _buildObject[], PlayerData _playerData, GameInfo& _gameData)
{
    int userInput; //this is an integer used to get player input
    int samCounter = 0; //Temporary integer that keeps track of how many sam sites are in range

    for(int i = 0;  i < _playerData.samCount; i++)
    { //Run a for loop through all sam sites
        if(scanRadius(_ufo, _buildObject[i], 15))
        { //If sam site is found in range of tghe specific ufo
            samCounter++; //Add 1 to the storing veriable
        }
    }

    if(_ufo.undetected)
    { //If ufo is destroyed, tell user
        cout << "    >- Sorry, this unidentified object is no longer detected" << endl;
    }
    else
    { //Otherwise, show attack options
        displayMenu(_actionOption, 3, _playerData, 1945, false); //Display options
        if(samCounter > 0)
        { //If same site is in range
            cout << "    >- [4] local SAM site in range. Launch intercepter missile." << endl; //display option
            userInput = getAnswer(4, 1); //allow option to be picked
        }
        else
        {
            userInput = getAnswer(3, 1); //Otherwise, remove option 5
        }

        if(userInput == 1)
        {
            if(!(_gameData.gameMap[_ufo.xPos][_ufo.yPos] == '?'))
            { //If radar is in range and ufo was scanned
                radioPlane(_gameData, _ufo);
            }
            else
            { //Else, radar is not in range, tell user
                cout << "    >- Sorry, a radar station in proimity is required" << endl;
            }
        }
        else if(userInput == 3)
        {
            launchNukes(_gameData); //Launch all nuclear weapons
        }
        else if(userInput == 4)
        {
            launchSAM(samCounter, _gameData, _ufo); //Call function to launch sam missile
        }
    }
    return;
}

//This is one of the game's endings, if you choose to launch all nukes
void launchNukes(GameInfo& _gameData)
{
    cout << endl << "    >- The president has authorized full use of all nuclear weapons on pre-determined targets. Please confirm order:" << endl;
    if(getConfirmation())
    {
        cout << "    >- Processing" << endl;
        _gameData.defcon = 1; //Set defcon to 1
        _gameData.endGame = true; //End game set true now
        for(int i = 0; i < 120; i++) //Spawn 100 different ! marks to symbolize nuclear missiles
        {
            setSpot(_gameData.gameMap[rand()%198][rand()%47], '!');
        }
        goThroughMap(_gameData, ' ', false); //Display map
        cout << endl << "    >- Launch protocol status: |ACTIVE|" << endl;
        cout << "    >- All personal seek emergency shelter, National Response Scenario Number One (NRSNO) is currently active." << endl;
        cout << "    >- Approx --- ~40 min before first strike impact" << endl;
    }
    else
    {
        cout << "    >- Launch canceled" << endl;
    }
    return;
}

//This will initiate the launch of a SAM against ufo's
void launchSAM(int _samCount, GameInfo& _gameData, UFO& _ufo)
{
    int hitProbability = 0; //This int represents the change of a missile hitting
    hitProbability += _samCount*3; //For every sam site in range, add 30% hit porbability

    cout << endl << "    >- " << _samCount << " SAM sites detected in range. Hit porbability at: " << _samCount*30 + 10 << "%" << endl; //Display hit porbability
    cout << endl << "    >- Are you sure you want to launch a SAM at this ufo? There could be international consequences" << endl; //Ask for confirmation

    if(getConfirmation())
    {
        if(_samCount >= 3 || hitProbability + rand()%11 + 1 >= 10) //If three or more SAM sites are in range, rig hit to 100%
        { //Otherwise generate number between 0 and 10. If added to the hit porbability is greater than 10%, you hit plane!
            cout << endl << "    >- UFO hit confirmed" << endl;
            if(_ufo.tag == "Friendly" || _ufo.type == "Cargo" || _ufo.type == "Passenger")
            {
                cout << endl << "    >- Command believes you hit a neutral or friendly civilian plane" << endl << "        + defcon (- world peace)" << endl;
                _gameData.defcon += 0.2; //Increase defcon by 0.2
            }
            else
            {
                cout << endl << "    >- Command believes you hit an enemy plane" << endl << "        + defcon (- world peace)"  << endl << "        + national security"  << endl;
                _gameData.defcon += 0.1; //Increase defcon by 0.1
                _gameData.nationalSecurity += 0.2;
            }
            _ufo.undetected = true; //Set destroyed (disappear) to true
            _ufo.symbol = '*'; //Make new character show status: destroyed
            setSpot(_gameData.gameMap[_ufo.xPos][_ufo.yPos], _ufo.symbol); //Set spot in map to destroyed
        }
        else
        {
            cout << endl << "    >- Command has confirmed that the missile has missed" << endl;
        }
    }
    else
    {
        cout << "    >- Launch canceled" << endl;
    }
    return;
}

//This function is in charge of finding out if a ufo is in a certain map area
bool inArea(int maxX, int minX, int maxY, int minY, int posX, int posY)
{
    if(posX < maxX && posX > minX && posY < maxY && posY > minY)
    { //Check to see if coordinates is in the area. If yes to all conditions, return true
        return true;
    }
    return false; //Else, return false
}

//This is for updating the penalty given to the player in secuirty every turn
void securityPenalty(GameInfo& _data, UFO _objects[])
{
    for(int i = 0; i < _data.ufoCount; i++)
    { //Run a for loop to use all UFO's
        if(inArea(100, 1, 30, 1, _objects[i].xPos, _objects[i].yPos) && _data.nationalSecurity < 10 && _objects[i].tag == "Enemy" && !_objects[i].undetected)
        { //Check to see if they are in the specified area. If yes, penalize country
            _data.nationalSecurity -= 0.2; //add penalty to national security
        }
    }
    return;
}

//This function is for the passive attack option of radioing the plane
void radioPlane(GameInfo& _gameData, UFO& _ufo)
{
    int baseChance; //This represents the boost to the chance to land aircraft depending on the geographical region

    cout << endl << endl; //Spaceing

    if(_ufo.tag == "Friendly") //If plane is ally
    {
        cout << "    >- Local ATC has commanded plane to perform a landing at the nearest airport" << endl;
        cout << "    >- Plane has landed and identified itself as friendly." << endl;

        _ufo.undetected = true; //Set landed (disappear) to true
        _ufo.symbol = '*'; //Make new character show status: landed
        setSpot(_gameData.gameMap[_ufo.xPos][_ufo.yPos], _ufo.symbol); //Set spot in map to landed
    }
    else if(_ufo.tag == "Neutral") //If plane is neutral
    {
        cout << "    >- Local ATC has commanded plane to perform a landing at the nearest airport" << endl;
        cout << "    >- Plane has landed and identified itself as neutral. World tension increase" << endl;

        _gameData.defcon += 0.1; //Add penalty of 0.1 defcon (world tension)
        _ufo.undetected = true; //Set landed (disappear) to true
        _ufo.symbol = '*'; //Make new character show status: landed
        setSpot(_gameData.gameMap[_ufo.xPos][_ufo.yPos], _ufo.symbol); //Set spot in map to landed
    }
    else //otherwise, if plane is enemy
    {
        if(inArea(100, 1, 30, 1, _ufo.xPos, _ufo.yPos)) //If plane is over NA
        {
            cout << "    >- UFO location classes as direct ally airspace" << endl;
            baseChance = 7;
        }
        else if(inArea(198, 101, 24, 1, _ufo.xPos, _ufo.yPos)) //If plane is over latin america
        {
            cout << "    >- UFO location classes as over mostly unalligned latin america " << endl;
            baseChance = 3;
        }
        else if(inArea(100, 1, 49, 31, _ufo.xPos, _ufo.yPos)) //If plane is over soviet controlled area
        {
            cout << "    >- UFO location classes as over soviet and proxy (enemy) controlled territory" << endl;
            baseChance = -30;
        }
        else if(inArea(198, 101, 49, 25, _ufo.xPos, _ufo.yPos)) //If plane is over asia
        {
            cout << "    >- UFO location classes as over mostly neutral or western alligned asian continent" << endl;
            baseChance = 5;
        }
        else //If plane is not in any of these areas
        {
            cout << "    >- UFO location can not be tracked" << endl;
            baseChance = 3;
        }

        cout << "    >- Analytic software predicts approximately a: " << baseChance * 10 << "% of sucess. Would you like to continue?" << endl;
        if(getConfirmation())
        {
            if(rand()%11 + baseChance + 1 > 10)
            { //If random number generated + base chance is greater than 10, player has sucess
                cout << "    >- UFO, identified as enemy, has followed your intructions and has landed." << endl; //Notify person
                cout << "        + Increase security" << endl;
                cout << "        + Decrease defcon" << endl;
                _gameData.defcon -= 0.2; //decreasse defcon
                _gameData.nationalSecurity += 0.2; //Increase security
            }
            else
            { //Otherwise, player has no suceeded
                cout << "    >- After ATC's attempt to gain contact, the UFO, identified as enemy, has dropped off the radar and fled local airspace" << endl; //Notify user
                cout << "        + Increase security" << endl;
                cout << "        + Decrease defcon" << endl;
                _gameData.defcon -= 0.1; //Decrease defcon
                _gameData.nationalSecurity += 0.1; //Increase security
            }
            _ufo.undetected = true; //Set landed (disappear) to true
            _ufo.symbol = '*'; //Make new character show status: landed
            setSpot(_gameData.gameMap[_ufo.xPos][_ufo.yPos], _ufo.symbol); //Set spot in map to landed
        }
    }
    return;
}

//This function is shown to teach the game
void tutorial(GameInfo _gameData)
{
    for(int i = 4; i < 7; i++)
    { //Runa for loop through every tutorial frame
        system("CLS"); //Wipe console
        getMap(_gameData, i); //Display frame
        anyInput(); //Get any input before continuing
    }
    return;
}
