#include<iostream>
#include"clsAuthor.cpp"
#include"clsScreen.cpp"
using namespace std;

class clasDeletedAuthorScreen {

private:
    template<typename T>
    static T readData()
    {
        T data;
        if constexpr (std::is_same<T, std::string>::value)
        {
            getline(cin, data);
        }
        else
        {
            cin >> data;
            cin.ignore();
        }
        return data;
    }

    static void readBooks(vector<string>& books, int numberOfBooks)
    {
        for (int i = 1; i <= numberOfBooks; i++)
        {
            cout << "\nEnter book" << i << ": ";
            string book = readData<string>();
            books.push_back(book);
        }
    }


    static void printAuthorData(clsAuthor& Data)
    {
        cout << "\nAuthor Name        :" << Data.getName();
        cout << "\nAuthor Age         :" << Data.getAge();
        cout << "\nAuthor Nationality :" << Data.getNationality();
        cout << "\nAuthor Books       :";
        for (const auto& book : Data.getBooks())
            cout << "\n-" << book;
    }

public:
public:
    static void showDeleteAuthorScreen()
    {
      
        clsScreen::showScreen("DELETE AUTHOR SCREEN");
        string AuthorName;
        cout << "\n Enter Author Name: ";
        getline(cin, AuthorName);

        while (!clsAuthor::isAuthorExist(AuthorName))
        {
            cout << "\n [!] Author not found. Please enter a valid author name: ";
            getline(cin, AuthorName);
        }

        clsAuthor Author = clsAuthor::Find(AuthorName);

        clsScreen::showScreen("AUTHOR INFORMATION");
       
        printAuthorData(Author);
        cout << "\n==================================================================================\n";

        cout << "\nAre you sure you want to delete this author? (y/n): ";
        char answer;
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            if (Author.Delete()) {
                clsScreen::showScreen("AUTHOR DELETED SUCCESSFULLY :-)");
            }
            else
            {
                cout << "\n[!] Error: Author was not deleted.\n";
            }
        }
        
    }

};

