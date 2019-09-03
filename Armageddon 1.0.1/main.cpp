/*
>- Author: Max Wong
>- Date: Sep 1, 2019
>- Updated: Sep 2, 2019
>- Purpose: To write a game for a summative project.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 0.0.1]
>- Thanks to Vedaant Srivastava for the error trapping system and play-testing
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>-
>- [TO DO]
>- commenting
>- confirm + placing base
>-
*/

//Declaring all used libraries
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>   // WinApi header
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

//Declaring all functions
void getMapFile (char[][55]); //This function is used to read a txt file line by line
void saveMapFile (std::string, char[][55], int); //This function is used to save the txt file into a double array
void readMapArray (char[][55], HANDLE); //This function is used to print the map into the consol
void placeBase(char[][55], HANDLE); //This function is used to select the location of a base

bool stringChecker(string); //Function to check if an input is a float or integer

int main()
{
    //Declaring all variables
    char gameMap [199][55];//This is the double array that houses the whole map

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
        cout << ">- Please enter a direct command. Below are the primary listed commands." << endl;
        cout << "create a new base -> /spawn" << endl;
        cout << "to refresh -> /refresh" << endl;
        cin >> inputCommand;

        //If player enters /spawn, create a base
        if(inputCommand == "/spawn")
        {
            placeBase(gameMap, hConsole);

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
        //cout << line[i] << endl;
       gameMap[i][currentRow] = line[i];
    }
    return;
}

//simply runs through a for loop through each value of the array and prints them out to console
void readMapArray(char gameMap [][55], HANDLE hConsole)
{

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Read out the map double array
    for(int i = 0; i < 55; i++)
    {
        for(int j = 0; j < 199; j++)
        {
            if(gameMap[j][i] == '@')
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << gameMap[j][i];
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 15);
                cout << gameMap[j][i];
            }
        }
        cout << endl;
    }
}

//Function used to place a base anywhere on the map
void placeBase(char gameMap[][55], HANDLE hConsole)
{

    //Defining variables

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //allows the manipulation of the console

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

        cout << ">- Please enter a direct command. Primary function commands are listed below" << endl;

        if(errorOccured == false)
        {

            cout << ">- Move up -> /up" << endl << ">- Move down -> /down" << endl << ">- Move left -> /left" << endl << ">- Move right -> /right" << endl;
            cout << endl << ">- to place on a custom coordinate -> /input" << endl << ">- to place base -> /place" << endl << ">- Cancel -> /cancel" << endl;
        }
        errorOccured = false;


        inputCommand = " ";
        cin >> inputCommand;

        if(inputCommand == "/up" || inputCommand == "/u")
        {
            if((current_y - 1) < 5 )
            {
                cout << ">- ERROR, item can not move there" << endl;
                cout << ">- Directive: Please type a different command" << endl;
            }
            else
            {
                gameMap[current_x][current_y] = savedCharacter;
                savedCharacter = gameMap[current_x][current_y - 1];
                gameMap[current_x][current_y - 1] = '@';
                current_y -= 1;

                system("CLS");
                readMapArray(gameMap, hConsole);
            }
        }

        if(inputCommand == "/down" || inputCommand == "/d")
        {
            if((current_y + 1) > 45 )
            {
                cout << ">- ERROR, item can not move there" << endl;
                cout << ">- Directive: Please type a different command" << endl;
            }
            else
            {
                gameMap[current_x][current_y] = savedCharacter;
                savedCharacter = gameMap[current_x][current_y + 1];
                gameMap[current_x][current_y + 1] = '@';
                current_y += 1;

                system("CLS");
                readMapArray(gameMap, hConsole);
            }
        }

        if(inputCommand == "/left" || inputCommand == "/l")
        {
            if((current_x - 1) < 0 )
            {
                cout << ">- ERROR, item can not move there" << endl;
                cout << ">- Directive: Please type a different command" << endl;
            }
            else
            {
                gameMap[current_x][current_y] = savedCharacter;
                savedCharacter = gameMap[current_x - 1][current_y];
                gameMap[current_x - 1][current_y] = '@';
                current_x -= 1;

                system("CLS");
                readMapArray(gameMap, hConsole);
            }
        }

        if(inputCommand == "/right" || inputCommand == "/r")
        {
            if((current_x + 1) > 199 )
            {
                cout << "ERROR, item can not move there" << endl;
                cout << "Directive: Please type a different command" << endl;
            }
            else
            {
                gameMap[current_x][current_y] = savedCharacter;
                savedCharacter = gameMap[current_x + 1][current_y];
                gameMap[current_x + 1][current_y] = '@';
                current_x += 1;

                system("CLS");
                readMapArray(gameMap, hConsole);
            }
        }

        if(inputCommand == "/input" || inputCommand == "/i")
        {
            findingCoordinate = true;

            do{

                cout << endl << ">- Please enter your specific X-coordinate below. Press /cancel to exit" << endl;
                cin >> inputCommand;

                if(inputCommand == "/cancel")
                {
                    findingCoordinate = false;
                    inputCommand = "";
                }

                if( stringChecker(inputCommand))
                {
                    saved_x = round(::atof(inputCommand.c_str()));

                    if(saved_x > 198) saved_x = 198;
                    if(saved_x <  3) saved_x = 3;

                    cout << endl << ">- Please enter your specific Y-coordinate below. Press /cancel to exit" << endl;
                    cin >> inputCommand;

                    if(inputCommand == "/cancel")
                    {
                        findingCoordinate = false;
                        inputCommand = "";
                    }
                    if( stringChecker(inputCommand))
                    {
                        saved_y = round(::atof(inputCommand.c_str()));

                        if(saved_y > 44) saved_y = 44;
                        if(saved_y <  3) saved_y = 3;

                        cout << ">- Your coordinate is [" << saved_x << "," << saved_y << "]. Press /y to confirm." << endl;
                        cin >> inputCommand;

                        if(inputCommand == "/y" || inputCommand == "/yes")
                        {
                            gameMap[current_x][current_y] = savedCharacter;
                            savedCharacter = gameMap[saved_x][saved_y];
                            gameMap[saved_x][saved_y] = '@';
                            current_x = saved_x;
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

        if(inputCommand == "/cancel" || inputCommand == "/c")
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

        if(inputCommand == "/place" || inputCommand == "/p")
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
        else if(inputCommand != "/up" && inputCommand != "/u" && inputCommand != "/down" && inputCommand != "/d" && inputCommand != "/left" && inputCommand != "/l" && inputCommand != "/cancel" && inputCommand != "/c" && inputCommand != "/input"  && inputCommand != "/i" && inputCommand != "/place" && inputCommand != "/p")
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

