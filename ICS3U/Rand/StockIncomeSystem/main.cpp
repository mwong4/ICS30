/*
>- Author: Max Wong
>- Date: February 11, 2019
>- Updated: October 23, 2020
>- Purpose: To write a program to practice vectors and pointers

To Do
Link image file
Auction system
    bidding intervals
    making auction only appear once in a while
*/

#include <iostream>
#include <vector>     //For vectors
#include <stdlib.h>
#include <fstream>    //For txt file
#include <limits>     //For error trapping
#include <tgmath.h>   //For rounding
#include <stdio.h>    //For NULL (srand)
#include <stdlib.h>   //For srand, rand
#include <time.h>     //For time
#include <conio.h>    //For getch()
#include <windows.h>  //For key detection

using namespace std;

struct Stock
{
    string name; //This represents the name of the stock
    int cost; //This represents the cost of the stock
    int dividend; //This represents the income the stock brings
    string status; //This represents the status of the stock
    int timeOwned; //This is a filler string
    bool triedSelling; //to prevent spamming the selling button

    //extra info
    string extraInfo; //This contains any extra info stored as a chain
};


struct UserData
{
    int index; //This represents how many items are in the vector
    float balance; //This represents the amout of money you have
    int timeKeeper; //keeps track of the time
    vector<Stock> ownedStock; //This vector saves all the stock you have
};


void showStocks(int*, vector<Stock>, int); //This function is in charge of displaying all your stocks
float countIncome(int*, vector<Stock>); //This function is in charge of finding and returning your monthly income
void resetData(UserData*); //This resets user data as the initializer
void updateMonth(UserData*); //This ends your turn/month
void resetVector(vector<Stock>*, int*, int, float*, int*); //This function is used to find each line in the stock file and save it into the vector
void getAnswer(int, int, int*); //Function used to get the players response as an integer (with error trapping)
void writeFile(vector<Stock>*, int*, int, float*, int*); //This function is in charge of saving the vector into the txt file
void wipeFile(int); //Wipe file
void addStock(vector<Stock>*, int*, float*, int*); //Used to add a new stock
void searchName(vector<Stock>*, int, int*, string); //For finding a stock by name
void searchLetter(vector<Stock>*, int, vector<int>*, int*, char); //For finding stocks by first letter
void searchRange(vector<Stock>*, int, vector<int>*, int*, int, int); //For finding stocks with range
void auctionMode(vector<Stock>*, int, vector<Stock>*, int*, float*, int*); //For the auction system

//For auction mode
const int AUCTIONLIMIT = 7000; //This is how long the auction timer goes before time is up
const int BASEODDS = 30; //This is the baseline % odds at the price of stock in 100s
const int RANDRANGE = 3; //This is the range od deviation that the odds have for the ai's interest

int main()
{
    srand (time(NULL)); //Randomize seed according to time

    UserData myData; //Declaring the struct to save user data
    resetData(&myData); //Initialize/reset data

    int inputValue = 0; //This int represents what the player inputs
    int savedNumber = 0; //For saving a number temp
    int markup = 0; //How much the player is willing to mark up their product
    int counter = 0; //For search function/system
    int randNum = 0; //Rand num assigned by the computer

    string keyWord = " ";
    char keyLetter = ' ';
    int rangeMax = 0;
    int rangeMin = 0;
    vector<int> foundResults;
    int resultSize = 0;
    int result = 0;

    vector<Stock> stockSelection; //This vector represents the available stocks
    int selectionSize = 0; //This determines the size of the selection

    //Get the stocks selection
    resetVector(&stockSelection, &selectionSize, 1, &myData.balance, &myData.timeKeeper);

    //Get user owned stocks
    resetVector(&myData.ownedStock, &myData.index, 2, &myData.balance, &myData.timeKeeper);

    while(inputValue < 7)
    {
        cout << " >- Welcome, You have: ~" << round(myData.balance) << " hundred thousand dollars" << endl;
        cout << " >- Your monthly income is: ~" << countIncome(&myData.index, myData.ownedStock) << " hundred thousand dollars" << endl;
        cout << " >- Current Month Count: ||" << myData.timeKeeper << "||" << endl;
        cout << " >- Press 1 to see stocks" << endl << " >- Press 2 to end month" << endl << " >- Press 3 to show my stocks" << endl << " >- Press 4 to add a stock" << endl << " >- Press 5 to search stock selection" << endl << " >- Press 6 to check auction" << endl;
        getAnswer(6, 1, &inputValue);

        if(inputValue == 1)
        {
            cout << " >- Loading stock selection" << endl << endl;
            cout << " >- Please select the stock to purchase:" << endl;
            showStocks(&selectionSize, stockSelection, 1);
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

                        wipeFile(2); //Wipe file
                        writeFile(&stockSelection, &selectionSize, 2, &myData.balance, &myData.timeKeeper); //Update my stock file
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
            cout << endl << " >- Loading my stocks" << endl;
            cout << " >- Please select a stock:" << endl << endl;
            showStocks(&myData.index, myData.ownedStock, 2);
            cout << " >- " << myData.index + 1 << ". To exit" << endl;
            getAnswer(myData.index + 1, 1, &inputValue);

            if(inputValue != myData.index + 1)
            {
                cout << endl << "////////////////////////////////////////////////////////////////" << endl << endl;
                savedNumber = inputValue; //save number temp

                //get player input
                cout << " >- 1 To Sell Stock. 2 To Upgrade Stock. 3 To Exit" << endl;
                cout << ">- Upgrade cost: $" << round(myData.ownedStock[savedNumber-1].cost*0.2) << endl;
                getAnswer(3, 1, &inputValue);

                if(inputValue == 1)
                {
                    if(!myData.ownedStock[savedNumber-1].triedSelling)
                    {
                        cout << " >- Please enter a markup: "; //get player's markup
                        getAnswer(2000, -myData.ownedStock[savedNumber-1].cost, &markup);

                        //Display availability
                        cout << " >- Action Available: ";
                        if(myData.ownedStock[savedNumber-1].triedSelling) cout << "No" << endl;
                        else cout << "Yes" << endl;
                        //Display Chanced
                        cout << " >- Chance of success: " << 100 - round((markup*150)/myData.ownedStock[savedNumber-1].cost) - 20 + myData.ownedStock[savedNumber-1].timeOwned*1.5 << "%" << endl;
                        //Breakdown
                        cout << "             >- 100% - 20%(Base) - " << round((markup*150)/myData.ownedStock[savedNumber-1].cost) << "%(For Markup) + " << myData.ownedStock[savedNumber-1].timeOwned*1.5 << "%(Time Owned)" << endl;
                        //Revenue
                        cout << " >- Approximate Revenue: " << round(myData.ownedStock[savedNumber-1].cost + myData.ownedStock[savedNumber-1].cost*0.001*myData.ownedStock[savedNumber-1].timeOwned + markup) << endl << endl;

                        cout << " >- Are you sure? Press 1 for Yes. 2 for No" << endl;
                        getAnswer(2, 1, &inputValue);
                        if(inputValue == 1)
                        {   //Spin the lottery wheel!
                            if(rand()%100 > 100 - round((markup*150)/myData.ownedStock[savedNumber-1].cost) - 20 + myData.ownedStock[savedNumber-1].timeOwned*2)
                            {
                                cout << " >- Selling Failed" << endl;
                                myData.ownedStock[savedNumber-1].triedSelling = true;
                            }
                            else
                            {
                                cout << " >- Sold Success" << endl;
                                myData.balance += round(myData.ownedStock[savedNumber-1].cost + myData.ownedStock[savedNumber-1].cost*0.001*myData.ownedStock[savedNumber-1].timeOwned + markup); //Seel your item and get money
                                myData.ownedStock.erase(myData.ownedStock.begin() + savedNumber-1); //Erase the chosen element
                                myData.index --; //Decrease index

                                counter = 0;
                                while(myData.ownedStock[savedNumber-1].name != stockSelection[counter].name) //Search for sold stock in stock selection
                                {
                                    counter ++;
                                }
                                if(myData.ownedStock[savedNumber-1].name == stockSelection[counter].name) //Safety check
                                {
                                    cout << "changed" << endl;
                                    stockSelection[counter].status = "unsold"; //Set to unsold
                                }
                            }
                        }
                    }
                    else cout << " >- Action not available" << endl;
                }
                else if(inputValue == 2)
                {
                    if(myData.balance >= round(myData.ownedStock[savedNumber-1].cost*0.2)) //If they have enough money
                    {   //Update stock information with upgraded data
                        myData.ownedStock[savedNumber-1].cost += round(myData.ownedStock[savedNumber-1].cost*0.1);
                        myData.ownedStock[savedNumber-1].dividend += round(myData.ownedStock[savedNumber-1].dividend*0.15);
                        myData.balance -= round(myData.ownedStock[savedNumber-1].cost*0.2);
                        wipeFile(1); //Wipe file
                        writeFile(&myData.ownedStock, &myData.index, 1, &myData.balance, &myData.timeKeeper); //Update my stock file
                    }
                    else //Print erro rotherwise
                    {
                        cout << " >- You do not have enough money" << endl;
                    }
                }
            }
            inputValue = 3;
            system("PAUSE");
            system("CLS");
        }
        else if(inputValue == 4)
        {
            addStock(&stockSelection, &selectionSize, &myData.balance, &myData.timeKeeper); //call function to add a stock
            system("PAUSE");
            system("CLS");
        }
        else if(inputValue == 5)
        {
            cout << endl << " >- What would you like to search with" << endl; //Display options and get input
            cout << " >- [1] To search by name" << endl << " >- [2] To search by first letter" << endl << " >- [3] To search by cost range" << endl << " >- [4] To quit" << endl;
            getAnswer(3, 1, &inputValue);

            if(inputValue == 1) //If user chooses to search by name
            {
                cout << endl << " >- Please enter the name" << endl;
                cin >> keyWord;

                searchName(&stockSelection, selectionSize, &result, keyWord); //Call function to search for a match

                if(result != 1000)
                {
                    cout << " >- " << result+1 << ". Name|| " << stockSelection[result].name << endl;
                    cout << " >- Cost|| " << stockSelection[result].cost << endl;
                    cout << " >- Return/m|| " << stockSelection[result].dividend << endl;
                    cout << " >- Status|| " << stockSelection[result].status << endl;
                    cout << " >- Months Owned|| " << stockSelection[result].timeOwned << endl;
                    cout << " >- Extra Info|| " << stockSelection[result].extraInfo << endl << endl;

                    if(stockSelection[result].status == "unsold" && myData.balance > stockSelection[result].cost) //If stock is unsold offer purchase offer
                    {
                        cout << endl << " >- Would you like to purchase? Press 1 for Yes, 2 for No" << endl;
                        getAnswer(2, 1, &inputValue);
                        if(inputValue == 1) //If they say yes, purchase stock
                        {
                            stockSelection[result].status = "sold";
                            myData.balance -= stockSelection[result].cost; //Subtract from budget to purchase
                            myData.ownedStock.push_back(stockSelection[result]); //Add element to vector
                            myData.index ++; //Add to index

                            wipeFile(2); //Wipe file
                            writeFile(&stockSelection, &selectionSize, 2, &myData.balance, &myData.timeKeeper); //Update my stock file
                        }
                    }
                }
            }
            else if(inputValue == 2) //If user chooses to search by first letter
            {
                cout << endl << " >- Please enter key first letter" << endl;
                cin >> keyLetter;

                searchLetter(&stockSelection, selectionSize, &foundResults, &resultSize, keyLetter); //Call function to search for results
                if(resultSize != 0)
                {
                    cout << endl << " >- Please select a stock to purchase it " << endl << endl;
                    for(int i = 0; i < resultSize; i++) //Show all information
                    {
                        cout << " >- " << i+1 << ". Name|| " << stockSelection[foundResults[i]].name << endl;
                        cout << " >- Cost|| " << stockSelection[foundResults[i]].cost << endl;
                        cout << " >- Return/m|| " << stockSelection[foundResults[i]].dividend << endl;
                        cout << " >- Status|| " << stockSelection[foundResults[i]].status << endl;
                        cout << " >- Months Owned|| " << stockSelection[foundResults[i]].timeOwned << endl;
                        cout << " >- Extra Info|| " << stockSelection[foundResults[i]].extraInfo << endl << endl;
                    }
                    cout << " >- Press " << resultSize + 1 << " to exit" << endl;
                    getAnswer(resultSize + 1, 1, &inputValue); //Get options

                    if(inputValue < resultSize + 1)
                    {
                        savedNumber = inputValue - 1; //Save selected stock
                        if(stockSelection[result].status == "unsold" && myData.balance > stockSelection[result].cost) //If stock is unsold offer purchase offer
                        {
                            cout << endl << " >- Would you like to purchase? Press 1 for Yes, 2 for No" << endl;
                            getAnswer(2, 1, &inputValue);
                            if(inputValue == 1) //If they say yes, purchase stock
                            {
                                stockSelection[savedNumber].status = "sold";
                                myData.balance -= stockSelection[savedNumber].cost; //Subtract from budget to purchase
                                myData.ownedStock.push_back(stockSelection[savedNumber]); //Add element to vector
                                myData.index ++; //Add to index

                                wipeFile(2); //Wipe file
                                writeFile(&stockSelection, &selectionSize, 2, &myData.balance, &myData.timeKeeper); //Update my stock file
                            }
                        }
                        else
                        {
                            cout << " >- Unable to purchase..." << endl;
                        }
                    }
                }

                inputValue = 1;//Reset to some value between 1 & 5
            }
            else if(inputValue == 3) //If user chooses to search by cost range
            {
                cout << endl << " >- Please enter the max value" << endl;
                getAnswer(1000, 0, &rangeMax);
                cout << " >- Please enter the min value" << endl;
                getAnswer(1000, 0, &rangeMin);

                searchRange(&stockSelection, selectionSize, &foundResults, &resultSize, rangeMax, rangeMin); //Call function to search for results

                if(resultSize != 0)
                {
                    cout << endl << " >- Please select a stock to purchase it " << endl << endl;
                    for(int i = 0; i < resultSize; i++) //Show all information
                    {
                        cout << " >- " << i+1 << ". Name|| " << stockSelection[foundResults[i]].name << endl;
                        cout << " >- Cost|| " << stockSelection[foundResults[i]].cost << endl;
                        cout << " >- Return/m|| " << stockSelection[foundResults[i]].dividend << endl;
                        cout << " >- Status|| " << stockSelection[foundResults[i]].status << endl;
                        cout << " >- Months Owned|| " << stockSelection[foundResults[i]].timeOwned << endl;
                        cout << " >- Extra Info|| " << stockSelection[foundResults[i]].extraInfo << endl << endl;
                    }
                    cout << " >- Press " << resultSize + 1 << " to exit" << endl;
                    getAnswer(resultSize + 1, 1, &inputValue); //Get options

                    if(inputValue < resultSize + 1)
                    {
                        savedNumber = inputValue - 1; //Save selected stock
                        if(stockSelection[result].status == "unsold" && myData.balance > stockSelection[result].cost) //If stock is unsold offer purchase offer
                        {
                            cout << endl << " >- Would you like to purchase? Press 1 for Yes, 2 for No" << endl;
                            getAnswer(2, 1, &inputValue);
                            if(inputValue == 1) //If they say yes, purchase stock
                            {
                                stockSelection[savedNumber].status = "sold";
                                myData.balance -= stockSelection[savedNumber].cost; //Subtract from budget to purchase
                                myData.ownedStock.push_back(stockSelection[savedNumber]); //Add element to vector
                                myData.index ++; //Add to index

                                wipeFile(2); //Wipe file
                                writeFile(&stockSelection, &selectionSize, 2, &myData.balance, &myData.timeKeeper); //Update my stock file
                            }
                        }
                        else
                        {
                            cout << " >- Unable to purchase..." << endl;
                        }
                    }
                }

                inputValue = 1;//Reset to some value between 1 & 5
            }
        system("PAUSE");
        system("CLS");
        }
        else
        {
            auctionMode(&stockSelection, selectionSize, &myData.ownedStock, &myData.index, &myData.balance, &myData.timeKeeper);
        }

    wipeFile(1); //Wipe file
    writeFile(&myData.ownedStock, &myData.index, 1, &myData.balance, &myData.timeKeeper); //Update my stock file
    }
    return 0;
}

//This function is in charge of displaying all your stocks
void showStocks(int* _stockCount, vector<Stock> _stocks, int _type)
{
    for(int i = 0; i < *_stockCount; i++)
    {
        if((_stocks[i].status == "unsold" && _type == 1) || _type == 2)
        {
            cout << " >- " << i+1 << ". Name|| " << _stocks[i].name << endl;
            cout << " >- Cost|| " << _stocks[i].cost << endl;
            cout << " >- Return/m|| " << _stocks[i].dividend << endl;
            cout << " >- Status|| " << _stocks[i].status << endl;
            cout << " >- Months Owned|| " << _stocks[i].timeOwned << endl;
            cout << " >- Extra Info|| " << _stocks[i].extraInfo << endl << endl;
        }
    }
    return;
}

//This function is in charge of finding and returning your monthly income
float countIncome(int* _stockCount, vector<Stock> _stocks)
{
    float totalIncome = 0;
    for(int i = 0; i < *_stockCount; i++)
    {
        totalIncome += _stocks[i].dividend + (_stocks[i].dividend*0.01*_stocks[i].timeOwned);
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
    (*_data).timeKeeper ++;
    (*_data).balance += countIncome(&(*_data).index, (*_data).ownedStock);

    for(int i = 0; i < (*_data).index; i++) //For each stock owned, increase time owned by a month
    {
        (*_data).ownedStock[i].timeOwned ++; //increase age
        (*_data).ownedStock[i].triedSelling = false; //set to false
    }
    return;
}

//Used to add a new stock
void addStock(vector<Stock>* _stocks, int* _size, float* _balance, int* _date)
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
    cout << " >- Months Owned" << endl;
    cin >> tempStock.timeOwned;
    cout << " >- What extra information would you like?" << endl;
    cin >> tempStock.extraInfo;

    (*_stocks).push_back(tempStock); //Push stock to list
    *_size += 1; //Update index

    wipeFile(2); //Wipe file
    writeFile(_stocks, _size, 2, _balance, _date); //Update the stock file
    return;
}

//This function is used to find each line in the stock file and save it into the vector
void resetVector(vector<Stock>* _stocks, int* _size, int _file, float* _balance, int* _date)
{
    string line; //String line used to seperate the text file into lines
    ifstream stockFile_("Stocks.txt"); //This is the map file
    ifstream myStocksFile_("myStocks.txt"); //This is the map file
    Stock tempStock; //This is a temporary stock

    int lineRow = -2; //This integer keeps count of the row number for the saving in array

    if(stockFile_.is_open() && _file == 1) //If instricted to save the file
    {
        lineRow = 0;
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
                tempStock.timeOwned = atoi(line.c_str());
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
            if(lineRow < 0)
            {
                if(lineRow == -2) //Run at very start
                {
                    *_balance = atoi(line.c_str());
                }
                if(lineRow == -1) //Run at very start
                {
                    *_date = atoi(line.c_str());
                }
            }
            else if(lineRow % 6 == 0)
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
                tempStock.timeOwned = atoi(line.c_str());
            }
            else if(lineRow % 6 == 5)
            {
                tempStock.triedSelling = false; //by default set to false
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
void writeFile(vector<Stock>* _stocks, int* _size, int _file, float* _balance, int* _date)
{
    ofstream myfile;
    ofstream stockFile;
    if(_file == 1)
    {
        myfile.open("myStocks.txt"); //Open files
        myfile << *_balance << endl; //Add balance on first line
        myfile << *_date << endl; //Add date to second line
    }
    else if(_file == 2)
    {
        stockFile.open("Stocks.txt");
    }

    for(int i = 0; i < *_size ; i++) //Write to files
    {
        if(_file == 1)
        {
            myfile << (*_stocks)[i].name << endl;
            myfile << (*_stocks)[i].cost << endl;
            myfile << (*_stocks)[i].dividend << endl;
            myfile << (*_stocks)[i].status << endl;
            myfile << (*_stocks)[i].timeOwned<< endl;
            myfile << (*_stocks)[i].extraInfo << endl;
        }
        else if(_file == 2)
        {
            stockFile << (*_stocks)[i].name << endl;
            stockFile << (*_stocks)[i].cost << endl;
            stockFile << (*_stocks)[i].dividend << endl;
            stockFile << (*_stocks)[i].status << endl;
            stockFile << (*_stocks)[i].timeOwned << endl;
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

//For finding a stock by name
void searchName(vector<Stock>* _stocks, int _stocksSize, int* _result, string _condition)
{
    cout << " >- Searching..." << endl; //Print to console for indication
    *_result = 1000; //Set to null value
    for(int i = 0; i < _stocksSize; i++) //Search for matching name
    {
        if((*_stocks)[i].name == _condition) //If mathc is found, save in result
        {
            *_result = i;
            i = 1000; //Skip for loop
        }
    }

    if(*_result == 1000) //If no result is found, print to console
    {
        cout << " >- No result found" << endl;
    }
    return;
}

//For finding stocks by first letter
void searchLetter(vector<Stock>* _stocks, int _stocksSize, vector<int>* _results, int* _resultSize, char _condition)
{
    int counter = 0;
    *_resultSize = 0;
    cout << " >- Searching..." << endl; //Print to console for indication
    for(int i = 0; i < _stocksSize; i++) //Search for matching name
    {
        if((*_stocks)[i].name.at(0) == _condition) //If mathc is found, save in result
        {
            counter ++;
            (*_results).push_back(i);
        }
    }

    *_resultSize = counter; //Transfer size, go around bug

    if(*_resultSize == 0) //If no result is found, print to console
    {
        cout << " >- No result found" << endl;
    }

    return;
}

//For finding stocks with range
void searchRange(vector<Stock>* _stocks, int _stocksSize, vector<int>* _results, int* _resultSize, int _max, int _min)
{
    int counter = 0;
    *_resultSize = 0;
    cout << " >- Searching..." << endl; //Print to console for indication
    for(int i = 0; i < _stocksSize; i++) //Search for matching name
    {
        if(_min < (*_stocks)[i].cost < _max) //If match is found, save in result
        {
            counter ++;
            (*_results).push_back(i);
        }
    }

    *_resultSize = counter; //Transfer size, go around bug

    if(*_resultSize == 0) //If no result is found, print to console
    {
        cout << " >- No result found" << endl;
    }
    return;
}

//For the auction system
void auctionMode(vector<Stock>* _stocks, int _index, vector<Stock>* _myStocks, int* _myIndex, float* _balance, int* _date)
{
    time_t timer = clock(); //Retains a time
    int interTime = 0; //To prevent repeating a print of time while between miliseconds
    int target = 0; //This is a randomly generated number for the target stock
    int counter = 0; //for safety in case a stock cannot be found
    float value = 100; //This is for tracking the value of the stock
    int odds = 100; //This is the percent chance for the ai to bid higher
    int oddsIntervals = 0; //Set to null initiially, determines approx what % of lossed interest will happen with ai each time
    bool playerHasIt = false; //Indicates who currently has the highest bid
    int intervenePeriod = 2 + rand() % ((AUCTIONLIMIT/1000)-3);
    Stock tempStock;

    //Randomly choose stock to auction -> Make sure the stock has not been sold yet
    do
    {
        target = rand() % _index;
        counter ++;
    }
    while((*_stocks)[target].status == "sold" && counter < _index*5); //After a threshold of checks or found a good stock, quit

    if(counter >= _index*5) //If over threshhold, output and return
    {
        cout << " >- Unable to find stock to auction" << endl;
        return;
    }
    else //otherwise output info on stock
    {
        cout << " >- Stock found" << endl;
        cout << " >- Name|| " << (*_stocks)[target].name << endl;
        cout << " >- Return/m|| " << (*_stocks)[target].dividend << endl << endl;
        cout << " [Your Balance: $" << *_balance << "]" << endl << endl;
    }

    //Generate the baseline decay of interest that the ai has for the stock based on price, random chance, and the baseline % const given
    oddsIntervals = round((100 - BASEODDS)/((*_stocks)[target].cost/100));

    //Actual auction system
    cout << " >- Ready? Press any key to continue" << endl;
    getch();

    cout << "<<start>>" << endl;
    cout << " >- Value ||> " << value << endl;
    timer = clock();

    while(clock() - timer < AUCTIONLIMIT) //Run through the timer phase untill timer runs out
    {
        if((clock() - timer) % 1000 == 0 && interTime != clock()) //if time has not been shown yet and rests on a second interval, print out
        {
            interTime = clock(); //This is to make sure that between miliseconds counted the number is not repeated
            cout << "[" << round((AUCTIONLIMIT - (clock() - timer))/1000) << "]" << endl;

            //When the pre-determined time is right, AI will make it's decision
            if(intervenePeriod == round((AUCTIONLIMIT - (clock() - timer))/1000))
            {
                if(rand() % 100 < odds && playerHasIt) //AI generates randomly if they want to bid higher. If yes, enter if
                {
                    cout << "<<Other Raises>> + $100" << endl;
                    value += 100; //Increase value
                    cout << " >- Value ||> " << value << endl;
                    cout << "[" << AUCTIONLIMIT/1000 << "]" << endl;//Print initial time
                    timer = clock(); //Reset timer
                    playerHasIt = false;

                    //Affect the odds of the AI giving a response
                    if(rand()%2 == 0)
                    {
                        odds -= oddsIntervals + round(rand() % (oddsIntervals/3));
                    }
                    else
                    {
                        odds -= oddsIntervals - round(rand() % (oddsIntervals/3));
                    }

                    //Generate new intervention time
                    intervenePeriod = 2 + rand() % ((AUCTIONLIMIT/1000)-3);
                }
            }
        }

        if(GetKeyState(VK_UP) & 0x8000) //Check for input , if yes reset timer
        {
            ///////////////////TODO: Make Intervals Varry//////////////////////////////////

            if(*_balance > value + 100)
            {
                cout << "<<Player Raises>> + $100" << endl;
                value += 100; //Increase value
                cout << " >- Value ||> " << value << endl;
                cout << "[" << AUCTIONLIMIT/1000 << "]" << endl;//Print initial time
                timer = clock(); //Reset timer
                playerHasIt = true;

                //Affect the odds of the AI giving a response
                if(rand()%2 == 0)
                {
                    odds -= oddsIntervals + round(rand() % (oddsIntervals/3));
                }
                else
                {
                    odds -= oddsIntervals - round(rand() % (oddsIntervals/3));
                }

                Sleep(200);
                intervenePeriod = 2 + rand() % ((AUCTIONLIMIT/1000)-3); //regenerate intervention period
            }
            else
            {
                cout << " >- Not enough money" << endl;
                Sleep(200);
            }
        }
    }
    cout << "<<sold";

    //If player one, allocate stock to player. Remove from stock market
    if(playerHasIt)
    {
        cout << " to Player>>" << endl;

        (*_stocks)[target].status = "sold";
        *_balance -= value; //Subtract from budget to purchase
        tempStock = (*_stocks)[target];
        (*_myStocks).push_back(tempStock); //Add element to vector
        *_myIndex += 1; //Add to index

        wipeFile(2); //Wipe file
        writeFile(_stocks, &_index, 2, _balance, _date); //Update my stock file
    }
    else
    {
        cout << " to Other>>" << endl;
    }

    system("PAUSE");//Pause temp
    system("CLS"); //Wipe screen

    return; //Return to main()
}
