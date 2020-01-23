/*
>- Author: Max Wong
>- Date: Jan 22, 2020
>- Updated: Jan 22, 2020
>- Purpose:

    Write a program that performs a retail transaction and displays the receipt.
    - The program should display a short list of items to purchase.
    - The user should be able to buy up to 10 items. (The same item may be repeated)
    - The user should enter how much they wish to pay with.
    - The receipt should include the list of items purchased, the cost of each item
    purchased, the total cost (you may assume no tax), the amount of cash tendered
    and the change provided.

    Ex: Coffee 5.00
    Bagel 7.79

    Total: 12.79
    Amount Tendered: 50.00
    The change is: 1 Twenties, 1 Ten, 1 Five, 1 Toonie, 2 dimes and 1 penny.
*/


#include <iostream>
#include<limits>     //For error trapping
#include <windows.h> //For system commands
#include <math.h>       /* floor */

using namespace std;

//This struct contains the receipt data
struct Receipt
{
    int itemsChosen[5]; //This int array represents the items chosen by the user
    int itemsInCart; //This int represents the # of items chosen
    float totalCost; //This represents the total amount needed to pay for the cart
    float enteredAmount; //This is the amount the person is paying with
};

void resetStruct(Receipt&); //This function is used to reset the struct values
void paymentSystem(Receipt, string[], float[]); //This function is run at the end when the user chooses to pay
void changeCalculator(float); //This function is used to calculate the change composition

int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)
void displayMenu(string[], int, Receipt, bool, float[]); //Function to show the menu: All positions are options except last which is reserved for quit number


int main()
{
    //This struct saves all info for the receipt
    Receipt userData;
    resetStruct(userData); //Call function to reset the Receipt

    //This string represents what can be purchased
    string itemsForSale[6] = {"Stuffy Dog", "Stuffy Bear", "Stuffy Rabit", "Stuffy Fox", "Stuffy Hamster", "Pay for items/Quit"};
    //This int array represents the prices of each merchandise
    float itemPrices[5] = {1.9, 1.5, 1.6, 1.25, 2.00};
    int userInput; //This integer get's a user input

    while(userInput != 6)
    {
        cout << ">- Welcome to Super Animal World stuffy shop!" << endl;
        cout << ">- Please pick a number to choose a product." << endl;
        displayMenu(itemsForSale, 6, userData, true, itemPrices); //Call menu function to display options
        userInput = getAnswer(6,1);

        if(userInput == 6)
        { //If user chooses to pay/quit
            if(userData.itemsInCart == 0)
            { //If user has not added anything to the cart
                cout << ">- Thank you for shopping at Super Animal World stuffy shop!" << endl;
            }
            else
            { //Otherwise
                paymentSystem(userData, itemsForSale, itemPrices);
            }
        }
        else if(userData.itemsInCart < 10)
        { //Otherwise, add item to cart
            cout << ">- " << itemsForSale[userInput - 1] << " was added to your cart. " << endl; //Tell user what they chose to add to their cart
            userData.itemsInCart ++;
            userData.itemsChosen[userInput - 1] ++;
        }
        else
        {
            cout << ">- Sorry, you have reached the purchase cap. You can not pick any more items." << endl;
        }
        system("PAUSE"); //Wait for any input before continuing
        system("CLS"); //Wipe console
    }

    return 0;
}

//This function is used to reset the struct values
void resetStruct(Receipt& _userData)
{
    _userData.itemsInCart = 0; //Set # of items chosen to 0

    for(int i = 0; i < 5; i++)
    {//For every item in the array
        _userData.itemsChosen[i] = 0; //Set the item chosen to 0
    }

    _userData.totalCost = 0;
    _userData.enteredAmount = 0;

    return;
}

//This function is run at the end when the user chooses to pay
void paymentSystem(Receipt _userData, string _itemsForSale[], float _itemPrices[])
{
    system("CLS");//Wipe console

    //Calculate total cost
    for(int i = 0; i < 5; i++)
    { //Go through every item in the cart
        _userData.totalCost += _itemPrices[i]*_userData.itemsChosen[i]; //Calculate the cost of each item
    }

    while(_userData.enteredAmount < _userData.totalCost)
    {
        cout << "Your total bill for all items in your cart is: $" << _userData.totalCost << endl;
        cout << "What would you like to pay?" << endl;
        cin >> _userData.enteredAmount;
        if(_userData.enteredAmount < _userData.totalCost)
        {
            cout << "Sorry, you did not pay enough" << endl;
            system("PAUSE");
        }
        system("CLS"); //Wipe console
    }

    cout << endl << "Here is your virtual receipt. Thank you for shopping at SAR stuffy shop!" << endl << endl;
    displayMenu(_itemsForSale, 5, _userData, false, _itemPrices); //Call menu function to display all in cart
    cout << "Total: " << _userData.totalCost << endl; //Display cost
    cout << "Amount Tendered: " << _userData.enteredAmount << endl; //Display payment
    changeCalculator(_userData.enteredAmount - _userData.totalCost); //Call function to calculate and display change composition
    return;
}

//This function is used to calculate the change composition
void changeCalculator(float _inputValue)
{
    cout << "The change is: ";

    if(_inputValue > 20)
    {
        cout << floor(_inputValue/20) << " Twenties, "; //Display how many twenties there are
        _inputValue -= 20*floor(_inputValue/20); //Subtract from change
    }
    if(_inputValue > 10)
    {
        cout << floor(_inputValue/10) << " Tens, "; //Display how many twenties there are
        _inputValue -= 10*floor(_inputValue/10); //Subtract from change
    }
    if(_inputValue > 5)
    {
        cout << floor(_inputValue/5) << " Fives, "; //Display how many twenties there are
        _inputValue -= 5*floor(_inputValue/5); //Subtract from change
    }
    if(_inputValue > 2)
    {
        cout << floor(_inputValue/2) << " Toonies, "; //Display how many twenties there are
        _inputValue -= 2*floor(_inputValue/2); //Subtract from change
    }

    _inputValue *= 100; //Multiply by 100 to sort through cents

    if(_inputValue > 100)
    {
        cout << floor(_inputValue/100) << " Dollars, "; //Display how many twenties there are
        _inputValue -= 100*floor(_inputValue/100); //Subtract from change
    }
    if(_inputValue > 25)
    {
        cout << floor(_inputValue/25) << " Quarters, "; //Display how many twenties there are
        _inputValue -= 25*floor(_inputValue/25); //Subtract from change
    }
    if(_inputValue > 10)
    {
        cout << floor(_inputValue/10) << " Dimes, "; //Display how many twenties there are
        _inputValue -= 10*floor(_inputValue/10); //Subtract from change
    }
    if(_inputValue > 5)
    {
        cout << floor(_inputValue/5) << " Nickles, "; //Display how many twenties there are
        _inputValue -= 5*floor(_inputValue/5); //Subtract from change
    }
    if(_inputValue >= 1)
    {
        cout << floor(_inputValue) + 1 << " Pennies";
    }
    cout << endl << endl;
    return;
}

//Function used to get the players response as an integer (with error trapping)
int getAnswer (int _maxLimit, int _minLimit)
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
            cout << "  >- Please enter a valid input number" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if(playerInput > _maxLimit || playerInput < _minLimit ) //Otherwise, print an error message
        {
            cout << "  >- Please enter a number between " << _minLimit << " and " << _maxLimit << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }
    while(findingInput);
    return playerInput;//Otherwise input is good, return input
}

//Displays the menu
void displayMenu(string _options[], int _arraySize, Receipt _userData, bool _showNumber, float _itemPrices[])
{
    //Display instructions
    for(int i = 0; i < _arraySize; i++) //For every option, display with number indicator
    {
        if(_showNumber)
        { //If instructed to show the front number
            cout << "    >- [" << i+1 << "] ";
        }

        if(i != 5)
        { //If option is not the quit option
             cout << _options[i] << " x" << _userData.itemsChosen[i];
        }
        else
        { //Else, display option without x...
            cout  << _options[i];
        }

        if(!_showNumber)
        { //If not instructed to show number, must be in paymnet system. Show prices
            cout << "               [cost: $" << _itemPrices[i] << " each,  $" << _itemPrices[i]*_userData.itemsChosen[i] << " total] ";
        }

        cout << endl; //End line
    }
    return;
}
