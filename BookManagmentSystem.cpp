#include <iostream>
#include <string.h>
#include <iomanip>
#include <stdexcept>
#define SIZE 50
using namespace std;

class Book
{
private:
    string title;
    string author;
    int stock;
    float price;
    int ISBN;
    string publisher;
    static int success;
    static int unsuccess;

public:
    Book();
    void addBook();
    void displayBook();
    void updateBook();
    // searchBook method overloading
    int searchBook(int);
    int searchBook(string);
    int searchBook(string, int);
    void purchaseBook();
    int getSuccess();
    int getUnsuccess();
    void displayBookInfo();
    ~Book();
};
Book ::Book() {
    // cout << "this is book constructor" << endl;
};
int Book::unsuccess;
int Book::success;
void Book ::addBook()
{
    try
    {
        cout << "enter the book ISBN number" << endl;
        cin >> ISBN;
        cin.ignore();
        cout << "enter title of the book" << endl;
        getline(cin, title);
        cout << "enter the author of the book" << endl;
        getline(cin, author);
        cout << "enter the publisher of the book" << endl;
        getline(cin, publisher);
        cout << "enter the price of the book" << endl;
        cin >> price;
        cout << "enter the stock of the book" << endl;
        cin >> stock;
    }
    catch (const exception &e)
    {
        cout << "exception" << e.what() << endl;
    }
};
void Book ::displayBook()
{
    static int i = 1;
    cout << i << "\t" << ISBN << "\t\t" << title << "\t\t\t" << author << "\t\t\t" << publisher << "\t\t\t" << price << "\t\t" << stock << endl;
    i++;
};
void Book::updateBook()
{
    cout << "\nenter new details: " << endl;
    cout << "\nenter the book ISBN number" << endl;
    cin >> ISBN;
    cin.ignore();
    cout << "enter new title of the book" << endl;
    getline(cin, title);
    cout << "enter the new author of the book" << endl;
    getline(cin, author);
    cout << "enter the new publisher of the book" << endl;
    getline(cin, publisher);
    cout << "enter the new price of the book" << endl;
    cin >> price;
    cout << "enter the new stock of the book" << endl;
    cin >> stock;
};
int Book::searchBook(int isbno)
{
    if (ISBN == isbno)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
int Book::searchBook(string title1)
{
    if (title.compare(title1) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
int Book::searchBook(string author1, int x)
{
    if (author.compare(author1) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
void Book::purchaseBook()
{
    int count;
    cout << "\nenter number of books you want to buy" << endl;
    cin >> count;
    if (count <= stock)
    {
        success++;
        stock -= count;
        cout << "Book successfully bought" << endl;
        cout << "details of the books are: " << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Title: " << title << endl;
        cout << "author: " << author << endl;
        cout << "publisher: " << publisher << endl;
        cout << "price of 1 book:" << price << endl;
        cout << "number of books bought" << count << endl;
        cout << "total amount is: " << price * count << endl;
    }
    else
    {
        cout << "required copies not in stock" << endl;
        unsuccess++;
    }
    cout << "available stock is: " << stock << endl;
};
int Book::getSuccess()
{
    return success;
};
int Book::getUnsuccess()
{
    return unsuccess;
};
void Book::displayBookInfo()
{
    cout << "ISBN: " << ISBN << endl;
    cout << "Title: " << title << endl;
    cout << "author: " << author << endl;
    cout << "publisher: " << publisher << endl;
}
int main()
{
    Book *books[SIZE];
    int bookCounter = 0;
    for (int i = 0; i < SIZE; i++)
    {
        books[i] = new Book();
    }
    int choice;
    int searchFlag = 1;
    char searchChoice;
    while (1)
    {
        try
        {
            cout << "\nBook Shop" << endl;
            cout << "1. Add a Book" << endl;
            cout << "2. Display the Book Inventory" << endl;
            cout << "3. Update a Book" << endl;
            cout << "4. Search for a Book" << endl;
            cout << "5. Purchase a Book" << endl;
            cout << "6. Display Successful and Unsuccessful Transactions" << endl;
            cout << "7. Exit" << endl;
            cout << "\nEnter your choice" << endl;
            cin >> choice;
            int isbno;
            int flag = 1;
            switch (choice)
            {
            case 1:

                if (bookCounter < SIZE)
                {
                    try
                    {
                        books[bookCounter]->addBook();
                        bookCounter++;
                    }
                    catch (const exception &e)
                    {
                        cout << "exception" << e.what() << endl;
                        return 0;
                    }
                }
                else
                {
                    cout << "not more books can be added" << endl;
                }
                break;
            case 2:
                cout << "\t\t\t\t\t\tBOOK INVENTORY" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
                cout << "Sr.No\tISBN\t\tTitle\t\t\tAuthor\t\t\tPublisher\t\t\tPrice\t\tStock" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
                for (int j = 0; j < bookCounter; j++)
                {
                    books[j]->displayBook();
                }
                cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
                break;
            case 3:
                flag = 1;
                cout << "\tPlease enter book ISBN number" << endl;
                cin >> isbno;
                for (int j = 0; j < bookCounter; j++)
                {
                    if (books[j]->searchBook(isbno))
                    {
                        books[j]->updateBook();
                        flag = 0;
                        break;
                    }
                }
                if (flag)
                {
                    cout << "\nBook you want to update was not found" << endl;
                }
                break;
            case 4:

                while (searchFlag == 1)
                {
                    cout << "Book Search" << endl;
                    cout << "A. Search By ISBN" << endl;
                    cout << "B. Search By Book Title" << endl;
                    cout << "C. Search By Book Author" << endl;
                    cout << "D. Stop Search" << endl;
                    cout << "Enter Your Choice: ";
                    cin >> searchChoice;
                    switch (searchChoice)
                    {
                    case 'a':
                    case 'A':
                        cout << "Enter The ISBN Number of The Book to Search" << endl;
                        cin >> isbno;
                        flag = 1;
                        for (int j = 0; j < bookCounter; j++)
                        {
                            if (books[j]->searchBook(isbno))
                            {
                                flag = 0;
                                cout << "Search Successful Found the Book" << endl;
                                books[j]->displayBookInfo();
                                break;
                            }
                        }
                        if (flag == 1)
                        {
                            cout << "Book Not Found" << endl;
                        }
                        break;
                    case 'b':
                    case 'B':
                        char t[SIZE];
                        cout << "Enter The Title of The Book to Search" << endl;
                        cin.ignore();
                        cin.getline(t, SIZE);
                        flag = 1;
                        for (int j = 0; j < bookCounter; j++)
                        {
                            if (books[j]->searchBook(t))
                            {
                                flag = 0;
                                cout << "Search Successful Found the Book" << endl;
                                books[j]->displayBookInfo();
                                break;
                            }
                        }
                        if (flag == 1)
                        {
                            cout << "Book Not Found" << endl;
                        }
                        break;
                    case 'c':
                    case 'C':
                        char a[SIZE];
                        cout << "Enter The Author of The Book to Search" << endl;
                        cin.ignore();
                        cin.getline(a, SIZE);
                        flag = 1;
                        for (int j = 0; j < bookCounter; j++)
                        {
                            if (books[j]->searchBook(a))
                            {
                                flag = 0;
                                cout << "Search Successful Found the Book" << endl;
                                books[j]->displayBookInfo();
                                break;
                            }
                        }
                        if (flag == 1)
                        {
                            cout << "Book Not Found" << endl;
                        }
                        break;
                    case 'd':
                    case 'D':
                        searchFlag = 0;
                        break;
                    default:
                        cout << "Wrong Choice Try Again" << endl;
                        break;
                    }
                }
                break;
            case 5:
                flag = 1;
                cout << "please enter ISBN number of the book to purchase" << endl;
                cin >> isbno;
                for (int j = 0; j < bookCounter; j++)
                {
                    if (books[j]->searchBook(isbno))
                    {
                        books[j]->purchaseBook();
                        flag = 0;
                        break;
                    }
                }
                if (flag)
                {
                    cout << "\nthe book you want to purchase was not found" << endl;
                }

                break;
            case 6:
                cout << "\nthe number of successful transactions are: ";
                cout << books[1]->getSuccess() << endl;
                cout << "\nthe number of unsuccessful transactions are: ";
                cout << books[1]->getUnsuccess() << endl;
                break;
            case 7:
                return 0;
            }
        }
        catch (const exception &e)
        {
            cout << "exception" << e.what() << endl;
            return 0;
        }
    }
    return 0;
}