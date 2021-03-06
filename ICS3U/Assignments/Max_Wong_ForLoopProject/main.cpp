/*
>- Author: Max Wong
>- Date: Sep 25, 2019
>- Updated: Sep 27, 2019
>- Purpose: To write a number guessing game using a for loop
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
*/

//Declaring used libraries
#include <iostream>
#include<limits> //For error trapping
#include <conio.h> //For getch();

//Declaring using namespace
using namespace std;

//Declaring Functions
int getAnswer(); //Function used to get the players response as an integer (with error trapping)
void getChar(); //Get any player input before continuing

//Loops
int main()
{
    int targetNumber; //An integer that is the number the player will be guessing
    int guessedNumber; //An integer that holds the value of the player's guess
    int scoreCounter = 0; //This integer keeps track of the player's points
    bool playingGame = true; //This boolean checks to see if the player wants to play again

    while(playingGame)
    {
        targetNumber = rand() % 101; //Assign the target a random value
        cout << ">- For debugging: The target number: " << targetNumber << endl << endl; //Print out the answer for debugging

        //The loop will run for i times
        for(int i = 10; i > 0; i--)
        {
            //Display UI elements
            cout << ">- Current score: [" << scoreCounter << "]" << endl;
            cout << ">- Number of guesses left: [" << i << "]" << endl << endl;

            //Get the player's input
            guessedNumber = getAnswer();
            cout << endl;

            //If the guessed number is the right number, reward # of points = to the remaining turns
            if(guessedNumber == targetNumber)
            {
                cout << ">- Yay! You got it! You won "<< i << " points!" << endl;
                scoreCounter += i;
                i = 0;
            }
            //Otherwise, if the player has not run out of turns yet, display this message
            else if(i != 1)
            {
                cout << endl << ">- Oh, so close! Guess again!" << endl;
            }
            //Otherwise, when player has run out of turns, display this message
            else
            {
                cout << endl << ">- Sorry you ran out of guesses!" << endl;
            }

            //Get any input before cleairng console
            getChar();
            system("CLS");
        }

        /*
            === Loop Description ===
            This loop will loop 10 times, each time asking for the player's input. If the players input is correct, reward players #
            of points equivalent to the remaining turns and end the loop. Otherwise if the player still has turns, give some feedback and loop.
            If the player runs out of turns, return feedback before exiting the loop.
        */

        //Ask player if they want to play again. If yes, play again
        cout << ">- Yay, you scored: " << scoreCounter << " points" << endl;
        cout << endl << ">- Would you like to play again?" << endl << ">- If yes, choose [1]" << endl;
        guessedNumber = getAnswer();
        if(guessedNumber != 1) //If they dont answer to play again, exit
        {
            playingGame = false;
        }
        system("CLS");
    }

    //If they choose to end game, exit
    cout << ">- Bye!" << endl;
    return 0;
}

//Get player input. Check to see if there is an error
int getAnswer ()
{
    int playerInput; //This variable is used to get the player's input
    bool findingInput; //This bool determines if the loop continues running

    do
    {
        //By default, the loop will end
        findingInput = false;

        //Get player input
        cout << ">- Your guess: ";
        cin >> playerInput;
        //Check to see if player entered a "bad" input type
        if(cin.fail())
        {
            cin.clear(); //Clear all flags

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore incorrect symbols

            cout << endl << ">- [Error], please enter an integer value!" << endl;

            findingInput = true; //If the input is invalid, then the loop will loop
        }
        //Else if player input is not between 1 to 3, pritn error message
        else if( playerInput < 0 || playerInput > 100)
        {
            cout << endl << ">- [Error], please enter an value between 1 and 100!" << endl;

            findingInput = true; //If the input is invalid, then the loop will loop
        }
    }while(findingInput);
    //Otherwise input is good, return input
    return playerInput;
}

//Function to get any key input to continue
void getChar ()
{
    cout << "[Press any key to continue]" << endl;
    //Get any input before continuing
    getch();
}
