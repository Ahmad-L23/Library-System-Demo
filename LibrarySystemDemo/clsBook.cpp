#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsAuthor.cpp"
using namespace std;

class clsBook
{
private:
    string title;
    string category;
    string language;
    clsAuthor Author;
    int numberOfPages;

    static string bookObjectToLine(clsBook book, string separator = "#\\#")
    {
        string Line = "";
        Line += book.title + separator;
        Line += book.category + separator;
        Line += book.language + separator;
        Line += to_string(book.numberOfPages) + separator;
        Line += "(";
        Line += book.Author.getName() + ",";
        Line += to_string(book.Author.getAge()) + ",";
        Line += book.Author.getNationality();
        Line += ")";
        return Line;
    }

    static clsBook bookLineToObject(string Line, string separator = "#\\#")
    {
        vector<string> vBookData;
        int pos = 0;

        while ((pos = Line.find(separator)) != string::npos)
        {
            vBookData.push_back(Line.substr(0, pos));
            Line.erase(0, pos + separator.length());
        }

        string authorData = Line.substr(1, Line.length() - 2);
        vector<string> vAuthorData;
        pos = 0;

        while ((pos = authorData.find(',')) != string::npos)
        {
            vAuthorData.push_back(authorData.substr(0, pos));
            authorData.erase(0, pos + 1);
        }
        vAuthorData.push_back(authorData);

        if (vAuthorData.size() < 3)
        {
            throw runtime_error("Invalid author data format");
        }

        int numberOfPages = stoi(vBookData[3]);
        int authorAge = stoi(vAuthorData[1]);

        clsAuthor author(vAuthorData[0], authorAge, vAuthorData[2]);
        return clsBook(vBookData[0], vBookData[1], vBookData[2], numberOfPages, author);
    }

    static vector<clsBook> loadBooksFromFile()
    {
        vector<clsBook> books;
        fstream myFile;
        myFile.open("Books.txt", ios::in); // Open the file in read mode

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                try
                {
                    clsBook book = bookLineToObject(line); // Convert line to book object
                    books.push_back(book); // Add the book to the vector
                }
                catch (const runtime_error& e)
                {
                    cout << "Error parsing line: " << e.what() << endl;
                }
            }
            myFile.close();
        }
        else
        {
            cout << "Failed to open the file." << endl;
        }

        return books;
    }

public:
    clsBook() : Author(clsAuthor())
    {
        title = "";
        category = "";
        language = "";
        numberOfPages = 0;
    }

    clsBook(string title, string category, string language, int numberOfPages, clsAuthor author)
        : title(title), category(category), language(language), numberOfPages(numberOfPages), Author(author) {
    }

    static bool FindBook(string title)
    {
        vector<clsBook> books = loadBooksFromFile();
        for (const auto& book : books)
        {
            if (book.title == title)
            {
                return true;
            }
        }
        return false;
    }

    static void addNewBook(clsBook& book)
    {
        fstream myFile;
        myFile.open("Books.txt", ios::out | ios::app);

        if (myFile.is_open())
        {
            string Line = bookObjectToLine(book);
            myFile << Line << endl;
            myFile.close();
        }
    }
};
