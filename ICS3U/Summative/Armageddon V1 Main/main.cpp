/*
>- Author: Max Wong
>- Date: Sep 1, 2019
>- Updated: Nov 14, 2019
>- Purpose: To write a game for a summative project.
>- Game should incorperate all the major programming requirements from the course.
>-
>- [version 1.1.6]
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [TO DO]
>- Efficiency
>- Different buildings
>- cleaning
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
    //Defcon indicator

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
    //ww2 ends (September 2, 1945)
    //Korean war starts (June 25, 1950)
    //Space Race begins (1955)
    //Large uprising in hungary begins (October 23, 1956)
    //Civil actions against the government for Vietnam are started (1960s)
    //U-2 shot down (May 1, 1960)
    //Cuban missile crisis begins (October 16, 1962)
    //Soviets invade afghanistan (December 25, 1979)
    //Soviet submarine acceident happens (K-219) (March 8, 1986)
    //Chernobyle (April 26, 1986)
    //Berlin wall falls (October 3, 1990)

//Declaring all used libraries
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>   // WinApi header
#include <sstream>
#include <iomanip>
#include <math.h>
#include <conio.h>

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include<limits> //For error trapping

using namespace std;

struct gameInfo
{
    char gameMap [199][55];//This is the double array that houses the whole map
    int current_x; //temporarily holds the x value while placing building
    int current_y; //temporarily holds the y value while placing building
    char savedCharacter; //Temporarily saves a character while placing building

    int currentYear = 1945; //Year is 1945
    float currentGDP = 2000000; //The stating US GDP is 2 trillion
    float currentIncome = 0.001; //The starting military funding is 0.001%
    float currentBalance = 0.5; //The current military balance is 500 millsion dollars
};

//Declaring all functions
gameInfo getMapFile (gameInfo); //This function is used to read a txt file line by line
gameInfo saveMapFile (std::string, gameInfo, int); //This function is used to save the txt file into a double array
void readMapArray (gameInfo); //This function is used to print the map into the consol
gameInfo placeBase(gameInfo, string[]); //This function is used to select the location of a base
gameInfo changePosition(gameInfo, int, int, bool); //This function is used to update the position of an object

gameInfo endTurn(gameInfo);

void loadStartGame(); //Fake loading screen to start the game
void loadConsoleFeed();

void displayRedText(string, bool);
void displayMenu(string[], int, gameInfo); //Function to show the menu: All positions are options except last which is reserved for quit number
float getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)

int main()
{
    //Declaring all variables
    gameInfo myGameInfo;
    string myOptions[10] = {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"}; //This array is used in the menu that allows custome size

    bool gameRun = true; //This boolean is used to determine if the program is running
    bool gameStart = true; //This boolean is used to determine if the game is running for the first time

    int inputCommand = 0;//This variable is used to get the players input

    srand (time(NULL)); //Randomize seed according to time

    //Reset the map double array to blank/null
    for(int i = 0; i < 55; i++)
    {
        for(int j = 0; j < 199; j++)
        {
            myGameInfo.gameMap[j][i] = ' ';
        }
    }

    loadStartGame();
    system("color F"); //Changed color to white
    //Get map from text file and save it
    myGameInfo = getMapFile(myGameInfo);

    myGameInfo.currentYear = 1945; //Year is 1945
    myGameInfo.currentGDP = 20000; //The stating US GDP is 2 trillion
    myGameInfo.currentIncome = 0.001; //The starting military funding is 0.001%
    myGameInfo.currentBalance = 0.5; //The current military balance is 500 million dollars


    //main loop of the game
    while(gameRun)
    {
        //Print out the map
        readMapArray(myGameInfo);

        //Ask for a input from the player
        myOptions[0] = "create a new base";
        myOptions[1] = "to refresh";
        myOptions[2] = "|| Finish Turn >>";
        displayMenu(myOptions, 3, myGameInfo);
        inputCommand = getAnswer(3, 1); //Get player input

        if(inputCommand == 1) //If player enters /spawn, create a base
        {
            myGameInfo = placeBase(myGameInfo, myOptions);
        }
        else if(inputCommand == 2)//To refresh
        {
            system("CLS");
        }
        else if(inputCommand >= 3)
        {
            myGameInfo = endTurn(myGameInfo);
        }
    }
    return 0;
}

gameInfo endTurn(gameInfo myGameInfo)
{
    float randomValue; //This number is randomly generated
    system("CLS"); //Clear console

    myGameInfo.currentYear ++;
    cout << "         >- [January 1, " << myGameInfo.currentYear << "]" << endl;

    randomValue = (rand()%4+1)/100.0;
    if(rand() % 5 == 0 && randomValue < 3 )
    {
        cout << "         >- Economy decreased by -> " << randomValue*100 << "%" << endl;
        myGameInfo.currentGDP -= myGameInfo.currentGDP*randomValue;
    }
    else
    {
        cout << "         >- Economy increased by -> " << randomValue*100 << "%" << endl;
        myGameInfo.currentGDP += myGameInfo.currentGDP*randomValue;
    }

    cout << "         >- GDP is Now:" << myGameInfo.currentGDP << endl;

    //Change income percent

    myGameInfo.currentBalance += (myGameInfo.currentGDP*myGameInfo.currentIncome)/100.0;
    cout << "         >- Current Department Anual Budget: " << myGameInfo.currentBalance << " billion dollars" << endl;

    system("PAUSE");
    return myGameInfo;
}

//This function is used to access the txt file and read the file line by line.
gameInfo getMapFile(gameInfo myGameInfo)
{
    std::string line;
    ifstream file_("MapFile.txt");

    int currentRow = 0;

    if(file_.is_open())
    {
        while(getline(file_,line)) //This function uses the builtin function: getline
        {
            myGameInfo = saveMapFile(line, myGameInfo, currentRow); //It then references the saveMapFile function in order to save it into a doubel array.
            currentRow += 1;
        }
        file_.close();
    }
    return myGameInfo;
}

//Saves the map from the txt file into a double array
gameInfo saveMapFile (std::string line, gameInfo myGameInfo, int currentRow)
{
    for(std::string::size_type i = 0; i < line.size(); ++i) //Running through every character
    {
       myGameInfo.gameMap[i][currentRow] = line[i];
    }
    return myGameInfo;
}

//simply runs through a for loop through each value of the array and prints them out to console
void readMapArray(gameInfo myGameInfo)
{
    for(int i = 0; i < 55; i++) //Read out the map double array
    {
        for(int j = 0; j < 199; j++)
        {
            if(myGameInfo.gameMap[j][i] == '@') //Everytime you encounter a @ sign, color it red
            {
                displayRedText("@", false);
            }
            else //Otherwise, color and display others in white
            {
                cout << myGameInfo.gameMap[j][i];
            }
        }
        cout << endl;
    }
    return;
}

//Function used to place a base anywhere on the map
gameInfo placeBase(gameInfo myGameInfo, string myOptions[])
{
    //Defining variables
    bool choosingLocation = false; //boolean that is used to check if the player is still choosing a lcation
    bool findingCoordinate = false; //Boolean that checks if an error has occured

    int inputCommand = 0; //Stirng to take inputs from player
    int saved_x; //Saves coordinate for the custom choice of coordinate feature
    int saved_y;

    cout << ">- Creating..." << endl << endl;
    choosingLocation = true;

    //Spawn base on position:
    myGameInfo.savedCharacter = myGameInfo.gameMap[100][20];
    myGameInfo.gameMap[100][20] = '@';

    //save current x and current y
    myGameInfo.current_x = 100;
    myGameInfo.current_y = 20;

    system("CLS");
    readMapArray(myGameInfo);

    while(choosingLocation)
    {
        //Print out what the player can do
        myOptions[0] = ">- Move around using keyboard";
        myOptions[1] = ">- to place on a custom coordinate";
        myOptions[2] = ">- to place base";
        myOptions[3] = ">- Cancel/exit";
        displayMenu(myOptions,4, myGameInfo);

        inputCommand = 0;
        inputCommand = getAnswer(4, 1);


        cout << "         >- Please use arrow keys or WASD" << endl;
        //If player inputs /k, activate keyboard mode
        while(inputCommand == 1)
        {
            //If specific key is pressed:
            if((GetKeyState('W') & 0x8000) || (GetKeyState(VK_UP) & 0x8000))
            {
                if((myGameInfo.current_y - 1) < 5 ) //Check to see if new position is legal
                {
                    displayRedText("         >- ERROR, item can not move there", true);
                    cout << "         >- Directive: Please type a different command" << endl;
                }
                else
                {
                    //Update position of base
                    myGameInfo = changePosition(myGameInfo, 0, -1, true);
                }
            }
            //Else if specific key is pressed:
            else if((GetKeyState('S') & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000))
            {
                if((myGameInfo.current_y + 1) > 45 ) //Check to see if new position is legal
                {
                    displayRedText("         >- ERROR, item can not move there", true);
                    cout << "         >- Directive: Please type a different command" << endl;
                }
                else
                {
                    //Update position of base
                    myGameInfo = changePosition(myGameInfo, 0, 1, true);
                }
            }
            //Else if specific key is pressed:
            else if((GetKeyState('A') & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000))
            {
                if((myGameInfo.current_x - 1) < 0 ) //Check to see if new position is legal
                {
                    displayRedText("         >- ERROR, item can not move there", true);
                    cout << "         >- Directive: Please type a different command" << endl;
                }
                else
                {
                    //Update position of base
                    myGameInfo = changePosition(myGameInfo, -1, 0, true);
                }
            }
            //Else if specific key is pressed:
            else if((GetKeyState('D') & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000))
            {
                if((myGameInfo.current_x + 1) > 199 ) //Check to see if new position is legal
                {
                    displayRedText("         >- ERROR, item can not move there", true);
                    cout << "         >- Directive: Please type a different command" << endl;
                }
                else
                {
                    //Update position of base
                    myGameInfo = changePosition(myGameInfo, 1, 0, true);
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
                cout << endl << "         >- Please enter your specific X-coordinate below between 3 and 198. Press 0 to exit" << endl;
                saved_x = getAnswer(198, 3);

                if(saved_x == 0) //If they choose to exit, exit
                {
                    findingCoordinate = false;
                }
                else
                {
                    if(saved_x <  3) saved_x = 3;

                    cout << endl << "         >- Please enter your specific Y-coordinate below between 3 and 43. Press 0 to exit" << endl;
                    saved_y = getAnswer(43, 3); //Get input for specific y-input

                    if(saved_y == 0)
                    {
                        findingCoordinate = false; //If player chooses to exit, exit
                    }
                    else
                    {

                        cout << "         >- Your coordinate is [" << saved_x << "," << saved_y << "]. Press 1 to confirm." << endl;
                        inputCommand = getAnswer(1, 0); //Get player confirmation for their input

                        if(inputCommand == 1) //If they answer yes, repeat process done above in keyboard mode
                        {
                            //Update position of base
                            myGameInfo = changePosition(myGameInfo, -myGameInfo.current_x + saved_x, -myGameInfo.current_y + saved_y, false);
                            findingCoordinate = false;
                        }
                    }
                }
            }while(findingCoordinate);
        }
        else if(inputCommand == 3)
        {
            cout << endl << "         >- Are you sure you want to place the base on [" << myGameInfo.current_x << "," << myGameInfo.current_y << "]? This action is not reversable. Press 1 to confirm." << endl;
            inputCommand = getAnswer(1, 0);

            system("CLS");
            readMapArray(myGameInfo);
            if(inputCommand == 1)
            {
                return myGameInfo;
            }
        }
        else if(inputCommand == 4)
        {
            cout << endl << "         >- You are Attempting to exit. Are you sure? Press 1 to quit" << endl;
            inputCommand = getAnswer(1, 0);

            system("CLS");
            readMapArray(myGameInfo);
            if(inputCommand == 1)
            {
                //wipe the base symbol from the map array
                myGameInfo.gameMap[myGameInfo.current_x][myGameInfo.current_y] = myGameInfo.savedCharacter;

                //For some reason the base character is not being wiped so I have to refresh two times
                system("CLS");
                readMapArray(myGameInfo);
                return myGameInfo;
            }
        }
        else
        {
            cout << endl << "         >- hmm, try choosing a number from 1-4" << endl;
        }
    }
}

//Functiont that will update the position of the base depending on the valeus inputted
gameInfo changePosition(gameInfo myGameInfo, int x_change, int y_change, bool usingKeyboard)
{
    myGameInfo.gameMap[myGameInfo.current_x][myGameInfo.current_y] = myGameInfo.savedCharacter; //Replace current position with the saved character
    myGameInfo.savedCharacter = myGameInfo.gameMap[myGameInfo.current_x + x_change][myGameInfo.current_y + y_change]; //Save the character of the future value
    myGameInfo.gameMap[myGameInfo.current_x + x_change][myGameInfo.current_y + y_change] = '@'; //Replace the future spot with an @ symbol
    myGameInfo.current_x = myGameInfo.current_x + x_change; //Update current position
    myGameInfo.current_y = myGameInfo.current_y + y_change;

    system("CLS"); //Wipe console
    readMapArray(myGameInfo); //Re-output map
    if(usingKeyboard)
    {
        displayRedText("         >- Press escape to exit keyboard mode", true); //Output warning/directions on how to exit
    }
    return myGameInfo; //return
}

//Game start menu
void loadStartGame()
{
    //Defining the variables
    string randInput = "";
    string userID = "";
    char ch;

    system("color A"); //Fake server connection animation
    cout << ">- -UNSC User Management System-" << endl << "================================" << endl << "________________________________" << endl;
    cout << "UNSC TacOS  v.337" <<  endl << "(S) 2294 FLEETCOM" << endl << "=======================" <<  endl << "|  User Log:" << endl;
    cout << "|  >> Administrator (UNSC ID 8384-C)" << endl << "|  >>> " << "unknown.GUEST_userGroup" << endl << endl;
    cout << "________________________________" << endl << "================================" << endl << endl << ">- Please enter your pin and ID" << endl << endl;
0
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

//Error trapping funcion that only accepts integers
float getAnswer (int maxLimit, int minLimit)
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
        else if(playerInput > maxLimit || playerInput < minLimit ) //Otherwise, print an error message
        {
            displayRedText("  ==================================================", true);
            cout << "  >- Please enter a number between " << minLimit << " and " << maxLimit << endl;
            displayRedText("  ==================================================", true);
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}

//Displays the menu
void displayMenu(string options[], int arraySize, gameInfo myGameInfo)
{
    cout << "         >- Please enter a direct command. Below are the primary listed commands.                                                      ";
    cout << "[January 1, " << myGameInfo.currentYear << "] <> Current Department Balance:" << myGameInfo.currentBalance<< " billion dollars" << endl;
    //Display instructions
    for(int i = 0; i < arraySize; i++)
    {
        cout << "         >- [" << i+1 << "] " << options[i] << endl;
    }
    return;
}

//Displays text in red
void displayRedText(string inputOne, bool returnTrue)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //HANDLE and hCOnsole are using the windows.h lbrary to color individual letters

    SetConsoleTextAttribute(hConsole, 12); //Set color to red
    cout << inputOne;
    SetConsoleTextAttribute(hConsole, 15); //Set color to red
    if(returnTrue)
    {
        cout << endl;
    }
}
