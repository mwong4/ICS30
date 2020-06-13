/*****************************************

Title: Library Summative
Date Last Modified: June 9, 2020
Description: Gives you the job of both the librarian and the customer.

*****************************************/
#include <iostream>//includes cout and cin
#include <string>//includes strings (always good habbit to use even if already combined with other default functions)
#include <fstream>//includes accessing external files
#include <windows.h>//includes system calls
using namespace std;

struct Book
{
    string title;
    string author;
    int pages;
    string availability;
    bool removeBook;
};

struct Library
{
    Book books[1000];
    int book_total;
};
int career_opt();//called when choosing between librarian and customer
int librarian_opt();//called when choosing options associated with the librarian
int costumer_opt();//called when choosing options associated with the customer
void add_book(Library&);//called when adding a book to the array
void remove_book(Library&, int);//called when removing a book to the array
int search_book(Library&, int);//called when searching for book
void librarian_subsearch(Library&, int);//called when choosing what to do for the librarian after book is found
void customer_subsearch(Library&, int);//called when choosing what to do for the customer after book is found
void display(Library, int);//displays a single book
void initalize_title(Library&, int);//initalize the title of a book
void initalize_author(Library&, int);//initializes the author of a book
void initalize_pages(Library&, int);//initializes the pages of a book
void initalize_availability(Library&, int);//inititalizes the availability of the book
void initalize_removeBook(Library&, int);//determines if the book is going to be viewable
void modify_book(Library&, int);//called when modifying book info
void view_content(Library);//displays every book
void rewrite_file(Library);

int main()
{
    int career, librarian_menu, customer_menu;
    Library myLibrary;
    myLibrary.book_total = 0;

    do
    {
        career = career_opt(); //determines their job

        if (career == 1)//librarian
        {
            librarian_menu = librarian_opt();//determines what they want to do

            if (librarian_menu == 1)//add a book
            {
                add_book(myLibrary);
                rewrite_file(myLibrary);
            }
            else if (librarian_menu == 2)//search for book
            {
                search_book(myLibrary, career);
            }
        }
        else if (career == 2)//customer
        {
            customer_menu = costumer_opt();//determines what they want to do

            if (customer_menu == 1)//search for book
            {
                search_book(myLibrary, career);
            }
            else if (customer_menu == 2)//view libraries content
            {
                system("CLS");
                view_content(myLibrary);
            }
            system("PAUSE");
        }
        system("CLS");
    }
    while(career != 3);

    return 0;
}

int career_opt()//called when choosing between librarian and customer
{
    int choice;
    do
    {
        cout << "What do you want to be (enter number): \n1. Librarian \n2. Customer \n3. Quit" << endl;
        cin >> choice;
        if (choice < 1 || choice > 3)
        {
            cout << "Invalid Response\n\n";
        }
    }
    while(choice < 1 || choice > 3);
    return choice;
}

int librarian_opt()//called when choosing options associated with the librarian
{
    int choice;
    do
    {
        cout << "\n\nWhat do you want to do: \n1. Add Book \n2. Seach for Book" << endl;
        cin >> choice;
        if (choice < 1 || choice > 2)
        {
            cout << "Invalid Response\n\n";
        }
    }
    while (choice < 1 || choice > 2);
    return choice;
}

int costumer_opt()//called when choosing options associated with the customer
{
    int choice;
    do
    {
        cout << "\n\nWhat do you want to do: \n1. Search for Book \n2. Examine Libraries Content" << endl;
        cin >> choice;
        if (choice < 1 || choice > 2)
        {
            cout << "Invalid Response\n\n";
        }
    }
    while (choice < 1 || choice > 2);
    return choice;
}

void add_book(Library& myLibrary)//called when adding a book to the array
{
    cout << "\n\n";
    initalize_title(myLibrary, myLibrary.book_total);
    initalize_author(myLibrary, myLibrary.book_total);
    initalize_pages(myLibrary, myLibrary.book_total);
    initalize_availability(myLibrary, myLibrary.book_total);
    initalize_removeBook(myLibrary, myLibrary.book_total);
    myLibrary.book_total++;
    cout << "\n\n";
    return;
}

void remove_book(Library& myLibrary, int i)//called when removing a book to the array
{
    myLibrary.books[i].removeBook = true;//if myLibrary.book[i].removeBook = true; then that book won't be viewed
    myLibrary.book_total--;
    return;
}

int search_book(Library& myLibrary, int career)//called when searching for book
{
    int choice, pages_;
    string title_, author_;

    do
    {
        cout << "\n\nWhich book detail do you want to search for: \n1.Title \n2.Author \n3.Pages" << endl;
        cin >> choice;

        if (choice == 1)//searching for book by the title
        {
            cout << "\nWhat is the title of the book?" << endl;
            cin.ignore();
            getline(cin, title_);
        }
        else if (choice == 2)//searching for book by the author
        {
            cout << "\nWho is the author of the book?" << endl;
            cin.ignore();
            getline(cin, author_);
        }
        else if (choice == 3)//searching for book by the number of pages
        {
            cout << "\nHow many pages does the book have?" << endl;
            cin >> pages_;
        }
        if (choice < 1 || choice > 3)
        {
            cout << "Invalid Response";
        }
    }
    while (choice < 1 || choice > 3);

    system("CLS");

    for(int i = 0; i < myLibrary.book_total; i++)
    {
        if (myLibrary.books[i].removeBook == false)//determines if book should be viewed
        {
            if (title_ == myLibrary.books[i].title)//searches for book by title
            {
                cout << "\n\nMatch!!!" << endl;
                display(myLibrary, i);//display the book

                if (career == 1)//determines if librarian or customer is playing because there are more sub-questions to ask
                {
                    librarian_subsearch(myLibrary, i);
                }
                else if (career == 2)
                {
                    customer_subsearch(myLibrary, i);
                }
                return i;
            }
            else if (author_ == myLibrary.books[i].author)//searched for book by author
            {
                cout << "\n\nMatch!!!" << endl;
                display(myLibrary, i);//display the book

                if (career == 1)//determines if librarian or customer is playing because there are more sub-questions to ask
                {
                    librarian_subsearch(myLibrary, i);
                }
                else if (career == 2)
                {
                    customer_subsearch(myLibrary, i);
                }
                return i;
            }
            else if (pages_ == myLibrary.books[i].pages)//searches for book by number of pages
            {
                cout << "\n\nMatch!!!" << endl;
                display(myLibrary, i);//display the book

                if (career == 1)//determines if librarian or customer is playing because there are more sub-questions to ask
                {
                    librarian_subsearch(myLibrary, i);
                }
                else if (career == 2)
                {
                    customer_subsearch(myLibrary, i);
                }
                return i;
            }
        }
    }
    cout << "Couldn't find match :(" << endl;
    return -1;//returns a number that is impossible for the number of books to be equal to
}

void librarian_subsearch(Library& myLibrary, int i)//called when choosing what to do for the librarian after book is found
{
    int choice;
    cout << "What do you want to with the book: " << endl;
    cout << "1. Remove Book \n2. Modify Book \n3. Quit" << endl;
    cin >> choice;

    if (choice == 1)//determines whether to remove or modify a book
    {
        remove_book(myLibrary, i);
    }
    else if (choice == 2)
    {
        modify_book(myLibrary, i);
    }
    return;
}

void customer_subsearch(Library& myLibrary, int i)//called when choosing what to do for the customer after book is found
{
    int choice;
    cout << "What do you want to do with the book: " << endl;

    if (myLibrary.books[i].availability == "Available")//if book is available then they have an option to borrow the book
    {
        cout << "1. Borrow Book \n2. Quit" << endl;
        cin >> choice;

        if (choice == 1)
        {
            myLibrary.books[i].availability = "Borrowed";
        }
    }
    else if (myLibrary.books[i].availability == "Borrowed")//if book is borrowed then they have an option to return the book
    {
        cout << "1. Return Book \n2. Quit" << endl;
        cin >> choice;

        if (choice == 1)
        {
            myLibrary.books[i].availability = "Available";
        }
    }
    return;
}

void display(Library myLibrary, int i)//displays a single book
{
    if (myLibrary.books[i].removeBook == false)
    {
        cout << "Title: " << myLibrary.books[i].title << endl;
        cout << "Author: " << myLibrary.books[i].author << endl;
        cout << "Pages: " << myLibrary.books[i].pages << endl;
        cout << "Availability Status: " << myLibrary.books[i].availability << endl;
        cout << "\n\n";
    }
    return;
}

void initalize_title(Library& myLibrary, int i)//initalize the title of a book
{
    cout << "What is the title of the book?" << endl;
    cin.ignore();//incase a cin statement was used right before this
    getline(cin, myLibrary.books[i].title);
    return;
}

void initalize_author(Library& myLibrary, int i)//initializes the author of a book
{
    cout << "Who is the author of the book?" << endl;
    getline(cin, myLibrary.books[i].author);
    return;
}

void initalize_pages(Library& myLibrary, int i)//initializes the pages of a book
{
    cout << "How many pages does the book have?" << endl;
    cin >> myLibrary.books[i].pages;
    return;
}

void initalize_availability(Library& myLibrary, int i)//inititalizes the availability of the book
{
    myLibrary.books[i].availability = "Available";//all books start out available
    return;
}

void initalize_removeBook(Library& myLibrary, int i)//determines if the book is going to be viewable
{
    myLibrary.books[i].removeBook = false;//all books start out not removed
    return;
}

void modify_book(Library& myLibrary, int i)//called when modifying book info
{
    int choice;

    if (i != -1)//if program found book that they were looking for
    {
        do
        {
            cout << "\n\n";
            cout << "Which book characteristic do you want to change: " << endl;
            cout << "1. Title \n2. Author \n3. Pages" << endl;
            cin >> choice;
            if (choice < 1 || choice > 3)
            {
                cout << "Invalid Response";
            }
        }
        while (choice < 1 || choice > 3);

        if (choice == 1)
        {
            initalize_title(myLibrary, i);
        }
        else if (choice == 2)
        {
            cin.ignore();//incase a cin statement was used right before this
            initalize_author(myLibrary, i);
        }
        else if (choice == 3)
        {
            initalize_pages(myLibrary, i);
        }
    }
    return;
}

void view_content(Library myLibrary)//displays every book
{
    for (int i = 0; i < myLibrary.book_total; i++)//loops until every book (which has a removeBook = false) has been displayed
    {
        display(myLibrary, i);
        cout << "\n\n";
    }
    return;
}

void rewrite_file(Library myLibrary)
{
    ofstream extFile;

    extFile.open("Library.txt", ios::trunc);
    if(extFile.is_open())
    {
        extFile << myLibrary.book_total << endl;
        for (int i = 0; i < myLibrary.book_total; i++)
        {
            extFile << myLibrary.books[i].title << endl;
            extFile << myLibrary.books[i].author << endl;
            extFile << myLibrary.books[i].pages << endl;
            extFile << myLibrary.books[i].availability << endl;
            extFile << myLibrary.books[i].removeBook << endl;
        }
        cout << "File opened" << endl;
        extFile.close();
    }
    else
    {
        cout << "File didn't open\n\n";
    }
    return;
}
