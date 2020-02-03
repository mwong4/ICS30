#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

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

void resetArray(Library&);
bool menu(Library&);
Library createRecord(Library&);
Library writeFile(Library&);
void wipeFile();
int findBook(Library&);
void display (int, Library&, int);
void swapBooks(Book&, Book&);
void displayBooks (int, Library &);
void borrowBook(Library &, int);
void returnBook(Library &, int);

//This function is used to find each line in the map txt file
void resetArray(Library &myLibrary)
{
    string line; //String line used to seperate the text file into lines
    ifstream libraryFile_("Library.txt"); //This is the map file

    int currentRow = 0; //This integer keeps count of the row number for the saving in array

    if(libraryFile_.is_open()) //If instricted to save the file
    {
        while(getline(libraryFile_,line)) //This function uses the builtin function: getline
        {
            if(currentRow % 5 == 0)
            {
                myLibrary.books[myLibrary.numOfBooks].title = line;
            }
            else if(currentRow % 5 == 1)
            {
                myLibrary.books[myLibrary.numOfBooks].author = line;
            }
            else if(currentRow % 5 == 2)
            {
                myLibrary.books[myLibrary.numOfBooks].ISBN = line;
            }
            else if(currentRow % 5 == 3)
            {
                myLibrary.books[myLibrary.numOfBooks].genre = line;
            }
            else if(currentRow % 5 == 4)
            {
                myLibrary.books[myLibrary.numOfBooks].availability = line;
                myLibrary.numOfBooks ++;
            }
            currentRow += 1;
        }
        libraryFile_.close(); //Close file
    }
    return;
}

bool menu(Library &myLibrary)
{
    int choice = 0;
    int bookFound = 0;
    string input = "";
    cout << "Please select the statement that applies to you by entering '1' or '2'." << endl;
    cout << "1. I am a librarian" << endl;
    cout << "2. I am a customer" << endl;
    cout << "3. Quit" << endl;
    cin >> choice;
    cin.ignore();

    system("CLS");

    if (choice == 1)
    {
        cout << "Please select an option by entering one of the numbers listed below." << endl;
        cout << "1. Add a book" << endl;
        cout << "2. Remove a book" << endl;
        cout << "3. Modify the properties of a book" << endl;
        cin >> choice;
        cin.ignore();

        system("PAUSE");
        system("CLS");

        if(choice == 1)
        {
            createRecord(myLibrary);
        }
        else if (choice == 2)
        {
            bookFound = findBook(myLibrary);
            if(bookFound != 10000)
            {
                swapBooks(myLibrary.books[bookFound], myLibrary.books[myLibrary.numOfBooks-1]);
                myLibrary.numOfBooks --;
                wipeFile();
                writeFile(myLibrary);
                cout << "Book Removed" << endl;
            }

        }
        else if (choice == 3)
        {
            bookFound = findBook(myLibrary);
            cout << "What would you like to modify?" << endl;
            cout << "1. Title" << endl;
            cout << "2. Author" << endl;
            cout << "3. ISBN" << endl;
            cout << "4. Genre" << endl;
            cout << "5. Availability" << endl;
            cin >> choice;
            cin.ignore();
            if(choice == 1)
            {
                cout << "What would you like to change it to. It is currently: Title: " << myLibrary.books[bookFound].title << endl;
                cin >> input;
                cin.ignore();
                myLibrary.books[bookFound].title = input;
            }
            else if (choice == 2)
            {
                cout << "What would you like to change it to. It is currently: Author: " << myLibrary.books[bookFound].author << endl;
                cin >> input;
                cin.ignore();
                myLibrary.books[bookFound].author = input;
            }
            else if (choice == 3)
            {
                cout << "What would you like to change it to. It is currently: ISBN: " << myLibrary.books[bookFound].ISBN << endl;
                cin >> input;
                cin.ignore();
                myLibrary.books[bookFound].ISBN = input;
            }
            else if (choice == 4)
            {
                cout << "What would you like to change it to. It is currently: Genre: " << myLibrary.books[bookFound].genre << endl;
                cin >> input;
                cin.ignore();
                myLibrary.books[bookFound].genre = input;
            }
            else if (choice == 5)
            {
                cout << "What status would you like to change it to " << myLibrary.books[bookFound].availability << endl;
                cin >> input;
                cin.ignore();
                myLibrary.books[bookFound].availability = input;
            }
            wipeFile();
            writeFile(myLibrary);
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

        system("PAUSE");
        system("CLS");

        if(choice == 1)
        {
            //Display
            displayBooks (5, myLibrary);
        }
        else if (choice == 2)
        {
            bookFound = findBook(myLibrary);
        }
        else if (choice == 3)
        {
            //borrow
            bookFound = findBook(myLibrary);
            if(bookFound != 10000)
            {
                borrowBook(myLibrary, bookFound);
                wipeFile();
                writeFile(myLibrary);
            }
        }
        else if (choice == 4)
        {
            //return
            bookFound = findBook(myLibrary);
            if(bookFound != 10000)
            {
                returnBook(myLibrary, bookFound);
                wipeFile();
                writeFile(myLibrary);
            }
        }
    }
    else
    {
        return true;
    }
    return false;
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

    cout << "what is the availability of the book? " << endl;
    getline (cin, myLibrary.books[myLibrary.numOfBooks].availability);

    myLibrary.numOfBooks ++;
    wipeFile();
    writeFile(myLibrary);
    return myLibrary;
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
        myfile << myLibrary.books[i].availability << endl;
    }
    return myLibrary;
}

void wipeFile()
{
    std::ofstream ofs;
    ofs.open("Library.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    return;
}

int findBook(Library &myLibrary)
{
    string userSearch;
    int linesInBook;

    //Get search string from user
    cout << "What is the title of the book? ";
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
    return 10000;
}

void display (int linesInBook, Library &myLibrary, int i)
{
    cout << myLibrary.books[i].title << endl;
    cout << myLibrary.books[i].author << endl;
    cout << myLibrary.books[i].ISBN << endl;
    cout << myLibrary.books[i].genre << endl;
    cout << "Status: " << myLibrary.books[i].availability << endl << endl;
}

void displayBooks (int linesInBook, Library &myLibrary)
{
    for(int i=0; i<myLibrary.numOfBooks; i++)
    {
        display(linesInBook, myLibrary, i);
    }
}

void swapBooks(Book& bookOne, Book& bookTwo)
{
    Book tempBook;

    tempBook.title = bookOne.title;
    bookOne.title = bookTwo.title;
    bookTwo.title = tempBook.title;


    tempBook.author = bookOne.author;
    bookOne.author = bookTwo.author;
    bookTwo.author = tempBook.author;


    tempBook.ISBN = bookOne.ISBN;
    bookOne.ISBN = bookTwo.ISBN;
    bookTwo.ISBN = tempBook.ISBN;


    tempBook.genre = bookOne.genre;
    bookOne.genre = bookTwo.genre;
    bookTwo.genre = tempBook.genre;

    tempBook.availability = bookOne.availability;
    bookOne.availability = bookTwo.availability;
    bookTwo.availability = tempBook.availability;
}

void borrowBook(Library &myLibrary, int bookFound)
{
    if(myLibrary.books[bookFound].availability == "Available")
    {
        myLibrary.books[bookFound].availability = "Unavailable";
        cout << "Book has been borrowed" << endl;
    }
    else
    {
        cout << "Sorry, this book is not available" << endl;
    }
    return;
}

void returnBook(Library &myLibrary, int bookFound)
{
    if(myLibrary.books[bookFound].availability == "Unavailable")
    {
        myLibrary.books[bookFound].availability = "Available";
        cout << "Book has been returned" << endl;
    }
    else
    {
        cout << "Sorry, this book is not borrowed?" << endl;
    }
    return;
}

int main()
{
    Library myLibrary;
    myLibrary.numOfBooks=0;
    bool quit = false;

    resetArray(myLibrary);
    cout << "Books in library: " << myLibrary.numOfBooks << endl;

    while(!quit)
    {
        quit = menu(myLibrary);
        system("PAUSE");
        system("CLS");
    }

    return 0;
}
