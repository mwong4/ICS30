/*
>- Author: Max Wong
>- Date: Dec 10, 2019
>- Updated: Dec 11, 2019
>- Purpose: To write gold fish using structs [version 3.0.4]
>-
>- Thanks to Thomas Maloley for teaching me how to program with C++

TO DO
 -Cleaning
    -find way to place all struct things in functions
     _ thing
     -Move everything into functions
     -EFFICIENCY!!!!

 -Better display
    -Show acual ASCII card art

 -Fix all bugs
    -Future max problem
*/

//Libraries used
#include <iostream>
#include <limits> //For error trapping
#include <tgmath.h> //For floor function
#include <stdio.h> //For NULL(srand)
#include <stdlib.h> //For srand, rand
#include <time.h> //For time(srand)

//Pre-processor commands used
using namespace std;

//This structure holds the values of the card
struct Card{
    char cardSuit; //Card suit saved as char
    string cardRank; //Card rank saved as string
    int cardValue; //Card value saved as integerds
    int identity; //Card indetity saved as integer
}; //Have an array of structures/cards

//Defining functions used
void displayCard(Card); //This function is used to display a specific card
Card setCard(Card, int, char[], string[], bool); //This function is used to set a specific card
int findIdentity(Card); //THis function is used to find the specific identity of a card

bool findSimilar(Card, int); //This function will try to see if other player has a similar card (Same Rank)
void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number
int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)

//Defining Global Variables Used
const int DECKSIZE = 52;

int main()
{
    Card pile[52];
    Card handOne[52];
    Card handTwo[52];

    srand(time(NULL));

    int playersTurn = 0;
    int getInput = 0; //This integer is used to get player input as to what they would like to do

    int identityOne; //this variable holds the value of the first selected card's identity
    int identityTwo; //this variable holds the value fo the seond selected card's identity
    int secondCardToSwap; //this integer saves the value of the second card to be swapped

    int deckCount = 52;
    int handOneCount = 5;
    int handTwoCount = 5;

    bool noMatch; //This boolean is for keeping track of if program should "go fish"

    //This string array saves all the menu options
    string menuOptions[14] = {"Guess One", "Guess Two", "Guess Three", "Guess Four", "Guess Five", "Guess Six", "Guess Seven", "Guess Eight", "Guess Nine", "Guess Ten", "Guess Jack", "Guess Queen", "Guess King", "To quit"};

    //this char array represents the possible suits
    char suitOptions[4] = {'S', 'H', 'C', 'D'};
    //this string array represents the different rank's possible
    string rankOptions[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    //Just run through the whole cards array and reset deck
    for(int i = 0; DECKSIZE > i; i++) //Run through every position of the deck
    {
        pile[i] = setCard(pile[i], i, suitOptions, rankOptions, false); //And reset it to default deck
        handOne[i] = setCard(handOne[i], 100, suitOptions, rankOptions, true); //And reset it to default deck
        handTwo[i] = setCard(handTwo[i], 100, suitOptions, rankOptions, true); //And reset it to default deck
    }

    //Next run through deck and shuffle
    for(int i = 0; DECKSIZE > i; i++)
    {//Find a random card to swap with to shuffle
        secondCardToSwap = rand()% 51;

        identityOne = findIdentity(pile[i]); //Find identity of first card
        identityTwo = findIdentity(pile[secondCardToSwap]); //Find identity of second card
        pile[i] = setCard(pile[i], identityTwo, suitOptions, rankOptions, false); //Rebuild first card with second's identity
        pile[secondCardToSwap] = setCard(pile[secondCardToSwap], identityOne, suitOptions, rankOptions, false); //Rebuilds second card with first's identity
    }

    //Go through and assign the first 10 elements/cards in the deck to both players (5 to each)
    for(int i = 0; i < 5; i++)
    {
        identityOne = findIdentity(handOne[i]); //Find identity of first card
        identityTwo = findIdentity(pile[52-deckCount]); //Find identity of second card
        handOne[i] = setCard(handOne[i], identityTwo, suitOptions, rankOptions, false); //Rebuild first card with second's identity
        pile[52-deckCount] = setCard(pile[52-deckCount], identityOne, suitOptions, rankOptions, false); //Rebuilds second card with first's identity
        deckCount --;

        identityOne = findIdentity(handTwo[i]); //Find identity of first card
        identityTwo = findIdentity(pile[52-deckCount]); //Find identity of second card
        handTwo[i] = setCard(handTwo[i], identityTwo, suitOptions, rankOptions, false); //Rebuild first card with second's identity
        pile[52-deckCount] = setCard(pile[52-deckCount], identityOne, suitOptions, rankOptions, false); //Rebuilds second card with first's identity
        deckCount --;
    }

    //While the player does not choose to quit (6)
    while(getInput != 14)
    {
        //Let player know it is their turn
        cout << ">- Player " << playersTurn % 2 + 1 << "'s turn. Please select a card to guess" << endl;
        cout << ">- These are your cards" << endl;

        //Display all cards, depending on player
        if(playersTurn % 2 == 1)
        {
            for(int i = 0;  i < handOneCount; i++)
            {
                displayCard(handOne[i]); //Call function to display all cards in hand one
            }
        }
        else
        {
            for(int i = 0;  i < handTwoCount; i++)
            {
                displayCard(handTwo[i]); //Call function to display all cards in hand two
            }
        }

        //Always display menu
        displayMenu(menuOptions, 14);
        getInput = getAnswer(14, 0); //now get player's input/choice
        if(getInput < 14) //If player chooses to guess the deck of other
        {
            noMatch = true;
            if(playersTurn % 2 == 1)
            {
                //Check to see if other player has your guess
                for(int i = 0; i < handTwoCount; i++)
                {
                    if(findSimilar(handTwo[i], getInput))
                    {
                        //If yes, switch your empty position with other player's card
                        identityOne = findIdentity(handOne[handOneCount + 1]); //Find identity of first card
                        identityTwo = findIdentity(handTwo[i]); //Find identity of second card
                        handOne[handOneCount + 1] = setCard(handOne[handOneCount + 1], identityTwo, suitOptions, rankOptions, false); //Rebuild first card with second's identity
                        handTwo[i] = setCard(handTwo[i], 100, suitOptions, rankOptions, true); //Rebuilds second card with first's identity

                        //End loop
                        i = 100;
                        noMatch = false;

                    }
                }
                if(noMatch)
                {
                    //If no match is found, "go fish" and get a card from the deck
                    identityOne = findIdentity(handOne[handOneCount + 1]); //Find identity of first card
                    identityTwo = findIdentity(pile[52-deckCount]); //Find identity of second card
                    handOne[handOneCount + 1] = setCard(handOne[handOneCount + 1], identityTwo, suitOptions, rankOptions, false); //Rebuild first card with second's identity
                    pile[52-deckCount] = setCard(pile[52-deckCount], 100, suitOptions, rankOptions, true); //Rebuilds second card with first's identity

                }
                    //Update current card counts
                    handOneCount ++;
                    deckCount --;
            }
            else
            {
                //Check to see if other player has your guess
                for(int i = 0; i < handOneCount; i++)
                {
                    if(findSimilar(handOne[i], getInput))
                    {
                        //If yes, switch your empty position with other player's card
                        identityOne = findIdentity(handTwo[handTwoCount + 1]); //Find identity of first card
                        identityTwo = findIdentity(handOne[i]); //Find identity of second card
                        handTwo[handTwoCount + 1] = setCard(handTwo[handTwoCount + 1], identityTwo, suitOptions, rankOptions, false); //Rebuild first card with second's identity
                        handOne[i] = setCard(handOne[i], 100, suitOptions, rankOptions, true); //Rebuilds second card with first's identity

                        //End loop
                        i = 100;
                        noMatch = false;
                    }
                }
                if(noMatch)
                {
                    //If no match is found, "go fish" and get a card from the deck
                    identityOne = findIdentity(handTwo[handTwoCount + 1]); //Find identity of first card
                    identityTwo = findIdentity(pile[52-deckCount]); //Find identity of second card
                    handTwo[handTwoCount + 1] = setCard(handTwo[handTwoCount + 1], identityTwo, suitOptions, rankOptions, false); //Rebuild first card with second's identity
                    pile[52-deckCount] = setCard(pile[52-deckCount], 100, suitOptions, rankOptions, true); //Rebuilds second card with first's identity

                }
                //Update current card counts
                handTwoCount ++;
                deckCount --;

            }
        }
        system("PAUSE"); //At end get player's input before continuing
        system("CLS"); //Make sure to wipe console
        playersTurn ++; //Set to next player's turn
    }
    return 0; //End program
}

//This function is used to display a specific card
void displayCard(Card myCard)
{
    cout << endl << ">- Suit " << myCard.cardSuit << endl;
    cout << ">- Card Rank " << myCard.cardRank << endl;
    cout << ">- Value " << myCard.cardValue << endl;
    return;
}

//This function is used to set a specific card
Card setCard(Card myCard, int counter, char suitOptions[], string rankOptions[], bool starting)
{
    if(!starting)
    {
        int tempInteger = floor(counter/13); //This is used to store a temporary integer to find a certain value in the array
        myCard.cardSuit = suitOptions[tempInteger]; //Set cardSuit to either position 1-4 of the suits array
        myCard.cardRank = rankOptions[counter % 13]; //Set cardRank to either position 1-13 of the ranks array
        myCard.cardValue = (counter % 13) + 1; //Assign the cards value from 1-13
    }
    myCard.identity = counter; //Assign the cards identity as the counter variable

    return myCard;
}

//This function is used to find the value of the card identity
int findIdentity(Card myCard)
{
    //Return identity value
    return myCard.identity;
}

//This function will try to see if other player has a similar card (Same Rank)
bool findSimilar(Card myCard, int playerGuess)
{
    //Get other cards identity
    int identity = findIdentity(myCard);
    if(identity % 13 == playerGuess)
    { //If player has that same card, return true that you have that card
        cout << "Player Two has your card!" << endl;
        return true;
    }
    else
    { //Otherwise, return false
        return false;
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
