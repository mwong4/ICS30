/*
>- Author: Max Wong
>- Date: June 9, 2020
>- Updated: June 9, 2020
>- Purpose: To track mia's sleep habits

To Do
Graph
*/

#include <iostream>
#include <vector> //For vectors
#include <stdlib.h>
#include <fstream>  //For txt file
#include <limits>     //For error trapping
#include <cmath> //For rounding

using namespace std;

struct Entry
{
    string date; //Date that the event occured
    int type; //This represents where she chose to sleep
    //1 = Alone, 2 = Parents room, 3 = with parents in own room
};

void showStocks(int*, vector<Entry>); //This function is in charge of displaying all your stocks
void resetVector(vector<Entry>*, int*); //This function is used to find each line in the stock file and save it into the vector
void getAnswer(int, int, int*); //Function used to get the players response as an integer (with error trapping)
void writeFile(vector<Entry>*, int*); //This function is in charge of saving the vector into the txt file
void wipeFile(); //Wipe file

void analyzeData(int*, vector<Entry>); //Gives % breakdown and a graph

int main()
{
    int index = 0; //how many entries are there?
    vector<Entry> sleepEntries; //All entries

    int input = 0;
    int secondInput = 0;
    Entry tempEntry;

    resetVector(&sleepEntries, &index);

    while(input != 4)
    {
        //Get user input
        cout << ">- Hello world!" << endl;
        cout << ">- [1] to show all entries" << endl;
        cout << ">- [2] to add entry" << endl;
        cout << ">- [3] to refresh data" << endl;
        cout << ">- [4] to quit" << endl;
        getAnswer(4, 1, &input);

        if(input == 1)
        {
            cout << "loading..." << endl;
            showStocks(&index, sleepEntries);
            analyzeData(&index, sleepEntries);
        }
        else if(input == 2)
        {
            //Get data
            cout << ">- Please enter type| 1 Alone | 2 Parents Room | 3 W/ Someone |" << endl;
            getAnswer(3, 1, &secondInput);

            if(secondInput == 1)
            {
                tempEntry.type = 1;
            }
            else if(secondInput == 2)
            {
                tempEntry.type = 2;
            }
            else
            {
                tempEntry.type = 3;
            }
            cout << ">- Please enter date in numbers. Ex: June 9, 2020 -> 2020/6/9" << endl;
            tempEntry.date = "0";
            cin >> tempEntry.date;
            //push data into files
            sleepEntries.push_back(tempEntry);
            index ++;
            //sleepEntries.insert(sleepEntries.begin(), tempEntry); //insert to front

            //Save data into disk as txt
            wipeFile(); //wipe file
            writeFile(&sleepEntries, &index); //save into file
            resetVector(&sleepEntries, &index); //reset vector
        }
        else if(input == 3)
        {
            resetVector(&sleepEntries, &index);
        }
        system("PAUSE"); //Pause before resetting
        system("CLS");
    }
    cout << "quitting..." << endl;
    return 0;
}

//This function is in charge of displaying all your entries
void showStocks(int* _entryCount, vector<Entry> _entries)
{
    for(int i = 0; i < *_entryCount; i++)
    {
        cout << " >- " << i+1 << ". Type|| ";

        if(_entries[i].type == 1)
        {
            cout << "Alone";
        }
        else if(_entries[i].type == 2)
        {
            cout << "Parents Room";
        }
        else
        {
            cout << "W/ someone";
        }
        cout << endl;
        cout << " >- Date|| " << _entries[i].date << endl << endl;
    }
    return;
}

//This function is used to find each line in the stock file and save it into the vector
void resetVector(vector<Entry>* _entries, int* _size)
{
    string line; //String line used to seperate the text file into lines
    ifstream file_("data.txt"); //This is the file
    Entry tempEntry; //This is a temporary entry
    *_size = 0;

    int lineRow = 0; //This integer keeps count of the row number for the saving in array

        while(getline(file_,line)) //This function uses the builtin function: getline
        {
            if(lineRow % 2 == 0)
            {
                tempEntry.type = atoi(line.c_str());
            }
            else if(lineRow % 2 == 1)
            {
                tempEntry.date = line;
                (*_entries).push_back(tempEntry);
                *_size += 1;
            }
            lineRow += 1;
        }
        file_.close(); //Close file
    return;
}

//Error trapping funcion that only accepts integers
void getAnswer (int _maxLimit, int _minLimit, int* _value)
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
            cout << " >- Please enter  valid input" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if(playerInput > _maxLimit || playerInput < _minLimit ) //Otherwise, print an error message
        {
            cout << "  >- Please enter a number between " << _minLimit << " and " << _maxLimit << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }
    while(findingInput);
    *_value = playerInput;//Otherwise input is good, return input
    return;
}

//This function is in charge of saving the vector into the txt file
void writeFile(vector<Entry>* _entries, int* _size)
{
    ofstream myfile;
    myfile.open("data.txt"); //Open files

    for(int i = 0; i < *_size ; i++) //Write to files
    {
        myfile << (*_entries)[i].type << endl;
        myfile << (*_entries)[i].date << endl;
    }
    myfile.close(); //Close files
    return;
}

//Wipe file
void wipeFile()
{
    std::ofstream myFile;
    myFile.open("data.txt", std::ofstream::out | std::ofstream::trunc);
    myFile.close();
    return;
}

//Gives % breakdown and a graph
void analyzeData(int* _size, vector<Entry> _entries)
{
    //counter variables
    float totalOne = 0;
    float totalTwo = 0;
    float totalThree = 0;

    for(int i = 0; i < *_size; i++)
    {
        if(_entries[i].type == 1)
        {
            totalOne ++;
        }
        else if(_entries[i].type == 2)
        {
            totalTwo ++;
        }
        else
        {
            totalThree ++;
        }
    }

    cout << endl << "///////////////////////Results///////////////////////" << endl << endl;

    cout << "   [Total Breakdown]" << endl;
    cout << ">- Alone " << (totalOne / (totalOne + totalTwo + totalThree))*100 << "%  (" << totalOne << "/" << (totalOne + totalTwo + totalThree) << ")" << endl;
    cout << ">- Parents Room " << (totalTwo / (totalOne + totalTwo + totalThree))*100 << "%  (" << totalTwo << "/" << (totalOne + totalTwo + totalThree) << ")" << endl;
    cout << ">- W/ Someone, in own room " << (totalThree / (totalOne + totalTwo + totalThree))*100 << "%  (" << totalThree << "/" << (totalOne + totalTwo + totalThree) << ")" << endl << endl;

    cout << "   [Alone vs. With]" << endl;
    cout << ">- Alone " << (totalOne / (totalOne + totalTwo + totalThree))*100 << "%  (" << totalOne << "/" << (totalOne + totalTwo + totalThree) << ")" << endl;
    cout << ">- W/ someone " << ((totalTwo + totalThree) / (totalOne + totalTwo + totalThree))*100 << "%  (" << (totalTwo + totalThree) << "/" << (totalOne + totalTwo + totalThree) << ")" << endl << endl;

    cout << "# = Alone" << endl << "_ = W/ Someone" << endl;
    cout << endl << ">- [";
    for(int i = 0; i < round((totalOne / (totalOne + totalTwo + totalThree))/0.05); i++)
    {
        cout << "#";
    }
    for(int i = 0; i < round(((totalTwo + totalThree) / (totalOne + totalTwo + totalThree))/0.05); i++)
    {
        cout << "_";
    }
    cout << "]" << endl;
}
