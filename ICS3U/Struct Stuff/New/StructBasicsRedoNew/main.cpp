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
    Give 5 cards to each person

when it is player's turn
    Guess a card
        If other person has card, take that card
        check if person has 4 of that card
            If yes, eliminate cards and give player points
        If not, go fish
        Get card from deck
    ///////////////////////////done////////////////////////////

    Check Win
    Sorting
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

struct Pile{
    Card cards[52];
    int cardCounter;
    int playerPoints;
};

void display(Card[]); //This function is used to display a single card struct
void initialize(Card&, char, string, int); //This function is used to set the value of a struct
bool compare(Card, int); //This function is used to compare two a card and an integer, and will return true if match is found
void swapValues(Card&, Card&); //This function will swap the two values of the cards given
void startingInitialize(Card[], char[], string[], bool); //This is run at the start to set the deck to the standard config
void shuffle(Card[]); //This function is for shuffling the cards
void displayAllCards(Card[], int); //This function is for outputing an array of cards
void checkForCards(Card[], Card[], Card[], int&, int&, int&, int, int&, int&); //This function carries out the check for similar cards and will take that card if a match is found
int getSmallest(Card[], int); //This function is used to get the smallest value
//void sortCards(Card[], int); //This function is used to sort the array


void displayMenu(int); //Function to show the menu: All positions are options except last which is reserved for quit number
int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)

const int DECKSIZE = 52; //This constant defines how big the base deck is

int main()
{
    //Set everything to random based on time
    srand(time(NULL));

    int playersTurn = 0; //This integer keeps track of who's turn it currently is
    int getInput; //This integer is to get an input from the player

    //Initialize the possible suits and ranks
    char suits[4] = {'S', 'H', 'C', 'D'};
    string ranks[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    //Now initialize whole deck -> shuffle it all
    Pile deck;
    deck.cardCounter = 52; //Set counter to 52 cards
    startingInitialize(deck.cards, suits, ranks, false); //Set deck to default settup
    shuffle(deck.cards);

    //Now initialize hands -> set all positions to null
    Pile handOne;
    Pile handTwo;
    handOne.cardCounter = 5; //Reset counters
    handTwo.cardCounter = 5; //Reset counters
    startingInitialize(handOne.cards, suits, ranks, true); //Set deck to NULL settup
    startingInitialize(handTwo.cards, suits, ranks, true);

    //Give 5 cards to each player -> swap first five empty spots in hands with first 10 spots in deck
    for(int i = 0; i < 5; i++)
    {
        swapValues(handOne.cards[i], deck.cards[52-deck.cardCounter]); //swap cards with hand and deck
        deck.cardCounter --; //Update counters
        swapValues(handTwo.cards[i], deck.cards[52-deck.cardCounter]); //swap cards with hand and deck
        deck.cardCounter --; //Update counters
    }


    do{
        cout << ">- Player [" << playersTurn % 2 + 1 << "]'s turn" << endl;
        cout << ">- Your cards" << endl;
        if(playersTurn % 2 == 0)
        {
            displayAllCards(handOne.cards, handOne.cardCounter);//Display player's cards
            displayMenu(handOne.cardCounter); //Display your menu
            getInput = getAnswer(handOne.cardCounter + 1, 1); //Get player's input
        }
        else
        {
            displayAllCards(handTwo.cards, handTwo.cardCounter);//Display player's card
            displayMenu(handTwo.cardCounter); //Display your menu
            getInput = getAnswer(handTwo.cardCounter + 1, 1); //Get player's input
        }
        playersTurn ++; //Set to next player's turn
        system("CLS"); //Reset console screen
    }while((playersTurn % 2 == 0 && getInput != handOne.cardCounter + 1) || (playersTurn % 2 == 1 && getInput != handTwo.cardCounter + 1));


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
bool compare(int _cardValue, int _value)
{
    if(_cardValue == _value)
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
void startingInitialize(Card _card[], char _suits[], string _ranks[], bool setNull)
{
    int tempInteger; //This integer temporarily stores the suits value in number form
    for(int i = 0; i < 52; i++)
    {
        if(!setNull)
        { //If the function is instructed not to set all to null, set cards suit, rank and value
            tempInteger = floor(i/13);
            initialize(_card[i], _suits[tempInteger], _ranks[i%13], ((i%13)+2));
        }
        else
        { //otherwise, set all to null positions
            initialize(_card[i], 'n', "NULL", 100 );
        }
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

//This function carries out the check for similar cards and will take that card if a match is found
void checkForCards(Card _handOne[], Card _handTwo[], Card _deck[], int& _counterOne, int& _counterTwo, int& _deckCounter, int _guessedValue)
{
    bool foundMatch = false;
    for(int i = 0; i < _counterTwo; i++)
    { //Go through whole other player's hand and check to see if they have your guessed card
        if(compare(_guessedValue, _handTwo[i].cardValue))
        { //If yes, swap your empty slot with their card, then resort their hand
            swapValues(_handOne[_counterOne], _handTwo[i]);
            _counterOne ++;
            swapValues(_handTwo[_counterTwo-1], _handTwo[i]);
            _counterTwo --;
            foundMatch = true;
        }
    }
    if(foundMatch == false)
    {
        //Go fish, get card from deck and swap with end position of player's hand
        swapValues(_handOne[_counterOne], _deck[52-_deckCounter]);
        _deckCounter --;
        _counterOne ++;
    }
    return;
}

//This function is used to get the smallest value
int getSmallest(Card _cards[], int arraySize)
{
    int smallestValue = 1000;
    for(int i = 0; i < arraySize; i++)
    {
        if(_cards[i].value < smallestValue)
        {
            smallestValue = _cards[i].value;
        }
    }
}

//Displays the menu
void displayMenu(int arraySize)
{
    cout << endl << ">- Please choose one of the options below." << endl;
    //Display instructions (using assistance of string array)
    for(int i = 0; i < arraySize; i++)
    {
        cout << ">- Press [" << i+1 << "] to play card " << i << " in hand" << endl;
    }
    cout << ">- Press [" << arraySize + 1 << "] to quit " << endl;
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






