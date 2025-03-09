#include <iostream>
#include <vector>
#include "clsAuthor.cpp"
#include "clsScreen.cpp"
#include "clsString.cpp"  

using namespace std;

class clasAddNewAuthorScreen {
private:
    static void readBooks(vector<string>& books, int numberOfBooks)
    {
        for (int i = 1; i <= numberOfBooks; i++)
        {
            cout << "\nEnter book " << i << ": ";
            string book = clsString::readData<string>();  // Use clsString::readData
            books.push_back(book);
        }
    }

    static void readAuthorInfo(clsAuthor& Author)
    {
        cout << "\nEnter Author Age: ";
        Author.setAge(clsString::readData<int>());  // Use clsString::readData
        cout << "\nEnter Author Nationality: ";
        Author.setNationality(clsString::readData<string>());  // Use clsString::readData
        cout << "\nEnter Number of Books you want to add: ";
        int numberOfBooks = clsString::readData<int>();  // Use clsString::readData
        vector<string> books;
        readBooks(books, numberOfBooks);
        if (!books.empty())
            Author.setBooks(books);
    }

    static void printAuthorData(clsAuthor& Data)
    {
        cout << "\nAuthor Name        : " << Data.getName();
        cout << "\nAuthor Age         : " << Data.getAge();
        cout << "\nAuthor Nationality : " << Data.getNationality();
        cout << "\nAuthor Books       :";
        for (const auto& book : Data.getBooks())
            cout << "\n- " << book;
    }

public:
    static void showAddNewAuthorScreen()
    {
        clsScreen::showScreen(" ADD NEW AUTHOR SCREEN ");
        string AuthorName;
        cout << "\n Enter Author Name: ";
        AuthorName = clsString::readData<string>();  // Use clsString::readData

        while (clsAuthor::isAuthorExist(AuthorName))
        {
            cout << "\n [!] Author name is already in use. Please choose another: ";
            AuthorName = clsString::readData<string>();  // Use clsString::readData
        }

        clsAuthor newAuthor = clsAuthor::getAddNewAuthorObject(AuthorName);
        readAuthorInfo(newAuthor);

        clsAuthor::enSaveResults saveResult = newAuthor.Save();

        clsScreen::showScreen(" AUTHOR INFORMATION ");
        switch (saveResult)
        {
        case clsAuthor::enSaveResults::svSucceeded:
            cout << "\nAuthor added successfully!";
            printAuthorData(newAuthor);
            cout << "\n==================================================================================\n";
            break;

        case clsAuthor::enSaveResults::svFaildEmptyObject:
            cout << "\n[!] Error: Author was not saved because the data is empty.\n";
            break;

        case clsAuthor::enSaveResults::svFaildUserExists:
            cout << "\n[!] Error: Author was not saved because the name is already used!\n";
            break;
        }
    }
};
