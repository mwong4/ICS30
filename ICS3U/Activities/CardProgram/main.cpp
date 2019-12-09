/*
>- Author: Max Wong
>- Date: Dec 5, 2019
>- Updated: Dec 8, 2019
>- Purpose: To write a card program using structs
>-
>- Thanks to Thomas Maloley for teaching me how to program with C++

TO DO
 -Commenting + Cleaning
 -Better display
 -Set individual value
*/

#include <iostream>
#include<limits> //For error trapping

using namespace std;

struct Card{
    char cardSuit;
    string cardRank;
    int cardValue;
    int identity;
} myCards[52];

void displayCard(Card);
Card setCard(Card, int);
int findIdentity(Card);

void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number
int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)


int main()
{
    int rangeStart = 0;
    int rangeEnd = 52;
    int getInput = 0;

    int cardToChange;
    int valueToChange;

    int identityOne;
    int identityTwo;
    int secondCardToSwap;

    int viewWhichCard = 0;
    string menuOptions[6] = {"Display card", "Display all cards", "Reset all card values", "Change one card", "Shuffle deck", "To quit"};

    for(int i = rangeStart; rangeEnd > i; i++)
    {
        myCards[i] = setCard(myCards[i], i);
    }

    while(getInput != 6)
    {
        displayMenu(menuOptions, 6);
        getInput = getAnswer(6, 0);

        if(getInput == 1)
        {
            cout << ">- Please the card you would like to display (from 0 to 51)" << endl;
            viewWhichCard = getAnswer(51,0);
            displayCard(myCards[viewWhichCard]);
        }
        else if(getInput == 2)
        {
            for(int i = rangeStart; rangeEnd > i; i++)
            {
                displayCard(myCards[i]);
            }
        }
        else if(getInput == 3)
        {
            for(int i = rangeStart; rangeEnd > i; i++)
            {
                myCards[i] = setCard(myCards[i], i);
            }
        }
        else if(getInput == 4)
        {
            cout << "Please pick card to manipulate (0-51)" << endl;
            cardToChange = getAnswer(51,0);
            cout << "Now please enter identity (0-51)" << endl;
            valueToChange = getAnswer(51,0);
            //Need to work on this system
            myCards[cardToChange] = setCard(myCards[cardToChange], valueToChange);
        }
        else if(getInput == 5)
        {
            for(int i = rangeStart; rangeEnd > i; i++)
            {
                secondCardToSwap = rand()% 51;

                identityOne = findIdentity(myCards[i]);
                identityTwo = findIdentity(myCards[secondCardToSwap]);
                myCards[i] = setCard(myCards[i], identityTwo);
                myCards[secondCardToSwap] = setCard(myCards[secondCardToSwap], identityOne);
            }
        }
        system("PAUSE");
        system("CLS");
    }
    return 0;
}

void displayCard(Card myCard)
{
    cout << endl << ">- Suit " << myCard.cardSuit << endl;
    cout << ">- Card Rank " << myCard.cardRank << endl;
    cout << ">- Value " << myCard.cardValue << endl;
    return;
}

Card setCard(Card myCard, int counter)
{
    myCard.cardValue = (counter % 13) + 1;
    myCard.identity = counter;
    if(counter % 13 == 0)
    {
        myCard.cardRank = "Ace";
    }
    else if(counter % 13 == 1)
    {
        myCard.cardRank = "Two";
    }
    else if(counter % 13 == 2)
    {
        myCard.cardRank = "Three";
    }
    else if(counter % 13 == 3)
    {
        myCard.cardRank = "Four";
    }
    else if(counter % 13 == 4)
    {
        myCard.cardRank = "Five";
    }
    else if(counter % 13 == 5)
    {
        myCard.cardRank = "Six";
    }
    else if(counter % 13 == 6)
    {
        myCard.cardRank = "Seven";
    }
    else if(counter % 13 == 7)
    {
        myCard.cardRank = "Eight";
    }
    else if(counter % 13 == 8)
    {
        myCard.cardRank = "Nine";
    }
    else if(counter % 13 == 9)
    {
        myCard.cardRank = "Ten";
    }
    else if(counter % 13 == 10)
    {
        myCard.cardRank = "Jack";
    }
    else if(counter % 13 == 11)
    {
        myCard.cardRank = "Queen";
    }
    else if(counter % 13 == 12)
    {
        myCard.cardRank = "King";
    }
    if(counter >= 0 && counter < 13)
    {
        myCard.cardSuit = 'S';
    }
    else if(counter >= 13 && counter < 26)
    {
        myCard.cardSuit = 'H';
    }
    else if(counter >= 26 && counter < 39)
    {
        myCard.cardSuit = 'C';
    }
    else if(counter >= 39 && counter < 52)
    {
        myCard.cardSuit = 'D';
    }
    return myCard;
}

//This function is used to find the value of the card identity
int findIdentity(Card myCard)
{
    return myCard.identity;
}

//Displays the menu
void displayMenu(string options[], int arraySize)
{
    cout << endl << ">- Please enter a direct command. Below are the primary listed commands." << endl;
    //Display instructions (using assistance of string array)
    for(int i = 0; i < arraySize; i++)
    {
        cout << ">- [" << i+1 << "] " << options[i] << endl;
    }
    return;
}

//Error trapping funcion that only accepts integers
int getAnswer (int limitMax, int limitMin)
{
    int playerInput; //This variable is used to get the player's input
    bool findingInput; //This bool determines if the loop continues running
    do
    {
        findingInput = false; //By default, the loop will end
        cout << ">- Your input: "; //Get player input
        cin >> playerInput;
        if(cin.fail())//Check to see if player entered a "bad" input type
        {
            cin.clear(); //Clear all flags
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore incorrect symbols
            cout << ">- ERROR: Please enter a valid input number" << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
        else if(playerInput > limitMax || playerInput < limitMin ) //Otherwise, print an error message
        {
            cout << ">- ERROR: Please enter a number between " << limitMin << " and " << limitMax << endl;
            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    return playerInput;//Otherwise input is good, return input
}
