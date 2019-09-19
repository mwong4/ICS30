/*
>- Author: Max Wong
>- Date: Sep 19, 2019
>- Updated: Sep 19, 2019
>- Purpose: To write a multiple choice quiz
>-
>-Thanks to Thomas Maloley for teaching me how to program with C++
>-
>- [TO DO]
>- Error trapping delay bug
>-
*/

//included liraries
#include <iostream>
#include <conio.h>
#include <windows.h>


//using namespace declarations
using namespace std;

//Declaring functions
int getAnswer(); //Get player input. Check to see if there is an error
void getChar(); //Get any player input before continuing

//Main loop
int main()
{
    int answerNumber = 0;
    int pointsCounter;

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

        //Print question
        cout << "=====================" << endl << " <> Question 1 </>" << endl;
        cout << "What is my favorite animal?" << endl;
        cout << "=====================" << endl;
        cout << "1) Crow" << endl << "2) Owl" << endl << "3) Targdigrade" << endl;
        //Get response
        answerNumber = getAnswer();

        //Check Answer. If correct, give points
        switch(answerNumber)
            {
            case 3:
                cout << endl << ">- Yay! You are correct" << endl;
                pointsCounter += 1;
                break;

            default:
                SetConsoleTextAttribute(hConsole, 12);
                cout << endl << ">- Poop! Got it wrong" << endl;
                SetConsoleTextAttribute(hConsole, 15);
                break;
        }
        getChar();
        system("CLS");

        //Print question
        cout << "=====================" << endl << " <> Question 2 </>" << endl;
        cout << "What is my favorite saying?" << endl;
        cout << "=====================" << endl;
        cout << "1) I don't share cause I'm not a communist!" << endl << "2) Quad Erat Demonstratum" << endl << "3) Makin Bakin Pancakes?" << endl;
        //Get response
        answerNumber = getAnswer();

        //Check Answer. If correct, give points
        switch(answerNumber)
            {
            case 1:
                cout << endl << ">- Yay! +1 to hunger" << endl;
                pointsCounter += 1;
                break;

            default:
                SetConsoleTextAttribute(hConsole, 12);
                cout << endl << ">- What! how could you?" << endl;
                SetConsoleTextAttribute(hConsole, 15);
                break;
        }
        getChar();
        system("CLS");

        //Print question
        cout << "=====================" << endl << " <> Question 3 </>" << endl;
        cout << "What is my favorite formula?" << endl;
        cout << "=====================" << endl;
        cout << "1) Snells law" << endl << "2) Binomial Theorum" << endl << "3) Quadratic equation" << endl;
        //Get response
        answerNumber = getAnswer();

        //Check Answer. If correct, give points
        switch(answerNumber)
            {
            case 2:
                cout << endl << ">- Praise the sun!" << endl;
                pointsCounter += 1;
                break;

            default:
                SetConsoleTextAttribute(hConsole, 12);
                cout << endl << ">- Poop! YOU DIED" << endl;
                SetConsoleTextAttribute(hConsole, 15);
                break;
        }
        getChar();
        system("CLS");

        //Show results and ask player if they would like to play again
        cout << ">- Yay! your done. You got " << pointsCounter << "/3" << endl;
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

    //For color to consol
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Get player input
    cout << "Your answer: ";
    cin >> playerInput;
    //Check to see if player entered a "bad" input type
    if(cin.fail())
    {
        cin.clear();

        //To do : play around with cin.ignore attribute
        cin.ignore(9);

        SetConsoleTextAttribute(hConsole, 12);
        cout << endl << ">- [Error], please enter an integer value!" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        Sleep(100);
        playerInput = getAnswer();
    }
    //Else if player input is not between 1 to 3, pritn error message
    if( playerInput <= 0 || playerInput >= 4)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << endl << ">- [Error], please enter an value between 1 and 3!" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        Sleep(100);
        playerInput = getAnswer();
    }
    //Otherwise input is good, return input
        return playerInput;
}

//Function to get any key input to continue
void getChar ()
{
    cout << "[Press any key to continue]" << endl;
    getch();
}
