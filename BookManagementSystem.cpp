
#include <iostream>
#include <string.h>
#include <iomanip>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <limits>
#define SIZE 50
using namespace std;

class Books
{
    char *title, *author, *publisher, *genre;
    int *stock, *isbn, *sold;
    float *price, *totalRating;
    int *numRatings;
    static int unsuccess;
    static int success;
    static vector<string> searchHistory;

public:
    template <typename T>
    static T getInput(const string &prompt)
    {
        T input;
        while (true)
        {
            cout << prompt;
            cin >> input;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Invalid input. Please try again.\n";
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return input;
            }
        }
    }
    Books();
    void addBook();
    void displayBook();
    void updateBook();
    int searchBook(int &);
    int searchBook(char[]);
    int searchBook(char[], int);
    void purchaseBook();
    static int getSuccess();
    static int getUnsuccess();
    void rateBook();
    static void addSearchHistory(const string &term);
    static void showSearchHistory();
    // Setter Methods
    void setISBN(int isbn);
    void setTitle(const string &title);
    void setAuthor(const string &author);
    void setPublisher(const string &publisher);
    void setGenre(const string &genre);
    void setPrice(float price);
    void setStock(int stock);
    void setTotalRating(float totalRating);
    void setNumRatings(int numRatings);
    // Getter Methods
    string getGenre() const;
    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    float getRating() const;
    int getStock() const;
    float getTotalRating() const;
    int getNumRatings() const;
    int getIsbn() const;
    int getSold() const;
    float getPrice() const;
    void decreaseStock(int count);
    void saveToFile(ofstream &);
    void loadFromFile(ifstream &);
    ~Books();
};

int Books::unsuccess;
int Books::success;
vector<string> Books::searchHistory;

Books::Books()
{
    title = new char[SIZE];
    author = new char[SIZE];
    publisher = new char[SIZE];
    genre = new char[SIZE];
    stock = new int;
    isbn = new int;
    price = new float;
    totalRating = new float;
    numRatings = new int;
    sold = new int;
    *totalRating = 0.0f;
    *numRatings = 0;
    *sold = 0;
}

void Books::addBook()
{
    cout << "Enter the book ISBN number (digits only): ";
    *isbn = getInput<int>("");

    cout << "Enter title of the book: ";
    cin.getline(title, SIZE);

    cout << "Enter author of the book: ";
    cin.getline(author, SIZE);

    cout << "Enter publisher of the book: ";
    cin.getline(publisher, SIZE);

    cout << "Enter genre of the book: ";
    cin.getline(genre, SIZE);

    cout << "Enter the price of the book: ";
    *price = getInput<float>("");

    cout << "Enter the stock available: ";
    *stock = getInput<int>("");
}

void Books::displayBook()
{
    static int i = 1;
    cout << left << setw(8) << i
         << setw(15) << *isbn
         << setw(25) << title
         << setw(20) << author
         << setw(20) << publisher
         << setw(15) << genre
         << setw(10) << fixed << setprecision(2) << *price
         << setw(8) << *stock
         << setw(8) << getRating()
         << endl;
    i++;
}

void Books::updateBook()
{
    cout << "\nEnter New details for ISBN: " << *isbn << endl;

    cout << "Title of Book: ";
    cin.getline(title, SIZE);

    cout << "Author of Book: ";
    cin.getline(author, SIZE);

    cout << "Publisher of Book: ";
    cin.getline(publisher, SIZE);

    cout << "Genre of Book: ";
    cin.getline(genre, SIZE);

    cout << "Enter the price of the book: ";
    *price = getInput<float>("");

    cout << "Enter the stock available: ";
    *stock = getInput<int>("");

    cout << "\nBook with ISBN " << *isbn << " has been updated successfully\n";
}

int Books::searchBook(int &isbno)
{
    return (isbno == *isbn) ? 1 : 0;
}

int Books::searchBook(char t[])
{
    return (strcmp(t, title) == 0) ? 1 : 0;
}

int Books::searchBook(char a[], int x)
{
    return (strcmp(a, author) == 0) ? 1 : 0;
}

void Books::purchaseBook()
{
    int count = getInput<int>("Enter Number Of Books to buy: ");

    if (count <= *stock)
    {
        success++;
        *stock -= count;
        *sold += count;
        cout << "\nBooks Bought Successfully\n";
        cout << "Details of the book are:\n"
             << "ISBN: " << *isbn << "\n"
             << "Title: " << title << "\n"
             << "Author: " << author << "\n"
             << "Price of 1 book: " << *price << "\n"
             << "Number of books bought: " << count << "\n"
             << "Total amount: " << (*price) * count << "\n";
    }
    else
    {
        cout << "\nRequired copies not in stock\n";
        unsuccess++;
    }
    cout << "Available stock: " << *stock << endl;
}

void Books::rateBook()
{
    float rating = getInput<float>("Enter your rating (0.0 to 5.0): ");
    while (rating < 0.0 || rating > 5.0)
    {
        cerr << "Invalid rating. Please enter a value between 0.0 and 5.0.\n";
        rating = getInput<float>("Enter your rating (0.0 to 5.0): ");
    }
    *totalRating += rating;
    (*numRatings)++;
    cout << "Thank you for your feedback!\n";
}

bool deleteBook(vector<Books *> &inventory)
{
    int isbno = Books::getInput<int>("Enter the ISBN of the book to delete: ");
    bool found = false;

    for (auto it = inventory.begin(); it != inventory.end(); ++it)
    {
        if ((*it)->searchBook(isbno))
        {
            delete *it;          // Free memory for the deleted book
            inventory.erase(it); // Remove the book from the inventory
            cout << "Book with ISBN " << isbno << " deleted successfully.\n";
            found = true;
            break;
        }
    }

    if (!found)
    {
        cerr << "The book with ISBN " << isbno << " was not found in the inventory.\n";
    }
    return found;
}

float Books::getRating() const
{
    if (*numRatings == 0)
        return 0.0f;
    return *totalRating / *numRatings;
}

void Books::addSearchHistory(const string &term)
{
    searchHistory.push_back(term);
}

void Books::showSearchHistory()
{
    cout << "\nSearch History:\n";
    for (const auto &term : searchHistory)
        cout << "- " << term << endl;
}

int Books::getSuccess()
{
    return success;
}

int Books::getUnsuccess()
{
    return unsuccess;
}

Books::~Books()
{
    delete[] title;
    delete[] author;
    delete[] publisher;
    delete[] genre;
    delete price;
    delete isbn;
    delete stock;
    delete totalRating;
    delete numRatings;
}

void Books::setISBN(int isbnValue)
{
    *isbn = isbnValue;
}

void Books::setTitle(const string &titleValue)
{
    strncpy(title, titleValue.c_str(), SIZE);
}

void Books::setAuthor(const string &authorValue)
{
    strncpy(author, authorValue.c_str(), SIZE);
}

void Books::setPublisher(const string &publisherValue)
{
    strncpy(publisher, publisherValue.c_str(), SIZE);
}

void Books::setGenre(const string &genreValue)
{
    strncpy(genre, genreValue.c_str(), SIZE);
}

void Books::setPrice(float priceValue)
{
    *price = priceValue;
}

void Books::setStock(int stockValue)
{
    *stock = stockValue;
}

void Books::setTotalRating(float totalRatingValue)
{
    *totalRating = totalRatingValue;
}

void Books::setNumRatings(int numRatingsValue)
{
    *numRatings = numRatingsValue;
}

string Books::getGenre() const
{
    return string(genre);
}

string Books::getTitle() const
{
    return string(title);
}
string Books::getAuthor() const
{
    return string(author);
}
string Books::getPublisher() const
{
    return string(publisher);
}

int Books::getStock() const
{
    return *stock;
}

int Books::getIsbn() const
{
    return *isbn;
}

int Books::getSold() const
{
    return *sold;
}
float Books::getTotalRating() const
{
    return *totalRating;
}
int Books::getNumRatings() const
{
    return *numRatings;
}

float Books::getPrice() const
{
    return *price;
}

void Books::decreaseStock(int count)
{
    *stock -= count;
}

void Books::saveToFile(ofstream &out)
{
    out << *isbn << '\n'
        << title << '\n'
        << author << '\n'
        << publisher << '\n'
        << *price << '\n'
        << *stock << '\n'
        << genre << '\n'
        << *totalRating << '\n'
        << *numRatings << '\n';
}

void Books::loadFromFile(ifstream &in)
{
    in >> *isbn;
    in.ignore();
    in.getline(title, SIZE);
    in.getline(author, SIZE);
    in.getline(publisher, SIZE);
    in >> *price >> *stock;
    in.ignore();
    in.getline(genre, SIZE);
    in >> *totalRating >> *numRatings;
}

void generateSalesReport(vector<Books *> &inventory)
{
    int totalSold = 0;
    float totalRevenue = 0.0;

    cout << "\n\t\t\tSALES REPORT\n";
    cout << "==========================================================================\n";
    cout << left << setw(10) << "ISBN"
         << setw(30) << "Title"
         << setw(10) << "Sold"
         << setw(15) << "Revenue"
         << endl;
    cout << "==========================================================================\n";

    for (auto &book : inventory)
    {
        int originalStock = 100; // Replace with your logic to store original stock
        float revenue = book->getSold() * (book->getPrice());

        totalSold += book->getSold();
        totalRevenue += revenue;

        cout << left << setw(10) << book->getIsbn()
             << setw(30) << book->getTitle()
             << setw(10) << book->getSold()
             << setw(15) << fixed << setprecision(2) << revenue
             << endl;
    }

    cout << "==========================================================================\n";
    cout << left << setw(40) << "Total:"
         << setw(10) << totalSold
         << setw(15) << fixed << setprecision(2) << totalRevenue
         << endl;
    cout << "==========================================================================\n";
}
void saveInventoryToFile(const vector<Books *> &inventory, const string &filename)
{
    ofstream outFile(filename, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open file for saving.\n";
        return;
    }

    for (const auto &book : inventory)
    {
        outFile << book->getIsbn() << '\n'
                << book->getTitle() << '\n'
                << book->getAuthor() << '\n'
                << book->getPublisher() << '\n'
                << book->getGenre() << '\n'
                << book->getPrice() << '\n'
                << book->getStock() << '\n'
                << book->getRating() << '\n'
                << book->getNumRatings() << '\n';
    }

    outFile.close();
    cout << "Inventory saved successfully to " << filename << ".\n";
}
void loadInventoryFromFile(vector<Books *> &inventory, int &bookCount, const string &filename)
{
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open file for loading.\n";
        return;
    }

    while (!inFile.eof())
    {
        Books *newBook = new Books();

        int isbn, stock, numRatings;
        float price, totalRating;
        string title, author, publisher, genre;

        inFile >> isbn;
        inFile.ignore();
        getline(inFile, title);
        getline(inFile, author);
        getline(inFile, publisher);
        getline(inFile, genre);
        inFile >> price >> stock >> totalRating >> numRatings;

        // cout << "Title: " << title << endl;
        // cout << "ISBN: " << isbn << endl;
        // cout << "Author: " << author << endl;
        // cout << "Publisher: " << publisher << endl;
        // cout << "Genre: " << genre << endl;
        // cout << "Price: $" << price << endl;
        // cout << "Stock: " << stock << endl;

        if (inFile)
        {
            newBook->setISBN(isbn);
            newBook->setTitle(title);
            newBook->setAuthor(author);
            newBook->setPublisher(publisher);
            newBook->setGenre(genre);
            newBook->setPrice(price);
            newBook->setStock(stock);
            newBook->setTotalRating(totalRating);
            newBook->setNumRatings(numRatings);
            // newBook->displayBook();
            inventory.push_back(newBook);
            bookCount++;
        }
        else
        {
            delete newBook; // Avoid memory leak
        }
    }

    inFile.close();
    cout << "Inventory loaded successfully from " << filename << ".\n";
}

int main()
{
    vector<Books *> inventory;
    int choice, isbno;
    string searchTerm;
    bool adminAuthenticated = false;
    int bookCount = 0, loopFlag = 1;
    char ch, t[SIZE], a[SIZE];
    bool found = false;

    while (true)
    {
        cout << "\nBook Shop\n";
        cout << "1. Add a Book\n";
        cout << "2. Display Book Inventory\n";
        cout << "3. Update a Book\n";
        cout << "4. Search a Book\n";
        cout << "5. Purchase a Book\n";
        cout << "6. Rate a Book\n";
        cout << "7. Display Successful and Unsuccessful Transactions\n";
        cout << "8. Delete a Book\n";
        cout << "9. Generate Sales Report\n";
        cout << "10. Show Search History\n";
        cout << "11. Save Inventory to File\n";
        cout << "12. Load Inventory from File\n";
        cout << "13. Exit\n";
        cout << "Enter your choice: ";
        choice = Books::getInput<int>("");

        switch (choice)
        {
        case 1:
            if (bookCount < SIZE)
            {
                Books *newBook = new Books();
                newBook->addBook();
                inventory.push_back(newBook);
                bookCount++;
            }
            else
                cerr << "No more books can be added.\n";

            break;
        case 2:
            cout << "\n\t\t\t\t\t\tBOOK INVENTORY\n";
            cout << "==================================================================================================================================\n";
            cout << left << setw(8) << "Sr.No"
                 << setw(15) << "ISBN"
                 << setw(25) << "Title"
                 << setw(20) << "Author"
                 << setw(20) << "Publisher"
                 << setw(15) << "Genre"
                 << setw(10) << "Price"
                 << setw(8) << "Stock"
                 << setw(8) << "Rating"
                 << endl;
            cout << "==================================================================================================================================\n";
            for (int j = 0; j < bookCount; j++)
                inventory[j]->displayBook();
            cout << "===================================================================================================================================\n";
            break;
        case 3:
            isbno = Books::getInput<int>("Enter the ISBN of the book to update: ");
            found = false;
            for (auto &book : inventory)
            {
                if (book->searchBook(isbno))
                {
                    book->updateBook();
                    found = true;
                    break;
                }
            }
            if (!found)
                cerr << "The book you want to update was not found.\n";
            break;
        case 4:
            while (loopFlag == 1)
            {
                cout << "\nBOOK SEARCH" << endl;
                cout << "a. Search by ISBN" << endl;
                cout << "b. Search by book title" << endl;
                cout << "c. Search by book author" << endl;
                cout << "d. Stop search" << endl;
                cout << "\nEnter your choice:- ";
                cin >> ch;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch (ch)
                {
                case 'a':
                case 'A':
                    found = false;
                    isbno = Books::getInput<int>("Enter the ISBN of the book to search: ");
                    for (auto &book : inventory)
                    {
                        if (book->searchBook(isbno))
                        {
                            book->displayBook();
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        cerr << "The book you want to search was not found\n";
                    break;
                case 'b':
                case 'B':
                    found = false;
                    cout << "Enter the title of the book to search: ";
                    cin.getline(t, SIZE);
                    for (auto &book : inventory)
                    {
                        if (book->searchBook(t))
                        {
                            book->displayBook();
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        cerr << "The book you want to search was not found\n";
                    break;
                case 'c':
                case 'C':
                    found = false;
                    cout << "Enter the author of the book to search: ";
                    cin.getline(a, SIZE);
                    for (auto &book : inventory)
                    {
                        if (book->searchBook(a, 0))
                        {
                            book->displayBook();
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        cerr << "The book you want to search was not found\n";
                    break;
                case 'd':
                case 'D':
                    loopFlag = 0;
                    break;
                default:
                    cerr << "Invalid choice. Try again.\n";
                    break;
                }
            }
            loopFlag = 1; // Reset for future searches
            break;
        case 5:
            isbno = Books().getInput<int>("Enter the ISBN of the book to purchase: ");
            found = false;
            for (auto &book : inventory)
            {
                if (book->searchBook(isbno))
                {
                    book->purchaseBook();
                    found = true;
                    break;
                }
            }
            if (!found)
                cerr << "The book you want to purchase was not found.\n";
            break;
        case 6:
            cout << "Enter the ISBN of the book to rate: ";
            isbno = Books().getInput<int>("");
            found = false;
            for (auto &book : inventory)
            {
                if (book->searchBook(isbno))
                {
                    book->rateBook();
                    found = true;
                    break;
                }
            }
            if (!found)
                cerr << "The book you want to rate was not found.\n";
            break;
        case 7:
            cout << "The number of successful transactions are: " << Books::getSuccess() << "\n";
            cout << "The number of unsuccessful transactions are: " << Books::getUnsuccess() << "\n";
            break;
        case 8:
            if (!adminAuthenticated)
            {
                string adminPassword;
                cout << "Enter admin password: ";
                cin >> adminPassword;
                if (adminPassword != "admin123")
                {
                    cerr << "Incorrect password. Access denied.\n";
                    break;
                }
                adminAuthenticated = true;
            }
            found = deleteBook(inventory);
            if (found)
                bookCount--;
            break;
        case 9:
            generateSalesReport(inventory); // Call the sales report function
            break;
        case 10:
            Books::showSearchHistory();
            break;
        case 11:
            saveInventoryToFile(inventory, "inventory.txt");
            break;
        case 12:
            loadInventoryFromFile(inventory, bookCount, "inventory.txt");
            break;
        case 13:
            for (auto &book : inventory)
                delete book; // Free memory
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default:
            cerr << "Invalid choice. Please try again.\n";
            break;
        }
    }
    return 0;
}