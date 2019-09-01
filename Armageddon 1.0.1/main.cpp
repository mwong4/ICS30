#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>   // WinApi header

using namespace std;

void getMapFile (char[][55]);
void saveMapFile (std::string, char[][55], int);
void readMapArray (char[][55], HANDLE);
void placeBase(char[][55], HANDLE);

int main()
{
    char gameMap [199][55];

    bool gameRun = true;
    bool gameStart = true;

    string inputCommand = "";

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Reset the map double array
    for(int i = 0; i < 55; i++)
    {
        for(int j = 0; j < 199; j++)
        {
            gameMap[j][i] = ' ';
        }
    }

    //Get map from text file
    getMapFile(gameMap);

    while(gameRun)
    {
        if(gameStart)
        {
           readMapArray(gameMap, hConsole);
           gameStart = false;
        }

        cout << ">- Please enter a direct command. Below are the primary listed commands." << endl;
        cout << "create a new base -> /spawn" << endl;
        cin >> inputCommand;

        if(inputCommand == "/spawn")
        {
            placeBase(gameMap, hConsole);

        }
        else if(inputCommand != "/spawn")
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

void getMapFile(char gameMap[][55])
{
    std::string line;
    ifstream file_("MapFile.txt");

    int currentRow = 0;

    if(file_.is_open())
    {
        while(getline(file_,line))
        {
            saveMapFile(line, gameMap, currentRow);
            currentRow += 1;
        }
        file_.close();
    }
    return;
}

void saveMapFile (std::string line, char gameMap [][55], int currentRow)
{
       for(std::string::size_type i = 0; i < line.size(); ++i)
    {
        //cout << line[i] << endl;
       gameMap[i][currentRow] = line[i];
    }
    return;
}

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

void placeBase(char gameMap[][55], HANDLE hConsole)
{

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    bool choosingLocation = false;
    bool errorOccured = false;

    string inputCommand = "";

    int current_x;
    int current_y;

    char savedCharacter;

    cout << ">- Creating..." << endl << endl;
    choosingLocation = true;

    savedCharacter = gameMap[100][20];
    gameMap[100][20] = '@';

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
            cout << endl << ">- Cancel -> /cancel" << endl;
        }
        errorOccured = false;


        inputCommand = " ";
        cin >> inputCommand;

        if(inputCommand == "/up" || inputCommand == "/UP" || inputCommand == "/U" || inputCommand == "/u")
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

        if(inputCommand == "/down" || inputCommand == "/DOWN" || inputCommand == "/D" || inputCommand == "/d")
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

        if(inputCommand == "/left" || inputCommand == "/LEFT" || inputCommand == "/L" || inputCommand == "/l")
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

        if(inputCommand == "/right" || inputCommand == "/RIGHT" || inputCommand == "/R" || inputCommand == "/r")
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

        if(inputCommand == "/cancel" || inputCommand == "/CANCEL" || inputCommand == "/C" || inputCommand == "/c")
        {
            cout << endl << ">- You are Attempting to exit. Are you sure? Press /y to quit" << endl;
            cin >> inputCommand;
            if(inputCommand == "y" || inputCommand == "Y" || inputCommand == "yes" || inputCommand == "YES")
            {
                  return;
            }
        }

        else if(inputCommand != "/up" && inputCommand != "/UP" && inputCommand != "/U" && inputCommand != "/u" && inputCommand != "/down" && inputCommand != "/DOWN" && inputCommand != "/D" && inputCommand != "/d" && inputCommand != "/left" && inputCommand != "/LEFT" && inputCommand != "/L" && inputCommand != "/l" && inputCommand != "/cancel" && inputCommand != "/CANCEL" && inputCommand != "/C" && inputCommand != "/c")
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

