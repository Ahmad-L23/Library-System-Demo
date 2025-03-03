#include<iostream>
#include"clsAuthor.cpp"
using namespace std;

class clasUpdateAuthorScreen {

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

    static void readAuthorInfo(clsAuthor& Author)
    {
        cout << "\nEnter Author Age: ";
        Author.setAge(readData<int>());
        cout << "\nEnter Author Nationality: ";
        Author.setNationality(readData<string>());
        cout << "\nEnter Number of Books you want to add: ";
        int numberOfBooks = 0;
        vector<string> books;
        cin >> numberOfBooks;
        cin.ignore();
        readBooks(books, numberOfBooks);
        if (!books.empty())
            Author.setBooks(books);
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
    static void showUpdateAuthorScreen()
    {
        string AuthorName = "";
        cout << "\nEnter Author Name :" << endl;
        getline(cin, AuthorName);

        while (!clsAuthor::isAuthorExist(AuthorName))
        {
            cout << "\n Author is not found, choose another one: ";
            getline(cin, AuthorName);
        }

        clsAuthor newAuthor = clsAuthor::Find(AuthorName);
        printAuthorData(newAuthor);

        cout << "\n Are you sure you want to update this author y/n: ";
        char answer = 'n';
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            readAuthorInfo(newAuthor);

            clsAuthor::enSaveResults saveResult;
            saveResult = newAuthor.Save();

            switch (saveResult)
            {
            case clsAuthor::enSaveResults::svSucceeded:
                cout << "\nAuthor Updated Successfully :-)\n";
                printAuthorData(newAuthor);
                break;

            case clsAuthor::enSaveResults::svFaildEmptyObject:
                cout << "\nError: Author was not saved because it's Empty";
                break;
            }
        }
        }
       
};

