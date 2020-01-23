/*
>- Author: Max Wong
>- Date: Jan 21, 2020
>- Updated: Jan 21, 2020
>- Purpose:

        - Create a structure called Student made up of strings firstName and lastName an integer age.
        - Create a function that will display the student in a single line.
        For example if the student was name John Doe and was 12 yrs old then the program
        would display: “Name: Doe, John Age: 12”
        The function must have the prototype: void displayStudent(Student);
        - Use the following code for main( )

        int main( )
        {
            Student newStudent = {“Bob”, “Dole”, 14};
            displayStudent( newStudent);
            system(“PAUSE”);
            return EXIT_SUCCESS;
        }
*/

#include <iostream>
#include <windows.h> //For system pause

using namespace std;

struct Student
{
    string firstName; //This represents the student's first name
    string lastName; //This represents the student's last name
    int age; //This represents the student's age
};

void displayStudent(Student); //This is for displaying the students information

int main()
{
    Student newStudent = {"Bob", "Dole", 14};
    displayStudent( newStudent);
    system("PAUSE");
    return 0;
}

//This is for displaying the students information
void displayStudent(Student _studentData)
{
    cout << "Name: " << _studentData.lastName << ", " << _studentData.firstName << "    Age: " << _studentData.age << endl; //Display students info
    return;
}
