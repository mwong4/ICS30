/*
>- Author: Max Wong
>- Date: Sep 1, 2019
>- Updated: Nov 10, 2019
>- Purpose: To write a game for a summative project.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 1.1.0]
>- Thanks to Vedaant Srivastava for the error trapping system and play-testing
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [TO DO]
>- Structures
>- place base efficiency
>- cleaning
>-
*/

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

//For error trapping
#include<limits>

using namespace std;

struct gameInfo
{

};

//Declaring all functions
void getMapFile (char[][55]); //This function is used to read a txt file line by line
void saveMapFile (std::string, char[][55], int); //This function is used to save the txt file into a double array
void readMapArray (char[][55]); //This function is used to print the map into the consol
void placeBase(char[][55], string[]); //This function is used to select the location of a base
void changePosition(char[][55]); //This function is used to update the position of an object

void loadStartGame();

void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number
float getAnswer(); //Function used to get the players response as an integer (with error trapping)

int main()
{
    //Declaring all variables
    char gameMap [199][55];//This is the double array that houses the whole map
    string myOptions[10] = {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"}; //This array is used in the menu that allows custome size

    bool gameRun = true; //This boolean is used to determine if the program is running
    bool gameStart = true; //This boolean is used to determine if the game is running for the first time

    int inputCommand = 0;//This variable is used to get the players input

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
           readMapArray(gameMap);
           gameStart = false;
        }

        //Ask for a input from the player
        myOptions[0] = "create a new base -> /spawn";
        myOptions[1] = "to refresh -> /refresh";
        displayMenu(myOptions, 2);
        inputCommand = getAnswer(); //Get player input


        if(inputCommand == 1) //If player enters /spawn, create a base
        {
            placeBase(gameMap, myOptions);
        }
        else //To refresh
        {
            system("CLS");
            readMapArray(gameMap);
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
        while(getline(file_,line)) //This function uses the builtin function: getline
        {
            saveMapFile(line, gameMap, currentRow); //It then references the saveMapFile function in order to save it into a doubel array.
            currentRow += 1;
        }
        file_.close();
    }
    return;
}

//Saves the map from the txt file into a double array
void saveMapFile (std::string line, char gameMap [][55], int currentRow)
{
    for(std::string::size_type i = 0; i < line.size(); ++i) //Running through every character
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

    for(int i = 0; i < 55; i++) //Read out the map double array
    {
        for(int j = 0; j < 199; j++)
        {
            if(gameMap[j][i] == '@') //Everytime you encounter a @ sign, color it red
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << gameMap[j][i];
            }
            else //Otherwise, color it white
            {
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
    bool findingCoordinate = false; //Boolean that checks if an error has occured

    int inputCommand = 0; //Stirng to take inputs from player

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
    readMapArray(gameMap);

    while(choosingLocation)
    {
        //Print out what the player can do
        myOptions[0] = ">- Move around using keyboard";
        myOptions[1] = ">- to place on a custom coordinate";
        myOptions[2] = ">- to place base";
        myOptions[3] = ">- Cancel/exit";
        displayMenu(myOptions,4);

        inputCommand = 0;
        inputCommand = getAnswer();

        //If player inputs /k, activate keyboard mode
        if(inputCommand == 1)
        {
            cout << ">- Please use arrow keys or WASD" << endl;
        }

        while(inputCommand == 1)
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
                    readMapArray(gameMap);
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
                    readMapArray(gameMap);
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
                    readMapArray(gameMap);
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
                    readMapArray(gameMap);
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << ">- Press escape to exit keyboard mode" << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
            //Else if escape is pressed, exit
            else if((GetKeyState(VK_ESCAPE) & 0x8000))
            {
                inputCommand = 0;
            }
        }
        //If player chooses to input a custom input:
        if(inputCommand == 2)
        {
            findingCoordinate = true;
            do
            {
                cout << endl << ">- Please enter your specific X-coordinate below between 3 and 198. Press 0 to exit" << endl;
                saved_x = getAnswer();

                if(saved_x == 0) //If they choose to exit, exit
                {
                    findingCoordinate = false;
                }
                else
                {
                    if(saved_x <  3) saved_x = 3;

                    cout << endl << ">- Please enter your specific Y-coordinate below between 3 and 43. Press 0 to exit" << endl;
                    saved_y = getAnswer(); //Get input for specific y-input

                    if(saved_y == 0)
                    {
                        findingCoordinate = false; //If player chooses to exit, exit
                    }
                    else
                    {
                        if(saved_y > 44) saved_y = 44; //If input is not legal, set to default values
                        if(saved_y <  3) saved_y = 3;

                        cout << ">- Your coordinate is [" << saved_x << "," << saved_y << "]. Press 1 to confirm." << endl;
                        inputCommand = getAnswer(); //Get player confirmation for their input

                        if(inputCommand == 1) //If they answer yes, repeat process done above in keyboard mode
                        {
                            gameMap[current_x][current_y] = savedCharacter; //place saved character back
                            savedCharacter = gameMap[saved_x][saved_y]; //save new position character
                            gameMap[saved_x][saved_y] = '@'; //Replace new position on map with @ sign
                            current_x = saved_x; //Save current position as the new values
                            current_y = saved_y;

                            findingCoordinate = false;
                        }
                    }
                }
            system("CLS");
            readMapArray(gameMap);
            }while(findingCoordinate);
        }
        else if(inputCommand == 3)
        {
            cout << endl << ">- Are you sure you want to place the base on [" << current_x << "," << current_y << "]? This action is not reversable. Press 1 to confirm." << endl;
            inputCommand = getAnswer();

            system("CLS");
            readMapArray(gameMap);
            if(inputCommand == 1)
            {
                return;
            }
        }
        else if(inputCommand == 4)
        {
            cout << endl << ">- You are Attempting to exit. Are you sure? Press 1 to quit" << endl;
            inputCommand = getAnswer();

            system("CLS");
            readMapArray(gameMap);
            if(inputCommand == 1)
            {
                //wipe the base symbol from the map array
                gameMap[current_x][current_y] = savedCharacter;

                //For some reason the base character is not being wiped so I have to refresh two times
                system("CLS");
                readMapArray(gameMap);
                return;
            }
        }
        else
        {
                cout << endl << ">- hmm, try choosing a number from 1-4" << endl;
        }

    }
}

void changePosition(char gameMap [][55])
{

}

//Error trapping funcion that only accepts integers
float getAnswer ()
{
    int playerInput; //This variable is used to get the player's input
    bool findingInput; //This bool determines if the loop continues running

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //HANDLE and hCOnsole are using the windows.h lbrary to color individual letters
    do
    {
        findingInput = false; //By default, the loop will end
        cout << ">- Your input: "; //Get player input
        cin >> playerInput;
        SetConsoleTextAttribute(hConsole, 12); //Set color to red

        if(cin.fail())//Check to see if player entered a "bad" input type
        {
            cin.clear(); //Clear all flags
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore incorrect symbols
            cout << endl << "==================================================" << endl;
            cout << ">- Please enter a valid input number"<< endl;
            cout << "==================================================" << endl << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if(playerInput > 198 || playerInput < 0 ) //Otherwise, print an error message
        {
            cout << endl << "==================================================" << endl;
            cout << ">- Please enter a number between 0 and 198 "<< endl;
            cout << "==================================================" << endl << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        SetConsoleTextAttribute(hConsole, 15); //Set color back to white
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
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

