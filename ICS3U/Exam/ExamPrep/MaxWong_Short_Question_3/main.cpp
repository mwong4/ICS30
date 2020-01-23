/*
>- Author: Max Wong
>- Date: Jan 19, 2020
>- Updated: Jan 19, 2020
>- Purpose: Write a program that will:
            - Create a structure called Point containing floats xCoordinate and yCoordinate
            - Create a function that will display the Point to the console window.
            The function must have the prototype: void displayPoint(Point);
            - Use the following code for main( )

            int main( )
            {
                Point newPoint = {5, 7};
                displayPoint( newPoint);
                system(“PAUSE”);
                return EXIT_SUCCESS;
            }
*/
#include <iostream>

using namespace std;

struct Point
{
    float xCoordinate;
    float yCoordinate;
};

void displayPoint(Point); //This is used to display the point

int main()
{
    Point newPoint = {5, 7}; //Initialize the point
    displayPoint(newPoint); //Display Point

    //system("PAUSE"); //Get any input before continuing
    return 0;
}

//This is used to display the point
void displayPoint(Point _point)
{
    cout << "My point is at [" << _point.xCoordinate << "," << _point.yCoordinate << "]" << endl;
    return;
}
