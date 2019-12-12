/*
>- Author: Max Wong
>- Date: Dec 11, 2019
>- Updated: Dec 11, 2019
>- Purpose: To write the basic 4 functions for struct manipulation
>-
>- Thanks to Thomas Maloley for teaching me how to program with C++

TO DO:

Settup
    Shuffle the deck


    ///////////////////////////done////////////////////////////

        Give 5 cards to each person

when it is player's turn
    Guess a card
        If other person has card, take that card
        check if person has 4 of that card
            If yes, eliminate cards and give player points
        If not, go fish
        Get card from deck
*/

#include <iostream>
#include <limits> //For error trapping
#include <stdio.h> //For NULL(srand)
#include <stdlib.h> //For srand, rand
#include <time.h> //For time(srand)
#include <tgmath.h> //For floor function

using namespace std;

//This structure holds the values of the card
struct Card{
    char cardSuit; //Card suit saved as char
    string cardRank; //Card rank saved as string
    int cardValue; //Card value saved as integerds
};

void display(Card[]); //This function is used to display a single card struct
void initialize(Card&, char, string, int); //This function is used to set the value of a struct
bool compare(Card, int); //This function is used to compare two a card and an integer, and will return true if match is found
void swapValues(Card&, Card&); //This function will swap the two values of the cards given
void startingInitialize(Card[], char[], string[]); //This is run at the start to set the deck to the standard config
void shuffle(Card[]); //This function is for shuffling the cards
void displayAllCards(Card[], int); //This function is for outputing an array of cards


void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number
int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)

const int DECKSIZE = 52; //This constant defines how big the base deck is

int main()
{
    //Set everything to random based on time
    srand(time(NULL));

    //Initialize the possible suits and ranks
    char suits[4] = {'S', 'H', 'C', 'D'};
    string ranks[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    //Now initialize whole deck -> shuffle it all
    Card deck[52];
    startingInitialize(deck, suits, ranks);
    shuffle(deck);




    return 0;
}

//This function is used to display a single card struct
void display(Card _card)
{
        cout << _card.cardRank << " of " << _card.cardSuit;
        return;
}

//This function is used to set the value of a struct
void initialize(Card& _card, char _suit, string _rank, int _value)
{
    _card.cardSuit = _suit;
    _card.cardRank = _rank;
    _card.cardValue = _value;
    return;
}

//This function is used to compare two a card and an integer, and will return true if match is found
bool compare(Card _card, int _value)
{
    if(_card.cardValue == _value)
    {
        return true;
    }
    return false;
}

//This function will swap the two values of the cards given
void swapValues(Card& _cardOne, Card& _cardTwo)
{
    char tempSuit; //This variable temporarily saves a suit
    string tempRank; //This variable temporarily saves a rank
    int tempValue; //This variable temporarily saves a value

    tempSuit = _cardOne.cardSuit; //This modules swap the suits of the two cards
    _cardOne.cardSuit = _cardTwo.cardSuit;
    _cardTwo.cardSuit = tempSuit;

    tempRank = _cardOne.cardRank; //This modules swap the ranks of the two cards
    _cardOne.cardRank = _cardTwo.cardRank;
    _cardTwo.cardRank = tempRank;

    tempValue = _cardOne.cardValue; //This modules swap the values of the two cards
    _cardOne.cardValue = _cardTwo.cardValue;
    _cardTwo.cardValue = tempValue;
    return;
}

//This is run at the start to set the deck to the standard config
void startingInitialize(Card _card[], char _suits[], string _ranks[])
{
    int tempInteger; //This integer temporarily stores the suits value in number form
    for(int i = 0; i < 52; i++)
    {
        tempInteger = floor(i/13);
        initialize(_card[i], _suits[tempInteger], _ranks[i%13], ((i%13)+2));
    }
    return;
}

//This function is for shuffling the cards
void shuffle(Card _card[])
{
    for(int i = 0; i < DECKSIZE; i++)
    {//Goes through every card in the deck and swaps it with a random location in the array
        swapValues(_card[i], _card[rand()%52]);
    }
    return;
}

 //This function is for outputing an array of cards
void displayAllCards(Card _card[], int _arraySize)
{
    for(int i = 0; i < _arraySize; i++)
    {//Go through entire array and display each card
        display(_card[i]);
        cout << endl;
    }
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






