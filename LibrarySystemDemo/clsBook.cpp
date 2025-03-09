#include <iostream>
#include "clsAuthor.cpp"
using namespace std;

class clsBook
{
public:
    enum enStatus { Add, Update };
private:
    
    enStatus type;
    string title;
    string category;
    string language;
    clsAuthor Author;
    int numberOfPages;

    static string bookObjectToLine(clsBook book, string separator = "#//#")
    {
        string Line = "";
        Line += book.getTitle() + separator;
        Line += book.getCategory() + separator;
        Line += book.getLanguage() + separator;
        Line += to_string(book.getNumberOfPages()) + separator;

        // Only store author's name, age, and nationality
        Line += book.getAuthor().getName() + ",";
        Line += to_string(book.getAuthor().getAge()) + ",";
        Line += book.getAuthor().getNationality();

        return Line;
    }

    static clsBook bookLineToObject(string Line, string separator = "#//#")
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


        int numberOfPages = stoi(vBookData[3]);
        int authorAge = stoi(vAuthorData[1]);

        clsAuthor author(vAuthorData[0], authorAge, vAuthorData[2]);
        return clsBook(enStatus::Update, vBookData[0], vBookData[1], vBookData[2], numberOfPages, author);
    }

    static vector<clsBook> loadBooksFromFile()
    {
        vector<clsBook> books;
        fstream myFile;
        myFile.open("Books.txt", ios::in);

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                try
                {
                    clsBook book = bookLineToObject(line);
                    books.push_back(book);
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

    clsBook(enStatus type, string title, string category, string language, int numberOfPages, clsAuthor author)
        : type(type), title(title), category(category), language(language), numberOfPages(numberOfPages), Author(author) {
    }

    string getTitle() const { return title; }
    void setTitle(const string& newTitle) { title = newTitle; }

    string getCategory() const { return category; }
    void setCategory(const string& newCategory) { category = newCategory; }

    string getLanguage() const { return language; }
    void setLanguage(const string& newLanguage) { language = newLanguage; }

    int getNumberOfPages() const { return numberOfPages; }
    void setNumberOfPages(int newNumberOfPages) { numberOfPages = newNumberOfPages; }

    clsAuthor getAuthor() const { return Author; }
    void setAuthor(const clsAuthor& newAuthor) { Author = newAuthor; }

    static bool FindBook(const string& title)
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

    static enStatus addNewBook(clsBook& book)
    {
        fstream myFile;
        myFile.open("Books.txt", ios::out | ios::app);

        if (myFile.is_open())
        {
            string Line = bookObjectToLine(book);
            myFile << Line << endl;
            myFile.close();
        }
        return enStatus::Add;
    }
};
