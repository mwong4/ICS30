/*
>- Author: Max Wong
>- Date: Jan 21, 2020
>- Updated: Jan 21, 2020
>- Purpose:
    - Use main( ) to ask the user for a float representing a mass in pounds.
    - Call a function to determine the equivalent mass in kilograms.
    - Use main() to display the converted weight to the user.
*/

#include <iostream>

using namespace std;

float metricConverter(float); //This function is in charge of converting the value from pounds to kilograms

int main()
{
    float kilogramMass; //This is the converted value in kilograms
    float poundMass; //This float represents the user's input in pounds
    cout << "Hello, please input a mass in pounds" << endl; //Tell user instructions
    cin >> poundMass; //Get user input

    kilogramMass = metricConverter(poundMass); //Call function to convert value
    cout << "Your mass in kilograms is: " << kilogramMass << endl; //Give user value in metric

    return 0;
}

//This function is in charge of converting the value from pounds to kilograms
float metricConverter(float poundMass)
{
    return (poundMass * 0.453514739); //Convert and return value in kilograms
}
