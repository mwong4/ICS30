#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void getMapFile (char[][99]);
void saveMapFile (std::string, char[][99], int);
void readMapArray (char[][99]);

int main()
{
    char gameMap [199][99];

    bool gameRun = true;

    //Reset the map double array
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 200; j++)
        {
            gameMap[j][i] = ' ';
        }
    }

    //Get map from text file
    getMapFile(gameMap);

    readMapArray(gameMap);





    return 0;
}

void getMapFile(char gameMap[][99])
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

void saveMapFile (std::string line, char gameMap [][99], int currentRow )
{
       for(std::string::size_type i = 0; i < line.size(); ++i)
    {
        //cout << line[i] << endl;
       gameMap[i][currentRow] = line[i];
    }
    return;
}

void readMapArray( char gameMap [][99] )
{
    //Read out the map double array
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 200; j++)
        {
            cout << gameMap[j][i];
        }
        cout << endl;
    }
}

