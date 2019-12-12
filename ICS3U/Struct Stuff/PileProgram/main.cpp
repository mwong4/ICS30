/*
>- Author: Max Wong
>- Date: Dec 5, 2019
>- Updated: Dec 12, 2019
>- Purpose: To write a card program using structs [version 2]
>-
>- Thanks to Thomas Maloley for teaching me how to program with C++

TO DO
-Pile thing
 -Cleaning
 -Better display
 -Set individual value
 -Do gold fish mechanics
*/

//Libraries used
#include <iostream>
#include <limits> //For error trapping
#include <tgmath.h> //For floor function

//Pre-processor commands used
using namespace std;

//This structure holds the values of the card
struct Card{
    char cardSuit; //Card suit saved as char
    string cardRank; //Card rank saved as string
    int cardValue; //Card value saved as integerds
    int identity; //Card indetity saved as integer
} pile[52]; //Have an array of structures/cards

//Defining functions used
void displayCard(Card); //This function is used to display a specific card
Card setCard(Card, int, char[], string[]); //This function is used to set a specific card
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

    //this char array represents the possible suits
    char suitOptions[4] = {'S', 'H', 'C', 'D'};
    //this string array represents the different rank's possible
    string rankOptions[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    //Just run through the whole cards array and reset to identity 0
    for(int i = 0; DECKSIZE > i; i++)
    {
        pile[i] = setCard(pile[i], 0, suitOptions, rankOptions);
    }

    //While the player does not choose to quit (6)
    while(getInput != 6)
    {
        //Always display menu
        displayMenu(menuOptions, 6);
        getInput = getAnswer(6, 0); //now get player's input/choice

        if(getInput == 1) //If option 1 is chosen
        {
            cout << ">- Please the card you would like to display (from 0 to 51)" << endl;
            viewWhichCard = getAnswer(51,0); //Get a specific card to display
            displayCard(pile[viewWhichCard]); //Then call function to display it
        }
        else if(getInput == 2) //If option 2 is chosen
        {//Run through every position in the deck
            for(int i = 0; DECKSIZE > i; i++)
            {
                displayCard(pile[i]); //And display every position
            }
        }
        else if(getInput == 3) //If option 3 is chosen
        {
            for(int i = 0; DECKSIZE > i; i++) //Run through every position of the deck
            {
                pile[i] = setCard(pile[i], i, suitOptions, rankOptions); //And reset it to default deck
            }
        }
        else if(getInput == 4) //If option 4 is chosen
        {
            cout << "Please pick card to manipulate (0-51)" << endl;
            cardToChange = getAnswer(51,0); //Get player input on what deck to manipulate
            cout << "Now please enter identity (0-51)" << endl;
            valueToChange = getAnswer(51,0); //Get player input on what new indentity to give it
            //Need to work on this system -> Ask Mr Maloley how he wants this, free reaigh or restricted?
            pile[cardToChange] = setCard(pile[cardToChange], valueToChange, suitOptions, rankOptions); //Next, call the function to reassign identity and other info
        }
        else if(getInput == 5) //If option 5 is chosen
        {//Run through every card in the deck
            for(int i = 0; DECKSIZE > i; i++)
            {//Find a random card to swap with to shuffle
                secondCardToSwap = rand()% 51;

                identityOne = findIdentity(pile[i]); //Find identity of first card
                identityTwo = findIdentity(pile[secondCardToSwap]); //Find identity of second card
                pile[i] = setCard(pile[i], identityTwo, suitOptions, rankOptions); //Rebuild first card with second's identity
                pile[secondCardToSwap] = setCard(pile[secondCardToSwap], identityOne, suitOptions, rankOptions); //Rebuilds second card with first's identity
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
Card setCard(Card myCard, int counter, char suitOptions[], string rankOptions[])
{
    int tempInteger = floor(counter/13); //This is used to store a temporary integer to find a certain value in the array
    myCard.cardSuit = suitOptions[tempInteger]; //Set cardSuit to either position 1-4 of the suits array
    myCard.cardRank = rankOptions[counter % 13]; //Set cardRank to either position 1-13 of the ranks array
    myCard.cardValue = (counter % 13) + 1; //Assign the cards value from 1-13
    myCard.identity = counter; //Assign the cards identity as the counter variable

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
