/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

struct Fraction
{
    int numerator;
    int denominator;
};

int menu_choice();
void initialize_fraction (Fraction&);
int fraction_choice();
void display_fraction (Fraction);
int unit_choice (string, string, string);
int GCD (Fraction, Fraction);
void compare_fractions (Fraction, Fraction);
void simplify_fractions (Fraction&, Fraction&, int);

int main()
{
    Fraction fraction1, fraction2;
    int menu_response, gcd;
    int choice1, choice2, choice3, choice4;
    int add_numerator, add_denominator, minus_numerator, minus_denominator;

    initialize_fraction (fraction1);
    initialize_fraction (fraction2);
    gcd = GCD (fraction1, fraction2);
    simplify_fractions (fraction1, fraction2, gcd);

    do
    {
        menu_response = menu_choice();

        if (menu_response == 1)// menu option 1
        {
        choice1 = fraction_choice();

        if (choice1 == 1)
        {
            display_fraction (fraction1);
        }
        else if (choice1 == 2)
        {
            display_fraction (fraction2);
        }
    }
        else if (menu_response == 2)// menu option 2
        {
            choice2 = fraction_choice();

            if (choice2 == 1)
            {
                initialize_fraction (fraction1);
            }
            else if (choice2 == 2)
            {
                initialize_fraction (fraction2);
            }
            gcd = GCD (fraction1, fraction2);
            simplify_fractions (fraction1, fraction2, gcd);
        }
        else if (menu_response == 3)//menu option 3
        {
            choice3 = unit_choice ("add", "subtract", "minus");

            if (choice3 = 1)// add them
            {
                add_numerator = ((fraction1.numerator * fraction2.denominator) + (fraction2.numerator * fraction1.denominator)) / gcd;
                add_denominator = (fraction1.denominator * fraction2.denominator) / gcd;
                cout << "When added together they equal ";
                cout << add_numerator << "/" << add_denominator << endl;
            }
            else if (choice3 == 2)// subtract them
            {
                minus_numerator = ((fraction1.numerator * fraction2.denominator) - (fraction2.numerator * fraction1.denominator)) / gcd;
                minus_denominator = (fraction1.denominator * fraction2.denominator) / gcd;
                cout << "When added together they equal ";
                cout << minus_numerator << "/" << minus_denominator << endl;
            }
        }
        else if (menu_response == 4)//menu option 4
        {
            choice4 = unit_choice ("multiply", "divide", "divided by");
            gcd = GCD (fraction1, fraction2);

            if (choice4 = 1)// multiply them
            {
                cout << "When multiplied they equal " << (fraction1.numerator * fraction2.numerator) / gcd;
                cout << "/" << (fraction1.denominator * fraction2.denominator) / gcd;
            }
            else if (choice4 == 2)// divide them
            {
                cout << "When divided they equal " << (fraction1.numerator * fraction2.denominator) / gcd;
                cout << "/" << (fraction1.denominator * fraction2.numerator) / gcd;
            }
        }
        else if (menu_response == 5)//mmenu option 5
        {
            compare_fractions (fraction1, fraction2);
        }
    }
    while (menu_response != 6);
}

int menu_choice()
{
    int response;

    do
    {
        cout << "What do you want to do with your fractions?\n1) Display a fraction:  ";
        cout << "2) Modify a fraction:  3) Add/Subtract the fractions:  ";
        cout << "4) Multiply/Divide the fractions:  5) Compare the fractions:  6) Quit" << endl;
        cin >> response;

        if (response < 1 || response > 6)
        {
            cout << "Invalid Response" << endl;
        }
    }
    while (response < 1 || response > 6);

    return response;
}

void initialize_fraction (Fraction& fraction_num)
{
    cout << "Enter numerator then denominator of " << "." << endl;
    cin >> fraction_num.numerator >> fraction_num.denominator;

    return;
}

int fraction_choice()
{
    int response;

    do
    {
        cout << "Which fraction do you want to see?\n1) Fraction1:  2) Fracton2" << endl;
        cin >> response;

        if (response < 1 || response > 2)
        {
            cout << "Invalid Response" << endl;
        }
    }
    while (response < 1 || response > 2);

    return response;
}

void display_fraction (Fraction fraction_num)
{
    cout << "The values of " << " is " << fraction_num.numerator;
    cout << "/" << fraction_num.denominator << endl;

    return;
}

int unit_choice (string unit1, string unit2, string unit2_reworded)
{
    int response;

    do
    {
        cout << "Do you want to 1) " << unit1 << " or 2) " << unit2;
        cout << "(fraction1 " << unit2_reworded << " fraction2)" << endl;
        cin >> response;

        if (response < 1 || response > 2)
        {
            cout << "Invalid Response" << endl;
        }
    }
    while (response < 1 || response > 2);

    return response;
}

int GCD (Fraction fraction1, Fraction fraction2)
{
    int gcd, total1, total2;

    total1 = fraction1.numerator / fraction1.denominator;
    total2 = fraction2.numerator / fraction2.denominator;

    if (total1 > total2)
    {
        gcd = fraction1.denominator % fraction2.denominator;
    }
    else if (total2 > total1)
    {
        gcd = fraction2.denominator % fraction1.denominator;
    }
    else if (total1 == total2)
    {
        gcd = fraction1.denominator;
    }

    return gcd;
}

void compare_fractions (Fraction fraction1, Fraction fraction2)
{
    int total1, total2;

    total1 = fraction1.numerator / fraction1.denominator;
    total2 = fraction2.numerator / fraction2.denominator;

    if (total1 > total2)
    {
        cout << fraction1.numerator << "/" << fraction1.denominator;
        cout << " > " << fraction2.numerator << "/" << fraction2.denominator << endl;
    }
    else if (total2 > total1)
    {
        cout << fraction1.numerator << "/" << fraction1.denominator;
        cout << " < " << fraction2.numerator << "/" << fraction2.denominator << endl;
    }
    else if (total2 == total1)
    {
        cout << fraction1.numerator << "/" << fraction1.denominator;
        cout << " = " << fraction2.numerator << "/" << fraction2.denominator << endl;
    }

    return;
}

void simplify_fractions (Fraction& fraction1, Fraction& fraction2, int gcd)
{
    fraction1.numerator = fraction1.numerator / gcd;
    fraction1.denominator = fraction1.denominator / gcd;
    fraction2.numerator = fraction2.numerator / gcd;
    fraction2.denominator = fraction2.denominator / gcd;

    return;
}

