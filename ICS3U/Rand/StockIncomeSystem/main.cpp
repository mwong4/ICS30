/*
>- Author: Max Wong
>- Date: February 11, 2019
>- Updated: April 25, 2020
>- Purpose: To write a program to practice vectors

To Do
Link image file

extra info
    display
    adding stocks
*/

#include <iostream>
#include <vector> //For vectors
#include <stdlib.h>
#include <fstream>  //For txt file
#include <limits>     //For error trapping

using namespace std;

struct Stock
{
    string name; //This represents the name of the stock
    int cost; //This represents the cost of the stock
    int dividend; //This represents the income the stock brings
    string status; //This represents the status of the stock
    string emptyFiller; //This is a filler string

    //extra info
    string extraInfo; //This contains any extra info stored as a chain
};


struct UserData
{
    int index; //This represents how many items are in the vector
    float balance; //This represents the amout of money you have
    vector<Stock> ownedStock; //This vector saves all the stock you have
};


void showStocks(int*, vector<Stock>); //This function is in charge of displaying all your stocks
int countIncome(int*, vector<Stock>); //This function is in charge of finding and returning your monthly income
void resetData(UserData*); //This resets user data as the initializer
void updateMonth(UserData*); //This ends your turn/month
void resetVector(vector<Stock>*, int*, int); //This function is used to find each line in the stock file and save it into the vector
void getAnswer(int, int, int*); //Function used to get the players response as an integer (with error trapping)
void writeFile(vector<Stock>*, int*, int); //This function is in charge of saving the vector into the txt file
void wipeFile(int); //Wipe file
void addStock(vector<Stock>*, int*); //Used to add a new stock

int main()
{
    UserData myData; //Declaring the struct to save user data
    resetData(&myData); //Initialize/reset data

    int inputValue = 0; //This int represents what the player inputs

    vector<Stock> stockSelection; //This vector represents the available stocks
    int selectionSize = 0; //This determines the size of the selection

    //Get the stocks selection
    resetVector(&stockSelection, &selectionSize, 1);

    //Get user owned stocks
    resetVector(&myData.ownedStock, &myData.index, 2);

    while(inputValue < 5)
    {
        cout << " >- Welcome, You have: " << myData.balance << " hundred thousand dollars" << endl;
        cout << " >- Your monthly income is: " << countIncome(&myData.index, myData.ownedStock) << " hundred thousand dollars" << endl;
        cout << " >- Press 1 to see stocks" << endl << " >- Press 2 to end month" << endl << " >- Press 3 to show my stocks" << endl << " >- Press 4 to add a stock" << endl;
        getAnswer(4, 1, &inputValue);

        if(inputValue == 1)
        {
            cout << " >- Loading stock selection" << endl << endl;
            cout << " >- Please select the stock to purchase:" << endl;
            showStocks(&selectionSize, stockSelection);
            cout << cout << " >- " << selectionSize + 1 << ". To exit" << endl;
            getAnswer(selectionSize + 1, 1, &inputValue);

            if(inputValue != selectionSize + 1)
            {
                if(myData.balance > stockSelection[inputValue-1].cost)
                {
                    if(stockSelection[inputValue-1].status == "unsold")
                    {
                        stockSelection[inputValue-1].status = "sold";
                        myData.balance -= stockSelection[inputValue-1].cost; //Subtract from budget to purchase
                        myData.ownedStock.push_back(stockSelection[inputValue-1]); //Add element to vector
                        myData.index ++; //Add to index
                    }
                    else
                    {
                        cout << " >- You have already bought the stock" << endl;
                    }
                }
                else
                {
                    cout << " >- You do not have enough money" << endl;
                }
            }

            inputValue = 1;
            system("PAUSE");
            system("CLS");
        }
        else if(inputValue == 2)
        {
            cout << " >- Ending month.... Updating balance" << endl;
            system("CLS");
            updateMonth(&myData);
            system("PAUSE");
        }
        else if(inputValue == 3)
        {
            cout << " >- Loading my stocks" << endl;
            cout << " >- Please select the stock to sell:" << endl;
            showStocks(&myData.index, myData.ownedStock);
            cout << " >- " << myData.index + 1 << ". To exit" << endl;
            getAnswer(myData.index + 1, 1, &inputValue);

            if(inputValue != myData.index + 1)
            {
                myData.balance += myData.ownedStock[inputValue-1].cost; //Seel your item and get money
                myData.ownedStock.erase(myData.ownedStock.begin() + inputValue-1); //Erase the chosen element
                myData.index --; //Decrease index
            }
            inputValue = 3;
            system("PAUSE");
            system("CLS");
        }
        else if(inputValue == 4)
        {
            addStock(&stockSelection, &selectionSize); //call function to add a stock
            system("PAUSE");
            system("CLS");
        }
    wipeFile(1); //Wipe file
    writeFile(&myData.ownedStock, &myData.index, 1); //Update my stock file
    }
    return 0;
}

//This function is in charge of displaying all your stocks
void showStocks(int* _stockCount, vector<Stock> _stocks)
{
    for(int i = 0; i < *_stockCount; i++)
    {
        cout << " >- " << i+1 << ". Name|| " << _stocks[i].name << endl;
        cout << " >- Cost|| " << _stocks[i].cost << endl;
        cout << " >- Return/m|| " << _stocks[i].dividend << endl;
        cout << " >- Status|| " << _stocks[i].status << endl;
        cout << " >- empty|| " << _stocks[i].emptyFiller << endl;
        cout << " >- Extra Info|| " << _stocks[i].extraInfo << endl << endl;
    }
    return;
}

//This function is in charge of finding and returning your monthly income
int countIncome(int* _stockCount, vector<Stock> _stocks)
{
    int totalIncome = 0;
    for(int i = 0; i < *_stockCount; i++)
    {
        totalIncome += _stocks[i].dividend;
    }
    return totalIncome;
}

//This resets user data as the initializer
void resetData(UserData* _data)
{
    (*_data).index = 0; //Start with 0 stocks
    (*_data).balance = 10; //Start with 10 million dollars
    return;
}

//This ends your turn/month
void updateMonth(UserData* _data)
{
    (*_data).balance += countIncome(&(*_data).index, (*_data).ownedStock);
    return;
}

//Used to add a new stock
void addStock(vector<Stock>* _stocks, int* _size)
{
    Stock tempStock; //This is a temporary stock

    //Get user input to the new stock
    cout << " >- What is the name of the stock?" << endl;
    cin >> tempStock.name;
    cout << " >- What is the cost of the stock?" << endl;
    cin >> tempStock.cost;
    cout << " >- What is the dividend return of the stock?" << endl;
    cin >> tempStock.dividend;
    cout << " >- What is the status of the stock?" << endl;
    cin >> tempStock.status;
    cout << " >- Filler Value" << endl;
    cin >> tempStock.emptyFiller;
    cout << " >- What extra information would you like?" << endl;
    cin >> tempStock.extraInfo;

    (*_stocks).push_back(tempStock); //Push stock to list
    *_size += 1; //Update index

    wipeFile(2); //Wipe file
    writeFile(_stocks, _size, 2); //Update the stock file
    return;
}

//This function is used to find each line in the stock file and save it into the vector
void resetVector(vector<Stock>* _stocks, int* _size, int _file)
{
    string line; //String line used to seperate the text file into lines
    ifstream stockFile_("Stocks.txt"); //This is the map file
    ifstream myStocksFile_("myStocks.txt"); //This is the map file
    Stock tempStock; //This is a temporary stock

    int lineRow = 0; //This integer keeps count of the row number for the saving in array

    if(stockFile_.is_open() && _file == 1) //If instricted to save the file
    {
        while(getline(stockFile_,line)) //This function uses the builtin function: getline
        {
            if(lineRow % 6 == 0)
            {
                tempStock.name = line;
            }
            else if(lineRow % 6 == 1)
            {
                tempStock.cost = atoi(line.c_str());
            }
            else if(lineRow % 6 == 2)
            {
                tempStock.dividend = atoi(line.c_str());
            }
            else if(lineRow % 6 == 3)
            {
                tempStock.status = line;
            }
            else if(lineRow % 6 == 4)
            {
                tempStock.emptyFiller = line;
            }
            else if(lineRow % 6 == 5)
            {
                tempStock.extraInfo = line;
                (*_stocks).push_back(tempStock);
                *_size += 1;
            }
            lineRow += 1;
        }
        stockFile_.close(); //Close file
    }
    else if(myStocksFile_.is_open() && _file == 2) //If instricted to save the file
    {
        while(getline(myStocksFile_,line)) //This function uses the builtin function: getline
        {
            if(lineRow % 6 == 0)
            {
                tempStock.name = line;
            }
            else if(lineRow % 6 == 1)
            {
                tempStock.cost = atoi(line.c_str());
            }
            else if(lineRow % 6 == 2)
            {
                tempStock.dividend = atoi(line.c_str());
            }
            else if(lineRow % 6 == 3)
            {
                tempStock.status = line;
            }
            else if(lineRow % 6 == 4)
            {
                tempStock.emptyFiller = line;
            }
            else if(lineRow % 6 == 5)
            {
                tempStock.extraInfo = line;
                (*_stocks).push_back(tempStock);
                *_size += 1;
            }
            lineRow += 1;
        }
        myStocksFile_.close(); //Close file
    }
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
void writeFile(vector<Stock>* _stocks, int* _size, int _file)
{
    ofstream myfile;
    ofstream stockFile;
    if(_file == 1) myfile.open("myStocks.txt"); //Open files
    else if(_file == 2) stockFile.open("Stocks.txt");

    for(int i = 0; i < *_size ; i++) //Write to files
    {
        if(_file == 1)
        {
            myfile << (*_stocks)[i].name << endl;
            myfile << (*_stocks)[i].cost << endl;
            myfile << (*_stocks)[i].dividend << endl;
            myfile << (*_stocks)[i].status << endl;
            myfile << (*_stocks)[i].emptyFiller << endl;
            myfile << (*_stocks)[i].extraInfo << endl;
        }
        else if(_file == 2)
        {
            stockFile << (*_stocks)[i].name << endl;
            stockFile << (*_stocks)[i].cost << endl;
            stockFile << (*_stocks)[i].dividend << endl;
            stockFile << (*_stocks)[i].status << endl;
            stockFile << (*_stocks)[i].emptyFiller << endl;
            stockFile << (*_stocks)[i].extraInfo << endl;
        }
    }

    if(_file == 1) myfile.close(); //Close files
    else if(_file == 2) stockFile.close();
    return;
}

//Wipe file
void wipeFile(int _file)
{
    std::ofstream myStock;
    std::ofstream stock;
    if(_file == 1)
    {
        myStock.open("myStocks.txt", std::ofstream::out | std::ofstream::trunc);
        myStock.close();
    }
    else if(_file == 2)
    {
        stock.open("Stocks.txt", std::ofstream::out | std::ofstream::trunc);
        stock.close();
    }
    return;
}
