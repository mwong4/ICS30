#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Book
{
    string title;
    string author;
    string ISBN;
    string genre;
    string availability;
};

struct Library
{
    Book books[1000];
    int numOfBooks;
};

Library writeFile(Library &);
int readFile(Library &);
Library createRecord(Library &);

float menu(int choice, Library &myLibrary)
{
    cout << "Please select the statement that applies to you by entering '1' or '2'." << endl;
    cout << "1. I am a librarian" << endl;
    cout << "2. I am a customer" << endl;
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        cout << "Please select an option by entering one of the numbers listed below." << endl;
        cout << "1. Add a book" << endl;
        cout << "2. Remove a book" << endl;
        cout << "3. Modify the properties of a book" << endl;
        cin >> choice;
        cin.ignore();

            if(choice == 1)
            {
                //readFile(myLibrary);
                //createRecord(myLibrary);
            }
            else if (choice == 2)
            {
                //delete
            }
            else if (choice == 3)
            {
                //modify
            }

    }
    else if (choice == 2)
    {
        cout << "Please select an option by entering one of the numbers listed below." << endl;
        cout << "1. Examine the library's content" << endl;
        cout << "2. Search for a book" << endl;
        cout << "3. Borrow a book" << endl;
        cout << "4. Return a book" << endl;
        cin >> choice;
        cin.ignore();
            if(choice == 1)
            {
                //Display
            }
            else if (choice == 2)
            {
                //search
            }
            else if (choice == 3)
            {
                //borrow
            }
            else if (choice == 4)
            {
                //return
            }
    }
}

Library createRecord(Library &myLibrary)
{
    cout << "what is the title of the book? " << endl;
    getline (cin, myLibrary.books[myLibrary.numOfBooks].title);

    cout << "who is the author of the book? " << endl;
    getline (cin, myLibrary.books[myLibrary.numOfBooks].author);

    cout << "what is the ISBN of the book? " << endl;
    getline (cin, myLibrary.books[myLibrary.numOfBooks].ISBN);

    cout << "what is the genre of the book? " << endl;
    getline (cin, myLibrary.books[myLibrary.numOfBooks].genre);

    writeFile(myLibrary);
    myLibrary.numOfBooks ++;
    return myLibrary;
}

int readFile(Library &myLibrary)
{
    int linesInBook=0;
    ifstream myfile;
    myfile.open ("Library.txt");

    while(!myfile.eof())
    {
        getline(myfile, myLibrary.books[linesInBook].title);
        getline(myfile, myLibrary.books[linesInBook].author);
        getline(myfile, myLibrary.books[linesInBook].ISBN);
        getline(myfile, myLibrary.books[linesInBook].genre);
        linesInBook++;
    }
    myLibrary.numOfBooks = linesInBook;
    myfile.close();
    return linesInBook;
}

Library writeFile(Library &myLibrary)
{
    ofstream myfile;
    myfile.open("Library.txt");
    for(int i = 0; i < myLibrary.numOfBooks; i++)
    {
        myfile << myLibrary.books[i].title << endl;
        myfile << myLibrary.books[i].author << endl;
        myfile << myLibrary.books[i].ISBN << endl;
        myfile << myLibrary.books[i].genre << endl;
    }

    return myLibrary;
}


int display (int linesInBook, Library &myLibrary, int i)
{
    cout << myLibrary.books[i].title << endl;
    cout << myLibrary.books[i].author << endl;
    cout << myLibrary.books[i].ISBN << endl;
    cout << myLibrary.books[i].genre << endl << endl;
}

int findBook(Library &myLibrary)
{
    string userSearch;
    int linesInBook;

    //Get search string from user
    //cout << "What is the title of the book you would like to search for? ";
    getline(cin, userSearch);

    //Compare Library file contents with user search string
    for(int i=0; i < myLibrary.numOfBooks; i++)
    {
        if (userSearch == myLibrary.books[i].title)
        {
            cout << "\nMatch!! User selection is in file!\n\n";
            display(linesInBook, myLibrary, i);
            return i;
        }
    }
    cout << endl << "No Match" << endl << endl;
}

void deleteBook(Library &, int i)
{
    //int answer=;
    cout << "What is the name of the book you would like to delete? ";
    //findBook(myLibrary);
}

int positionOfBook(Library myLibrary, string )
{

}



int main()
{
    int linesInBook;
    int i, choice;

    Library myLibrary;
    myLibrary.numOfBooks=0;

    do
    {
        menu(choice, myLibrary);
        //linesInBook = readFile(myLibrary);
        //i = findBook(myLibrary);
        //myLibrary = createRecord(myLibrary);
        //display(linesInBook, myLibrary);
    }while(1==1);


}
