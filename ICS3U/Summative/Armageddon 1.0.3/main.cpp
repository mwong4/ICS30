/*
>- Author: Max Wong
>- Date: Sep 1, 2019
>- Updated: Nov 10, 2019
>- Purpose: To write a game for a summative project.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 1.0.5]
>- Thanks to Vedaant Srivastava for the error trapping system and play-testing
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [TO DO]
>- Handle
>- Menu's
>- Error trapping new
>- Structures
>- place base efficiency
>- cleaning
>-
*/

//Version 1.0.8

//Game features to be finished
    //Spending money to build nuclear bases (a balance of power thing)
    //Build radar stations to detect ships or planes
    //Be able to search ships and planes and figure out if they are soviet
    //Events that affect income or gameplay
        //Soviets invade afghenistan
        //Cuban missile crisis
        //Berlin wall
    //Always a nuclear ending, no winning
    //Research tech
    //Communiquges with the other military department

//Events that could affect income:
    //Soviets become more agressive, US Government becomes more worried and increases military spending (+)
    //New government is pro-military and increases military spending(+)
    //Military demonstration impresses the public(+)
    //World is goingt through a recession, funding is decreased(-)
    //New government is against military and decreases military spending(-)
    //Military demonstration goes badly, public is less supportive(-)
    //NATO performs a military excercise
    //Warsaw Pact performs military exercise
    //More refugees escape East Germany
    //Civial war in south america supports an anti-soviet regime

//Specific events
    //Soviets invade afghanistan
    //Cuban missile crisis begins
    //Berlin wall falls
    //Large uprising in hungary begins
    //Soviet submarine acceident happens (K-219)
    //Macarthur calls for 100 nuclear bombs for Korea
    //Civil actions against the government for Vietnam are started
    //U-2 shot down
    //Space Race begins

//Declaring all used libraries
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>   // WinApi header
#include <sstream>
#include <iomanip>
#include <math.h>
#include <conio.h>

using namespace std;

struct gameInfo
{

};

//Declaring all functions
void getMapFile (char[][55]); //This function is used to read a txt file line by line
void saveMapFile (std::string, char[][55], int); //This function is used to save the txt file into a double array
void readMapArray (char[][55]); //This function is used to print the map into the consol
void placeBase(char[][55], string[]); //This function is used to select the location of a base
void loadStartGame();
void changePosition(char[][55]); //This function is used to update the position of an object
void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number

bool stringChecker(string); //Function to check if an input is a float or integer

int main()
{
    //Declaring all variables
    char gameMap [199][55];//This is the double array that houses the whole map
    string myOptions[10] = {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"}; //This array is used in the menu that allows custome size

    bool gameRun = true; //This boolean is used to determine if the program is running
    bool gameStart = true; //This boolean is used to determine if the game is running for the first time

    string inputCommand = "";//This variable is used to get the players input

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //HANDLE and hCOnsole are using the windows.h lbrary to color individual letters

    //Reset the map double array to blank/null
    for(int i = 0; i < 55; i++)
    {
        for(int j = 0; j < 199; j++)
        {
            gameMap[j][i] = ' ';
        }
    }

    loadStartGame();
    //Get map from text file and save it
    getMapFile(gameMap);

    //main loop of the game
    while(gameRun)
    {
        //If the game is starting for the first time, print out the map
        if(gameStart)
        {
           readMapArray(gameMap, hConsole);
           gameStart = false;
        }

        //Ask for a input from the player
        myOptions[0] = "create a new base -> /spawn";
        myOptions[1] = "to refresh -> /refresh";
        displayMenu(myOptions, 2);
        cin >> inputCommand;

        //If player enters /spawn, create a base
        if(inputCommand == "/spawn")
        {
            placeBase(gameMap, hConsole, myOptions);
        }
        //To refresh
        if(inputCommand == "/refresh")
        {
            system("CLS");
            readMapArray(gameMap, hConsole);
        }
        //Otherwise, print an error message
        else if(inputCommand != "/spawn" && inputCommand != "/refresh" )
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << endl << "==================================================" << endl;
            cout << ">- Please enter a valid input command"<< endl;
            cout << "==================================================" << endl << endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
    return 0;
}

//This function is used to access the txt file and read the file line by line.
void getMapFile(char gameMap[][55])
{
    std::string line;
    ifstream file_("MapFile.txt");

    int currentRow = 0;

    if(file_.is_open())
    {
        //This function uses the builtin function: getline
        while(getline(file_,line))
        {
            //It then references the saveMapFile function in order to save it into a doubel array.
            saveMapFile(line, gameMap, currentRow);
            currentRow += 1;
        }
        file_.close();
    }
    return;
}

//Saves the map from the txt file into a double array
void saveMapFile (std::string line, char gameMap [][55], int currentRow)
{
    //Running through every character
    for(std::string::size_type i = 0; i < line.size(); ++i)
    {
       gameMap[i][currentRow] = line[i];
    }
    return;
}

//simply runs through a for loop through each value of the array and prints them out to console
void readMapArray(char gameMap [][55])
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //HANDLE and hCOnsole are using the windows.h lbrary to color individual letters

    //Read out the map double array
    for(int i = 0; i < 55; i++)
    {
        for(int j = 0; j < 199; j++)
        {
            if(gameMap[j][i] == '@')
                //Everytime you encounter a @ sign, color it red
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << gameMap[j][i];
            }
            else
            {
                //Otherwise, color it white
                SetConsoleTextAttribute(hConsole, 15);
                cout << gameMap[j][i];
            }
        }
        cout << endl;
    }
}

//Function used to place a base anywhere on the map
void placeBase(char gameMap[][55], string myOptions[])
{
    //Defining variables
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //HANDLE and hCOnsole are using the windows.h lbrary to color individual letters

    bool choosingLocation = false; //boolean that is used to check if the player is still choosing a lcation
    bool errorOccured = false; //Boolean that checks if an error has occured
    bool findingCoordinate = false; //Boolean that checks if an error has occured

    string inputCommand = ""; //Stirng to take inputs from player

    int current_x; //temporarily holds the x value
    int current_y; //temporarily holds the y value
    int saved_x; //Saves coordinate for the custom choice of coordinate feature
    int saved_y;

    char savedCharacter; //Temporarily saves a character

    cout << ">- Creating..." << endl << endl;
    choosingLocation = true;

    //Spawn base on position:
    savedCharacter = gameMap[100][20];
    gameMap[100][20] = '@';

    //save current x and current y
    current_x = 100;
    current_y = 20;

    system("CLS");
    readMapArray(gameMap, hConsole);

    while(choosingLocation)
    {
        //Print out what the player can do
        if(errorOccured == false)
        {
            myOptions[0] = ">- Move around using keyboard -> /k";
            myOptions[1] = ">- to place on a custom coordinate -> /input";
            myOptions[2] = ">- to place base -> /place";
            myOptions[3] = ">- Cancel -> /cancel";
            myOptions[4] = ">- Press escape to exit keyboard mode";
            displayMenu(myOptions,5);
        }
        errorOccured = false;
        inputCommand = " ";
        cin >> inputCommand;

        //If player inputs /k, activate keyboard mode
        if(inputCommand == "/k" || inputCommand == "/keyboard") cout << ">- Please use arrow keys or WASD" << endl;

        while(inputCommand == "/k" || inputCommand == "/keyboard")
        {
            //If specific key is pressed:
            if((GetKeyState('W') & 0x8000) || (GetKeyState(VK_UP) & 0x8000))
            {
                if((current_y - 1) < 5 ) //Check to see if new position is legal
                {
                    cout << ">- ERROR, item can not move there" << endl;
                    cout << ">- Directive: Please type a different command" << endl;
                }
                else
                {
                    gameMap[current_x][current_y] = savedCharacter; //Replace current position with the saved character
                    savedCharacter = gameMap[current_x][current_y - 1]; //Save the character of the future value
                    gameMap[current_x][current_y - 1] = '@'; //Replace the future spot with an @ symbol
                    current_y -= 1; //Update current position

                    system("CLS");
                    readMapArray(gameMap, hConsole);
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << ">- Press escape to exit keyboard mode" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
            //Else if specific key is pressed:
            else if((GetKeyState('S') & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000))
            {
                if((current_y + 1) > 45 ) //Check to see if new position is legal
                {
                    cout << ">- ERROR, item can not move there" << endl;
                    cout << ">- Directive: Please type a different command" << endl;
                }
                else
                {
                    gameMap[current_x][current_y] = savedCharacter; //Replace current position with the saved character
                    savedCharacter = gameMap[current_x][current_y + 1]; //Save the character of the future value
                    gameMap[current_x][current_y + 1] = '@'; //Replace the future spot with an @ symbol
                    current_y += 1; //Update current position

                    system("CLS");
                    readMapArray(gameMap, hConsole);
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << ">- Press escape to exit keyboard mode" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
            //Else if specific key is pressed:
            else if((GetKeyState('A') & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000))
            {
                if((current_x - 1) < 0 ) //Check to see if new position is legal
                {
                    cout << ">- ERROR, item can not move there" << endl;
                    cout << ">- Directive: Please type a different command" << endl;
                }
                else
                {
                    gameMap[current_x][current_y] = savedCharacter; //Replace current position with the saved character
                    savedCharacter = gameMap[current_x - 1][current_y]; //Save the character of the future value
                    gameMap[current_x - 1][current_y] = '@'; //Replace the future spot with an @ symbol
                    current_x -= 1; //Update current position

                    system("CLS");
                    readMapArray(gameMap, hConsole);
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << ">- Press escape to exit keyboard mode" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
            //Else if specific key is pressed:
            else if((GetKeyState('D') & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000))
            {
                if((current_x + 1) > 199 ) //Check to see if new position is legal
                {
                    cout << "ERROR, item can not move there" << endl;
                    cout << "Directive: Please type a different command" << endl;
                }
                else
                {
                    gameMap[current_x][current_y] = savedCharacter; //Replace current position with the saved character
                    savedCharacter = gameMap[current_x + 1][current_y]; //Save the character of the future value
                    gameMap[current_x + 1][current_y] = '@'; //Replace the future spot with an @ symbol
                    current_x += 1; //Update current position

                    system("CLS");
                    readMapArray(gameMap, hConsole);
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << ">- Press escape to exit keyboard mode" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
            //Else if escape is pressed, exit
            else if((GetKeyState(VK_ESCAPE) & 0x8000))
            {
                inputCommand = "escape";
            }
        }
        //If player chooses to input a custom input:
        if(inputCommand == "/input" || inputCommand == "/i")
        {
            findingCoordinate = true;
            do
            {
                cout << endl << ">- Please enter your specific X-coordinate below. Press /cancel to exit" << endl;
                cin >> inputCommand; //get the specific x input

                if(inputCommand == "/cancel") //If they choose to exit, exit
                {
                    findingCoordinate = false;
                    inputCommand = "";
                }

                else if(stringChecker(inputCommand)) //Check to see if input is valid
                {
                    saved_x = round(::atof(inputCommand.c_str())); //If yes convert to int

                    if(saved_x > 198) saved_x = 198; //Check to see if new position is legal. If no, set to default value
                    if(saved_x <  3) saved_x = 3;

                    cout << endl << ">- Please enter your specific Y-coordinate below. Press /cancel to exit" << endl;
                    cin >> inputCommand; //Get input for specific y-input

                    if(inputCommand == "/cancel")
                    {
                        findingCoordinate = false; //If player chooses to exit, exit
                        inputCommand = "";
                    }
                    else if( stringChecker(inputCommand)) //Otherwise check to see if input in an integer
                    {
                        saved_y = round(::atof(inputCommand.c_str())); //If yes, convert to integer

                        if(saved_y > 44) saved_y = 44; //If input is not legal, set to default values
                        if(saved_y <  3) saved_y = 3;

                        cout << ">- Your coordinate is [" << saved_x << "," << saved_y << "]. Press /y to confirm." << endl;
                        cin >> inputCommand; //Get player confirmation for their input

                        if(inputCommand == "/y" || inputCommand == "/yes") //If they answer yes, repeat process done above in keyboard mode
                        {
                            gameMap[current_x][current_y] = savedCharacter; //place saved character back
                            savedCharacter = gameMap[saved_x][saved_y]; //save new position character
                            gameMap[saved_x][saved_y] = '@'; //Replace new position on map with @ sign
                            current_x = saved_x; //Save current position as the new values
                            current_y = saved_y;

                            system("CLS");
                            readMapArray(gameMap, hConsole);

                            findingCoordinate = false;
                            inputCommand  = "/input";
                        }
                    }
                    else
                    {
                        cout << endl << ">- Error, please enter an integer between 2 and 45" << endl << endl;
                    }
                }
                else
                {
                    cout << endl << ">- Error, please enter an integer between 2 and 199" << endl << endl;
                }

            }while(findingCoordinate);
        }

        else if(inputCommand == "/cancel" || inputCommand == "/c")
        {
            cout << endl << ">- You are Attempting to exit. Are you sure? Press /y to quit" << endl;
            cin >> inputCommand;

            system("CLS");
            readMapArray(gameMap, hConsole);
            if(inputCommand == "/y" || inputCommand == "/yes")
            {
                //wipe the base symbol from the map array
                gameMap[current_x][current_y] = savedCharacter;

                //For some reason the base character is not being wiped so I have to refresh two times
                system("CLS");
                readMapArray(gameMap, hConsole);
                return;
            }
        }

        else if(inputCommand == "/p" || inputCommand == "/place")
        {
            cout << endl << ">- Are you sure you want to place the base on [" << current_x << "," << current_y << "]? This action is not reversable. Press /y to confirm." << endl;
            cin >> inputCommand;

            if(inputCommand == "/y" || inputCommand == "/yes")
            {
                system("CLS");
                readMapArray(gameMap, hConsole);
                return;
            }
        }
        //If input is not valid, print an error message in red
        else if(inputCommand != "/cancel" && inputCommand != "/c" && inputCommand != "/input"  && inputCommand != "/i" && inputCommand != "/place" && inputCommand != "/p" && inputCommand != "/k" && inputCommand != "/keyboard" && inputCommand != "escape")
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << endl << "==================================================" << endl;
            cout << ">- Please enter a valid input command"<< endl;
            cout << "==================================================" << endl << endl;
            SetConsoleTextAttribute(hConsole, 15);

            errorOccured = true;
        }

    }
}

void changePosition(char gameMap [][55])
{

}

//Function used to check if input string is a float
//Credit to Vedaant for this function
bool stringChecker(string myString)
{
    long double flMyString;
    ostringstream conversion;

    //Checks the string using built in iostream library
    stringstream(myString) >> flMyString;
    conversion << setprecision(9) << flMyString;

    string convFlMyString = conversion.str();

    //If initial string does not match corrected string, string is not a float
    if (convFlMyString == myString)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Game start menu
void loadStartGame()
{
    //Defining the variables
    string randInput = "";
    string userID = "";
    char ch;

    system("color A"); //Fake server connection animation

    //When server is connected
    cout << ">- -UNSC User Management System-" << endl << "================================" << endl << "________________________________" << endl;
    cout << "UNSC TacOS  v.337" <<  endl << "(S) 2294 FLEETCOM" << endl << "=======================" <<  endl << "|  User Log:" << endl;
    cout << "|  >> Administrator (UNSC ID 8384-C)" << endl << "|  >>> " << "unknown.GUEST_userGroup" << endl << endl;
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
    cout << endl;
    if(randInput == "cheats.activate")
    {
        cout << ">- \Admin hacks activated." << endl << ">- Welcome " << userID << endl;
    }
    else
    {
        cout << ">- \Acess Granted." << endl << ">- Welcome " << userID << endl;
    }
    cout << endl << "    [Press any key to continue]" << endl;
    getch();
}

void displayMenu(string options[], int arraySize)
{
    cout << ">- Please enter a direct command. Below are the primary listed commands." << endl;
    //Display instructions
    for(int i = 0; i < arraySize; i++)
    {
        cout << ">- [" << i+1 << "] " << options[i] << endl;
    }
    return;
}

