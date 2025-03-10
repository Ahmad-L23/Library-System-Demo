#include <iostream>
#include "clsBook.cpp"
#include "clsString.cpp"

using namespace std;

class clsAddNewBookScreen {
private:
    static void readBookData(clsBook& book)
    {
        cout << "\nEnter Book Category: ";
        book.setCategory(clsString::readData<string>());

        cout << "\nEnter Book Language: ";
        book.setLanguage(clsString::readData<string>());

        cout << "\nEnter Number of Pages: ";
        book.setNumberOfPages(clsString::readData<int>());
    }

    static void printBookData(const clsBook& book)
    {
        cout << "\n========= BOOK DETAILS =========";
        cout << "\nTitle         : " << book.getTitle();
        cout << "\nCategory      : " << book.getCategory();
        cout << "\nLanguage      : " << book.getLanguage();
        cout << "\nPages         : " << book.getNumberOfPages();
        cout << "\nAuthor        : " << book.getAuthor().getName() << " ("
            << book.getAuthor().getAge() << ", " << book.getAuthor().getNationality() << ")";
    }

public:
    static void showAddNewBookScreen()
    {
        cout << "\n========= ADD NEW BOOK =========\n";

        string bookTitle;
        cout << "\nEnter Book Title: ";
        bookTitle = clsString::readData<string>();

        while (clsBook::isBookExist(bookTitle))
        {
            cout << "\n[!] Book title already exists. Please enter a different title: ";
            bookTitle = clsString::readData<string>();
        }

        string authorName;
        cout << "\nEnter Author Name: ";
        authorName = clsString::readData<string>();

        clsAuthor author = clsAuthor::Find(authorName);

        if (author.isEmpty())
        {
            int age;
            cout << "\nEnter Author Age: ";
            age = clsString::readData<int>();

            string nationality;
            cout << "\nEnter Author Nationality: ";
            nationality = clsString::readData<string>();

            clsAuthor newAuthor(authorName, age, nationality);

            author = newAuthor;
        }

        clsBook newBook(clsBook::enStatus::Add, bookTitle, "", "", 0, author);

        readBookData(newBook);

        vector<string> updatedBooks = author.getBooks();
        updatedBooks.push_back(bookTitle);
        author.setBooks(updatedBooks);

        author.Save();

        clsBook::enStatus saveResult = clsBook::addNewBook(newBook);

        cout << "\n========= BOOK INFORMATION =========\n";
        if (saveResult == clsBook::enStatus::Add)
        {
            cout << "\nBook added successfully!";
            printBookData(newBook);
        }
        else
        {
            cout << "\n[!] Error: Book could not be saved.\n";
        }
    }
};
