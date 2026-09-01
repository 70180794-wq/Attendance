#include <iostream>
#include <string>
using namespace std;

// Base Class 1
class Book
{
protected:
    int bookID;
    string bookName;
    float bookPrice;

public:
    virtual void input()
    {
        cout << "Enter Book ID: ";
        cin >> bookID;
        cin.ignore();

        cout << "Enter Book Name: ";
        getline(cin, bookName);

        cout << "Enter Book Price: ";
        cin >> bookPrice;
        cin.ignore();
    }

    virtual void display()
    {
        cout << "Book ID: " << bookID << endl;
        cout << "Book Name: " << bookName << endl;
        cout << "Book Price: " << bookPrice << endl;
    }

    virtual ~Book() {}
};

// Base Class 2
class Writer
{
protected:
    string writerName;
    string writerAddress;
    int number_of_books_written;

public:
    virtual void input()
    {
        cout << "Enter Writer Name: ";
        getline(cin, writerName);

        cout << "Enter Writer Address: ";
        getline(cin, writerAddress);

        cout << "Enter Number of Books Written: ";
        cin >> number_of_books_written;
        cin.ignore();
    }

    virtual void display()
    {
        cout << "Writer Name: " << writerName << endl;
        cout << "Writer Address: " << writerAddress << endl;
        cout << "Books Written: "
             << number_of_books_written << endl;
    }

    int getBooksWritten()
    {
        return number_of_books_written;
    }

    string getWriterName()
    {
        return writerName;
    }

    virtual ~Writer() {}
};

// Derived Class
class Scholar : public Book, public Writer
{
private:
    int scholarID;

public:
    void input() override
    {
        cout << "\nEnter Scholar ID: ";
        cin >> scholarID;
        cin.ignore();

        Book::input();
        Writer::input();
    }

    void display() override
    {
        cout << "\n===== Scholar Record =====\n";
        cout << "Scholar ID: " << scholarID << endl;

        Book::display();
        Writer::display();
    }

    static void compare(Scholar arr[], int size)
    {
        cout << "\n===== Comparison Report =====\n";

        for (int i = 0; i < size; i++)
        {
            cout << "\nAuthor: "
                 << arr[i].writerName << endl;

            if (arr[i].number_of_books_written > 3)
            {
                cout << "Congrats! You are a distinguished author."
                     << endl;
            }
            else
            {
                int n = 3 - arr[i].number_of_books_written;

                cout << "Keep going! You are short "
                     << n
                     << " number of books."
                     << endl;
            }
        }
    }
};

int main()
{
    const int SIZE = 5;

    Scholar scholars[SIZE];

    // Input
    for (int i = 0; i < SIZE; i++)
    {
        cout << "\n--- Scholar "
             << i + 1
             << " ---\n";

        // Late Binding
        Book *ptr = &scholars[i];
        ptr->input();
    }

    // Display
    for (int i = 0; i < SIZE; i++)
    {
        Book *ptr = &scholars[i];
        ptr->display();
    }

    // Static Function Call
    Scholar::compare(scholars, SIZE);

    return 0;
}