#include <iostream>
#include "clsBook.cpp"
#include "clsString.cpp"

using namespace std;

class clsDeleteBookScreen {
private:
    static void printBookData(const clsBook& book)
    {
        cout << "\n========= BOOK DETAILS =========";
        cout << "\nTitle         : " << book.getTitle();
        cout << "\nCategory      : " << book.getCategory();
        cout << "\nLanguage      : " << book.getLanguage();
        cout << "\nPages         : " << book.getNumberOfPages();
        cout << "\nAuthor        : " << book.getAuthor().getName() << " ("
            << book.getAuthor().getAge() << ", " << book.getAuthor().getNationality() << ")";
        cout << "\n=======================================\n";
    }

public:
    static void showDeleteBookScreen()
    {
        cout << "\n========= DELETE BOOK =========\n";

        string bookTitle;
        cout << "\nEnter Book Title: ";
        bookTitle = clsString::readData<string>();

        while (!clsBook::isBookExist(bookTitle))
        {
            cout << "\n[!] Book not found, Please enter a valid book title: ";
            bookTitle = clsString::readData<string>();
        }

        clsBook book = clsBook::FindBook(bookTitle);

        cout << "\n========= CURRENT BOOK DETAILS =========\n";
        printBookData(book);

        cout << "\nAre you sure you want to delete this book? (y/n): ";
        char choice;
        cin >> choice;

        if (tolower(choice) != 'y')
        {
            cout << "\nDeletion canceled.\n";
            return;
        }

        book.Delete();
        cout << "\nBook deleted successfully!\n";

        // Remove book from author's list
        clsAuthor author = book.getAuthor();
        vector<string> updatedBooks;

        for (const string& title : author.getBooks())
        {
            if (title != bookTitle)
            {
                updatedBooks.push_back(title);
            }
        }
        author.setBooks(updatedBooks);

        // If author has no more books, delete the author
        if (updatedBooks.empty())
        {
            author.Delete();
            cout << "\nAuthor " << author.getName() << " has been removed as they had no remaining books.\n";
        }
        else
        {
            author.Save();
        }
    }
};
