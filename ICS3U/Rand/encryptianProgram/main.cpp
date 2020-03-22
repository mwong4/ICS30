#include <iostream>
#include <vector> //For vectors
#include <fstream>  //For txt file
#include <string> //to convert char to string (push_back())
#include <windows.h> //for system pause

using namespace std;

struct Line
{
    vector<char> characters; //This represents the characters in the line
    int vecSize; //This represents the length of the line
};

struct Key
{
    char value; //This is the real value
    char assocVal;  //This is it's encrypted counterpart
};

void writeFile(vector<Line>, int); //This function is in charge of saving the vector into the txt file
void wipeFile(); //Wipe file
void readKey(vector<Key>*); //This saves the key into the system
void readData(vector<Line>*, int*); //This saves the data into the system
void scrambleData(vector<Line>*, vector<Key>, int); //This is used to scramble the values of the data
void unscrambleData(vector<Line>*, vector<Key>, int); //This is used to unscramble the data

int main()
{
    vector<Line> text; //This represents the whole text
    int textSize = 0; //This records the length of the text size

    vector<Key> keyChain; //This is the encryptian key

    int playerChoice = 1;

    readKey(&keyChain); //read keys
    readData(&text, &textSize); //read data

    while(playerChoice > 0 && playerChoice < 4)
    {
        playerChoice = 0; //reset choice
        cout <<  endl << " ////////////////////////////// " << endl;
        cout << "Please choose an option (1 to encrypt, 2 to decrypt, 3 to reread)" << endl;
        cin >> playerChoice;

        if(playerChoice == 1)
        {
            scrambleData(&text, keyChain, textSize); //scramble data
            wipeFile(); //put back into file
            writeFile(text, textSize);
        }
        if(playerChoice == 2)
        {
            unscrambleData(&text, keyChain, textSize); //unscramble data
            wipeFile(); //put back into file
            writeFile(text, textSize);
        }
        if(playerChoice == 3)
        {
            //reset keys
            keyChain.clear();

            //reset lines
            text.clear();

            //reset text size
            textSize = 0;

            readKey(&keyChain); //read keys
            readData(&text, &textSize); //read data
            cout << ">reread files complete" << endl;
        }
    }
    return 0;
}


//This function is in charge of saving the vector into the txt file
void writeFile(vector<Line> _lines, int _size)
{
    ofstream file; //this is the file to be encrytped
    file.open("file.txt"); //Open files

    string tempString; //this is to temporarily save a string to be placed into the file

    for(int i = 0; i < _size ; i++) //Write to files
    {
        for(int j = 0; j < _lines[i].vecSize; j++) //run through every char in the line
        {
            tempString.push_back(_lines[i].characters[j]); //save to string
        }
        file << tempString << endl; //write string into file
        tempString = ""; //reset temp string
    }

    file.close(); //Close file
    return;
}

//Wipe file
void wipeFile()
{
    std::ofstream file; //This is the input file
    file.open("file.txt", std::ofstream::out | std::ofstream::trunc); //wipe file
    file.close(); //close file
    return;
}

//This saves the key into the system
void readKey(vector<Key>* _keychain)
{
    std::string line; //String line used to seperate the text file into lines
    ifstream key_("key.txt"); //This is the key file
    Key tempKey; //This is a temporary key


    if(key_.is_open()) //If instricted to save the file
    {
        while(getline(key_,line)) //This function uses the builtin function: getline
        {
            //Save spot in double array with specific corresponding char and spot
            tempKey.value =  line[0];
            tempKey.assocVal =  line[1];

            (*_keychain).push_back(tempKey);
        }
        key_.close(); //Close file
    }
    cout << ">key read" << endl;
    return;
}

//This saves the data into the system
void readData(vector<Line>* _text, int* _size)
{
    std::string line; //String line used to seperate the text file into lines
    ifstream file_("file.txt"); //This is the text file
    Line tempLine; //This is a temporary line in the text


    if(file_.is_open())
    {
        while(getline(file_,line)) //This function uses the builtin function: getline
        {
            *_size += 1;
            tempLine.vecSize = 0;
            tempLine.characters.clear();
            //Save spot in double array with specific corresponding char and spot
            for(std::string::size_type i = 0; i < line.size(); ++i) //Running through every character
            {
                tempLine.characters.push_back(line[i]);
                tempLine.vecSize ++;
            }
            (*_text).push_back(tempLine);
        }
        file_.close(); //Close file
    }
    cout << ">file read" << endl;
    return;
}

//This is used to scramble the values of the data
void scrambleData(vector<Line>* _text, vector<Key> _keychain, int _size)
{
    int counter = 0; //this is a temporary counter
    for(int i = 0; i < _size; i++) //go through each line in text
    {
        for(int j = 0; j < (*_text)[i].vecSize; j++) //In each character in the line:
        {
            if((*_text)[i].characters[j] != ' ')
            {
                while((*_text)[i].characters[j] != _keychain[counter].value && counter < 62) //Go through the database
                {

                    //debug logs
                    //cout << (*_text)[i].characters[j] << _keychain[counter].value << " i: " << i << " j: " << j << " counter: " << counter << " vecsize: " << (*_text)[i].vecSize << endl;
                    counter ++; //everytime a match is not found with keychain database, increase counter
                }

                if(counter < 62)
                {
                    //if match is found:
                    (*_text)[i].characters[j] = _keychain[counter].assocVal; //Swap value in text for the associated encryted value
                }
                counter = 0; //reset counter
            }
        }
    }
    cout << ">file scrambled" << endl;
    return;
}

//This is used to unscramble the data
void unscrambleData(vector<Line>* _text, vector<Key> _keychain, int _size)
{
    int counter = 0; //this is a temporary counter
    for(int i = 0; i < _size; i++) //go through each line in text
    {
        for(int j = 0; j < (*_text)[i].vecSize; j++) //In each character in the line:
        {
            if((*_text)[i].characters[j] != ' ')
            {
                while((*_text)[i].characters[j] != _keychain[counter].assocVal && counter < 62) //Go through the database
                {
                    counter ++; //everytime a match is not found with keychain database, increase counter
                }

                if(counter < 62)
                {
                    //if match is found:
                    (*_text)[i].characters[j] = _keychain[counter].value; //Swap value in text for the associated encryted value
                }
                counter = 0; //reset counter
            }
        }
    }
    cout << ">file unscrambled" << endl;
    return;
}
