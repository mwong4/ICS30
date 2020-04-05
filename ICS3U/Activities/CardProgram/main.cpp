/*
>- Author: Max Wong
>- Date: Dec 5, 2019
>- Updated: Dec 12, 2019
>- Purpose: To write a card program using structs
>-
>- Thanks to Thomas Maloley for teaching me how to program with C++

TO DO
 -Cleaning
 -Better display
 -Set individual value
*/

//Libraries used
#include <iostream>
#include<limits> //For error trapping
#include<windows.h> //For rand and system

//Pre-processor commands used
using namespace std;

//This structure holds the values of the card
struct Card{
    char cardSuit; //Card suit saved as char
    string cardRank; //Card rank saved as string
    int cardValue; //Card value saved as integer
    int identity; //Card indetity saved as integer
} myCards[52]; //Have an array of structures/cards


//Defining functions used
void displayCard(Card); //This function is used to display a specific card
Card setCard(Card, int); //This function is used to set a specific card
int findIdentity(Card); //THis function is used to find the specific identity of a card

void displayMenu(string[], int); //Function to show the menu: All positions are options except last which is reserved for quit number
int getAnswer(int, int); //Function used to get the players response as an integer (with error trapping)

//Defining Global Variables Used
const int DECKSIZE = 52;

int main()
{
    int getInput = 0; //This integer is used to get player input as to what they would like to do

    int cardToChange; //This integer get's player's input to decide what card to change
    int valueToChange; //This integer get's the players input to deide chat value to change a card to

    int identityOne; //this variable holds the value of the first selected card's identity
    int identityTwo; //this variable holds the value fo the seond selected card's identity
    int secondCardToSwap; //this integer saves the value of the second card to be swapped

    int viewWhichCard = 0; //this integer is to get the player's input of which card they would like to read
    //This string array saves all the menu options
    string menuOptions[6] = {"Display card", "Display all cards", "Reset all card values", "Change one card", "Shuffle deck", "To quit"};

    //Just run through the whole cards array and reset to identity 0
    for(int i = 0; DECKSIZE > i; i++)
    {
        myCards[i] = setCard(myCards[i], 0);
    }

    //While the player does not choose to quit (6)
    while(getInput != 6)
    {
        //Always display menu
        displayMenu(menuOptions, 6);
        getInput = getAnswer(6, 0); //now get player's input/choice

        if(getInput == 1) //If option 1 is chosen
        {
            cout << ">- Please indicate the card you would like to display (from 0 to 51)" << endl;
            viewWhichCard = getAnswer(51,0); //Get a specific card to display
            displayCard(myCards[viewWhichCard]); //Then call function to display it
        }
        else if(getInput == 2) //If option 2 is chosen
        {//Run through every position in the deck
            for(int i = 0; DECKSIZE > i; i++)
            {
                displayCard(myCards[i]); //And display every position
            }
        }
        else if(getInput == 3) //If option 3 is chosen
        {
            for(int i = 0; DECKSIZE > i; i++) //Run through every position of the deck
            {
                myCards[i] = setCard(myCards[i], i); //And reset it to default deck
            }
        }
        else if(getInput == 4) //If option 4 is chosen
        {
            cout << "Please pick card to manipulate (0-51)" << endl;
            cardToChange = getAnswer(51,0); //Get player input on what deck to manipulate
            cout << "Now please enter identity (0-51)" << endl;
            valueToChange = getAnswer(51,0); //Get player input on what new indentity to give it
            //Need to work on this system -> Ask Mr Maloley how he wants this, free reaigh or restricted?
            myCards[cardToChange] = setCard(myCards[cardToChange], valueToChange); //Next, call the function to reassign identity and other info
        }
        else if(getInput == 5) //If option 5 is chosen
        {//Run through every card in the deck
            for(int i = 0; DECKSIZE > i; i++)
            {//Find a random card to swap with to shuffle
                secondCardToSwap = rand()% 51;

                identityOne = findIdentity(myCards[i]); //Find identity of first card
                identityTwo = findIdentity(myCards[secondCardToSwap]); //Find identity of second card
                myCards[i] = setCard(myCards[i], identityTwo); //Rebuild first card with second's identity
                myCards[secondCardToSwap] = setCard(myCards[secondCardToSwap], identityOne); //Rebuilds second card with first's identity
            }
        }
        system("PAUSE"); //At end get player's input before continuing
        system("CLS"); //Make sure to wipe console
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
Card setCard(Card myCard, int counter)
{
    myCard.cardValue = (counter % 13) + 1; //Assign the cards value from 1-13
    myCard.identity = counter; //Assign the cards identity as the counter variable

    //Run through 13 if statements to define it's Rank
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
    //Run through 4 if statements to define it's Suit
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
    //Return identity value
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
