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

Library createRecord(Library &theLibrary)
{
    string str;

    cout << "what is the title of the book? " << endl;
    getline (cin, theLibrary.books[theLibrary.numOfBooks].title);

    cout << "who is the author of the book? " << endl;
    getline (cin, theLibrary.books[theLibrary.numOfBooks].author);

    cout << "what is the ISBN of the book? " << endl;
    getline (cin, theLibrary.books[theLibrary.numOfBooks].ISBN);

    cout << "what is the genre of the book? " << endl;
    getline (cin, theLibrary.books[theLibrary.numOfBooks].genre);

    writeFile(theLibrary);
    theLibrary.numOfBooks ++;
    return theLibrary;
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
        myfile.close();
        return linesInBook;
}

Library writeFile(Library &theLibrary)
{
    ofstream myfile;
    myfile.open("Library.txt");
    cout << theLibrary.books[theLibrary.numOfBooks].title << endl;
    myfile << theLibrary.books[theLibrary.numOfBooks].title << "\n";
    myfile << theLibrary.books[theLibrary.numOfBooks].author << "\n";
    myfile << theLibrary.books[theLibrary.numOfBooks].ISBN << "\n";
    myfile << theLibrary.books[theLibrary.numOfBooks].genre << "\n";
    myfile.close();
    return theLibrary;
}


int display (int linesInBook, Library &myLibrary)
{
    ifstream myfile;
    myfile.open("Library.txt");

    for(int _book=0; _book<=linesInBook; _book++)
    {
        cout << endl;
        cout << myLibrary.books[_book].title << endl;
        cout << myLibrary.books[_book].author << endl;
        cout << myLibrary.books[_book].ISBN << endl;
        cout << myLibrary.books[_book].genre << endl << endl;
    }
    myfile.close();
}

int main()
{
    int linesInBook;

    Library myLibrary;
    Library theLibrary;
    myLibrary.numOfBooks=0;

    do{
    linesInBook = readFile(myLibrary);
    theLibrary = createRecord(myLibrary);
    display(linesInBook, myLibrary);
    }while(1==1);
    return 0;
}

