/*
>- Author: Max Wong
>- Date: Sep 19, 2019
>- Updated: Oct 21, 2019
>- Purpose: To write a multiple choice quiz
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
*/
//included liraries
#include <iostream>
#include <conio.h>
#include <windows.h> //For color
#include<limits> //For error trapping


//using namespace declarations
using namespace std;

//Declaring functions
int getAnswer(); //Get player input. Check to see if there is an error
void getChar(); //Get any player input before continuing

int questionOne(); //This function is to ask the first question
int questionTwo(); //This function is to ask the second question
int questionThree(); //This function is to ask the third question
int questionFour(); //This function is to ask the fourth question
int questionFive(); //This function is to ask the fifth question

int askQuestion(int, string, string, string, string, int);
int checkAnswer(int, int);

//Main loop
int main()
{
    int answerNumber = 0;//This stores the player's answer
    int pointsCounter; //This variable keeps track of your score

    //For color to consol
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //welcoming screen
    cout << endl << ">- Welcome to the multiple choice quiz assignment that I made" << endl;
    cout << ">- last minute cause I didnt know it existed" << endl;
    getChar();
    system("CLS");

    do
    {
        //Reset values
        pointsCounter = 0;

        //Calling the function to ask the first question
        pointsCounter += askQuestion(1, "What is my favorite animal?", "Crow", "Owl", "Targdigrade", 3);
        getChar();
        system("CLS");

        //Calling the function to ask the second question
        pointsCounter += askQuestion(2, "What is my favorite saying?", "I don't share cause I'm not a communist!", "Quad Erat Demonstratum", "Makin Bakin Pancakes?", 1);
        getChar();
        system("CLS");
        //Calling the function to ask the third question
        pointsCounter += askQuestion(3, "What is my favorite formula?", "Snells law", "Binomial Theorum", "Quadratic equation", 2);
        getChar();
        system("CLS");
        //Calling the function to ask the fourth question
        pointsCounter += askQuestion(4, "What's my favorite TV show?", "Adventure Time", "I don't watch TV", "House MD", 2);
        getChar();
        system("CLS");
        //Calling the function to ask the fifth question
        pointsCounter += askQuestion(5, "What is the book I just finished?", "Red Platoon", "Tribe", "The Martian", 1);
        getChar();
        system("CLS");

        //Show results and ask player if they would like to play again
        cout << ">- Yay! your done. You got " << pointsCounter << "/5" << endl;
        cout << endl << ">- Would you like to play again?" << endl << "1) to play again" << endl << "2) to quit" << endl;
        answerNumber = getAnswer();

    //If they answer yes, loop
    }while(answerNumber == 1);

    system("CLS");
    cout << "Ok, bye!" << endl;
    getChar();
    //Otherwise, return
    return 0;
}

//Get player input. Check to see if there is an error
int getAnswer ()
{
    int playerInput; //This variable is used to get the player's input
    bool findingInput; //This bool determines if the loop continues running

    //For color to consol
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    do
    {
        //By default, the loop will end
        findingInput = false;

        //Get player input
        cout << "Your answer: ";
        cin >> playerInput;
        //Check to see if player entered a "bad" input type
        if(cin.fail())
        {
            cin.clear();

            //To do : play around with cin.ignore attribute
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            SetConsoleTextAttribute(hConsole, 12);
            cout << endl << ">- [Error], please enter an integer value!" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            Sleep(100);

            findingInput = true; //If the input is invalid, then the loop will loop
        }
        //Else if player input is not between 1 to 3, pritn error message
        else if( playerInput <= 0 || playerInput >= 4)
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << endl << ">- [Error], please enter an value between 1 and 3!" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            Sleep(100);

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
    getch();
}

//This function asks the questions
int askQuestion(int currentQuestionNumber, string currentQuestion, string choiceOne, string choiceTwo, string choiceThree, int correctAnswer )
{
    //Print question
    cout << "=====================" << endl << " <> Question "<< currentQuestionNumber << " </>" << endl;
    cout << currentQuestion << endl;
    cout << "=====================" << endl;
    cout << "1) " << choiceOne << endl << "2) " << choiceTwo << endl << "3) " << choiceThree << endl;
    //Get response

    return checkAnswer(getAnswer(), correctAnswer);
}

//This function checks if the answer is correct
int checkAnswer(int playerInput, int correctAnswer)
{
    //For color to consol
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //Check Answer. If correct, give points
    if(playerInput == correctAnswer)
    {
        cout << endl << ">- Yay! You are correct" << endl;
        return 1;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << endl << ">- Oh no! You got it wrong" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return 0;
    }

}
