/*
>- Author: Max Wong
>- Date: Sep 12, 2019
>- Updated: Sep 16, 2019
>- Purpose: write a Storefront simulator
*/

#include <iostream>
#include <conio.h>

//For error trapping
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <string>

#include <dos.h> //for delay
#include <windows.h>

//For reading txt file
#include <fstream>

using namespace std;

struct shoppingList
{
    string name;
    string contact;
    string creditCardNumber;
    int purchaseCounter = 0;
    int itemsPurchased[20];
};

void printStock();
void thankForPurchase();
bool stringChecker(string); //This function checks if an input in a string can be coverted into an integer

int main()
{
    shoppingList userInformation;

    string inputValue;
    int purchasedItemInt;
    bool isPurchasing = true;
    bool isPaying = false;

    //For fake login
    string randInput = "";
    string userID = "";
    char ch;

    for(int i = 0; i < 20; i++) userInformation.itemsPurchased[i] = 0;

    cout << ">- Welcome to the S.A.W (Super Animal World) Store." << endl;

    while(isPurchasing)
    {
        printStock();

        //To do: color number
        cout << endl << ">- You have [" << userInformation.purchaseCounter << "] items in your cart." << endl << "Type /p to purchase " << endl << endl;
        cout << ">- Please enter your number: ";
        cin >> inputValue;

        if(inputValue == "/p")
        {
            //purchasing = false;
            isPaying = true;
        }
        else if(stringChecker(inputValue))
        {
            purchasedItemInt = ::atof(inputValue.c_str());

            cout << ">- [processing...]" << endl;
            Sleep( 200 );
            if(purchasedItemInt  <= 10)
            {
                userInformation.itemsPurchased[purchasedItemInt - 1] += 1;
                userInformation.purchaseCounter += 1;
                system("CLS");
            }
            else cout << ">- ERROR, please enter a proper command" << endl;
        }
        else cout << ">- ERROR, please enter a proper command" << endl;

        while(isPaying)
        {
            system("CLS");
            cout << ">- Here is your reciept" << endl;
            cout << endl << "=======================" << endl;
            for(int i = 0; i < 10; i++)
            {
                if( userInformation.itemsPurchased[i] > 0)
                {
                    switch(i)
                    {
                        case 0: cout << "Tiger Hat x" << userInformation.itemsPurchased[i] << endl;
                            break;
                        case 1: cout << "Fox Hat x" << userInformation.itemsPurchased[i] << endl;
                            break;
                        case 2: cout << "Deer Hat x" << userInformation.itemsPurchased[i] << endl;
                            break;
                        case 3: cout << "Skunk Hat x" << userInformation.itemsPurchased[i] << endl;
                            break;
                        case 4: cout << "Blue Bird Plushie x" << userInformation.itemsPurchased[i] << endl;
                            break;
                        case 5: cout << "Skull Muskrat Plushie x" << userInformation.itemsPurchased[i] << endl;
                            break;
                        case 6: cout << "House Cat Plushie x" << userInformation.itemsPurchased[i] << endl;
                            break;
                        case 7: cout << "Husky Plushie x" << userInformation.itemsPurchased[i] << endl;
                            break;
                        case 8: cout << "Red Panda Dorayaki (Red Bean Pancake Buns) x" << userInformation.itemsPurchased[i] << endl;
                            break;
                        case 9: cout << "Pink Fox Lemonade x" << userInformation.itemsPurchased[i] << endl;
                            break;
                    }
                }
            }

            cout << endl << ">- Welcome to the S.A.R payment system. Please enter your information below to confirm your purchase." << endl;

            cout << "Please enter your name:";
            cin >> userInformation.name;
            cout << endl;

            cout << "Please enter your email:";
            cin >> userInformation.contact;
            cout << endl;

            cout << "Now please enter your credit card number" << endl;

            //Fake username and password system. Converts all letters into *'s
            ch = _getch();
            while(ch != 13)
            {
                randInput.push_back(ch);
                cout << '*';
                ch = _getch();
            }
            cout << endl;
            userInformation.creditCardNumber = randInput;

            cout << endl << ">- [Checkout]" << endl;
            cout << "Name: " << userInformation.name << endl << "Contact: " << userInformation.contact << endl;
            cout << "Please type /y to confirm. /b to return to the purcahse menu" << endl;
            cin >> inputValue;

            if(inputValue == "/y")
            {
                isPurchasing = false;
                isPaying = false;
            }
            else if(inputValue == "/b")
            {
                isPaying = false;
            }
            else
            {
                cout << endl << ">- Please enter a valid response" << endl;
            }
        }
    }
    thankForPurchase();
    return 0;
}

void printStock()
{
    cout << ">- Please select a number to buy a product. Type /p to pay" << endl;

    cout << endl << "[Please press any key to continue]" << endl;
    getch();

    cout << endl << ">- [<> - Today in stock - <>]" << endl << "==----------------------------==" << endl << endl;


    cout << endl << ">- Hats" << endl << "==========" << endl << "   + Tiger Hat [1]" << endl << "   + Fox Hat [2]" << endl << "   + Deer Hat [3]" << endl << "   + Skunk Hat [4]" << endl;
    cout << endl << ">- Plushies" << endl << "==========" << endl << "   + Blue Bird Plushie [5]" << endl << "   + Skull Muskrat Plushie [6]" << endl << "   + House Cat Plushie [7]" << endl << "   + Husky Plushie [8]" << endl;
    cout << endl << ">- Food" << endl << "==========" << endl << "   + Red Panda Dorayaki (Red Bean Pancake Buns) [9]" << endl << "   + Pink Fox Lemonade [10]" << endl << endl;
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

void thankForPurchase()
{
    std::string line;
    ifstream file_("SARfile.txt");

    if(file_.is_open())
    {
        //This function uses the builtin function: getline
        while(getline(file_,line))
        {
            cout << line << endl;
        }
        file_.close();
    }
    return;
}
