#include <iostream>
#include "clsBook.cpp"
#include "clsString.cpp"

using namespace std;

class clsUpdateBookScreen {
private:
    static void readBookData(clsBook& book)
    {
        cout << "\nEnter new Book Category (Leave empty to keep current: " << book.getCategory() << "): ";
        string category = clsString::readData<string>();
        if (!category.empty()) book.setCategory(category);

        cout << "\nEnter new Book Language (Leave empty to keep current: " << book.getLanguage() << "): ";
        string language = clsString::readData<string>();
        if (!language.empty()) book.setLanguage(language);

        cout << "\nEnter new Number of Pages (Leave 0 to keep current: " << book.getNumberOfPages() << "): ";
        int pages = clsString::readData<int>();
        if (pages > 0) book.setNumberOfPages(pages);
    }

    static void printBookData(const clsBook& book)
    {
        cout << "\n========= UPDATED BOOK DETAILS =========";
        cout << "\nTitle         : " << book.getTitle();
        cout << "\nCategory      : " << book.getCategory();
        cout << "\nLanguage      : " << book.getLanguage();
        cout << "\nPages         : " << book.getNumberOfPages();
        cout << "\nAuthor        : " << book.getAuthor().getName() << " ("
            << book.getAuthor().getAge() << ", " << book.getAuthor().getNationality() << ")";
        cout << "\n=======================================\n";
    }

public:
    static void showUpdateBookScreen()
    {
        cout << "\n========= UPDATE BOOK =========\n";

        string bookTitle;
        cout << "\nEnter Book Title: ";
        bookTitle = clsString::readData<string>();

        while (!clsBook::isBookExist(bookTitle))
        {
            cout << "\n[!] Book not found, Please enter a valid book name: ";
            bookTitle = clsString::readData<string>();
        }

        clsBook book = clsBook::FindBook(bookTitle);

        cout << "\n========= CURRENT BOOK DETAILS =========\n";
        printBookData(book);

        cout << "\nDo you want to update this book? (y/n): ";
        char choice;
        cin >> choice;
        if (tolower(choice) != 'y')
        {
            cout << "\nUpdate canceled.\n";
            return;
        }

        cin.ignore();
        readBookData(book);

        book.updateBook();

        cout << "\nBook updated successfully!";
        printBookData(book);
    }
};
