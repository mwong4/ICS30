/* The purpose of this program is to give the user a multiple choice quiz 
and to increase their score by one for each question that the user answers correctly.
*/

#include <cstdlib>
#include <iostream>

using namespace std;

bool question1();
bool question2();
bool question3();

bool question1()
{   string response = "";
    
    cout << "What is the capital of France? " << endl;
    cout << "a) Paris" << endl;
    cout << "b) Bordeaux" << endl
    cout << "c) Versailles" << endl;
    
    cin >> response;
    
    if (response = "a")
    {   isItCorrect = true;   
        cout << "CORRECT !!!" << endl;
    }
    else
    {   cout << "Wrong!" << endl;
    }
    
    return isItCorrect;
}

int question2()
{   bool isItCorrect = false;
    string response = "";
    
    cout << "What is 2 + 2 ? " << endl;
    cout << "a) 5" << endl;
    cout << "b) 4" << endl;
    cout << "c) 3" << endl;
    
    cin >> response;
    
    if (response == 'b')
    {   
        cout << "CORRECT !!!" << endl;
    }
    else
    {   cout << "Wrong!" << endl;
    }
    
    return isItCorrect;
}

bool question3()
{   bool isItCorrect = false;
    string response = "";
    
    cout << "Who is your favourite teacher ? " << endl;
    cout << "a) Mr. Maloley" << endl;
    cout << "b) Ms. Mroz" << endl;
    cout << "c) Mr. Archibald" << endl;
    cout << "d) Life" << endl;
    
    cin << response;
    
    if (response == "d")
    {   isItCorrect = true;
        cout << "CORRECT !!!" << endl;
    }
    else (response == "a")
    {   cout << "Nice try but wrong" << endl;
    }
    else
    {   cout << "Wrong!" << endl;
    } 
    
    return;
}    



int main(int argc, char *argv[])
{   int score = 0;
    
    cout << "Welcome to this horrible multiple choice quiz!!!" << endl;
    cout << "Please respond by choosing the letter associated with your selection." << endl;
    system("PAUSE");
    system("CLS");
    
    if (question1())
    {   score ++;
    }
    system(PAUSE);
    system("CLS");
    
    if (question2())
    {   score +;
    }
    system("PAUSE");
    system("CLS");
    
    if (question3())
    {   score == score + 1;
    }
    system("PAUSE");
    system("CLS");
    
    cout << "Your score was " score  " out of 3." << endl;
    cout << "I hope you had fun" << endl;
    

    system("PAUSE");
    
    return EXIT_SUCCESS;
}
