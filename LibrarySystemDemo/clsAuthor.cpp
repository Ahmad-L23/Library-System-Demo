#include<iostream>
#include <fstream>
#include<string>
#include<vector>
using namespace std;

class clsAuthor {
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode mode;
    string name;
    int age;
    string nationality;
    vector<string>books;

    bool MarkedFDeleted = false;



    static clsAuthor authorLineToObject(string line, string seperator = "#//#")
    {
        vector<string> vUserData;
        size_t pos = 0;

        while ((pos = line.find(seperator)) != string::npos) {
            vUserData.push_back(line.substr(0, pos));
            line.erase(0, pos + seperator.length());
        }
        vUserData.push_back(line);

        int authorAge = stoi(vUserData[1]);
        vector<string> booksList;
        string booksStr = vUserData[3];

        if (booksStr.front() == '(' && booksStr.back() == ')') {
            booksStr = booksStr.substr(1, booksStr.length() - 2);
        }

        size_t bookPos = 0;
        string bookDelimiter = ",";
        while ((bookPos = booksStr.find(bookDelimiter)) != string::npos) {
            booksList.push_back(booksStr.substr(0, bookPos));
            booksStr.erase(0, bookPos + bookDelimiter.length());
        }
        if (!booksStr.empty()) {
            booksList.push_back(booksStr);
        }

        return clsAuthor(enMode::UpdateMode, vUserData[0], authorAge, vUserData[2], booksList);
    }


    static vector<clsAuthor> loadAuthorsFromFile()
    {
        vector<clsAuthor> vAuthors;
        fstream myFile;
        myFile.open("Authors.txt", ios::in);

        if (myFile.is_open())
        {
            string line;
            while (getline(myFile, line))
            {
                
                clsAuthor author = authorLineToObject(line);
                
                    vAuthors.push_back(author); 
                
            }
            myFile.close();
        }
        

        return vAuthors;
    }

    
    static string authorObjectToLine(clsAuthor Author, string seperator = "#//#")
    {

        string authorRecord = "";
        authorRecord += Author.name+seperator;
        authorRecord += to_string(Author.age) + seperator;
        authorRecord += Author.nationality + seperator;

        string strBook = "(";

        for (string& book : Author.getBooks())
            strBook += book + ",";

        if (!strBook.empty()) {
            strBook.pop_back();
            strBook += ")";
        }
        else
            strBook = "";
        authorRecord += strBook;

        return authorRecord;
    }

    static void addAuthorToFile(string line)
    {
        fstream myFile;
        myFile.open("Authors.txt", ios::out | ios::app);
        if (myFile.is_open())
        {
            myFile << line<<endl;
            myFile.close();
        }
    }
    void addNewAuthor()
    {
        addAuthorToFile(authorObjectToLine(*this));
    }

    static clsAuthor GetEmptyUserObject()
    {
        vector<string>vauhtor;
        return clsAuthor(enMode::EmptyMode, "", 0, "", vauhtor);
    }


    static void SaveAuthorsDataToFile(vector <clsAuthor> vAuthors)
    {

        fstream MyFile;
        MyFile.open("Authors.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsAuthor Author : vAuthors)
            {
                if (Author.MarkedFDeleted == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = authorObjectToLine(Author);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void update()
    {
        vector<clsAuthor>vAuthors;
        vAuthors = loadAuthorsFromFile();

        for (clsAuthor& Author : vAuthors)
        {
            if (Author.name == name)
            {
                Author = *this;
                break;
            }
        }
        SaveAuthorsDataToFile(vAuthors);
    }


public:

    clsAuthor() :mode(enMode::EmptyMode), name(""), age(0), nationality(""), books() {}

    clsAuthor(enMode mode,string name, int age, string nationality, vector<string>& books)
    {
        this->mode = mode;
        this->name = name;
        this->age = age;
        this->nationality = nationality;
        this->books = books;
    }

    clsAuthor(string name, int age, string nationality)
    {
        this->mode = enMode::AddNewMode;
        this->name = name;
        this->age = age;
        this->nationality = nationality;
    }
    void setName(string name)
    {
        this->name = name;
    }
    string getName()
    {
        return name;
    }
    void setAge(int age)
    {
        this->age = age;
    }
    int getAge()
    {
        return age;
    }

    void setNationality(string nationality)
    {
        this->nationality = nationality;
    }
    string getNationality()
    {
        return nationality;
    }
    void setBooks(const vector<string>& books)
    {
        this->books = books;
    }
    vector<string> getBooks() const
    {
        return books;
    }

     
    static clsAuthor getAddNewAuthorObject(string authorName)
    {
        vector<string>emptyBook;
        return clsAuthor(enMode::AddNewMode,authorName, 0, "", emptyBook);
    }
    
    bool isEmpty()
    {
        return(mode == enMode::EmptyMode);
    }
    static clsAuthor Find(string name)
    {
        fstream MyFile;
        MyFile.open("Authors.txt", ios::in); // read Mode
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsAuthor Author = authorLineToObject(Line);
                if (Author.getName() == name)
                {
                    MyFile.close();
                    return Author;
                }
            }
            MyFile.close();
        }
        return GetEmptyUserObject();
    }

    bool MarkedForDeleted() {
        return MarkedFDeleted;
    }

    static bool isAuthorExist(string name)
    {
        clsAuthor author = clsAuthor::Find(name);
        return (!author.isEmpty());
    }
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save() {
        switch ((mode)) {
        case enMode::EmptyMode:
            if (isEmpty()) {
                return enSaveResults::svFaildEmptyObject;
            }
        case enMode::UpdateMode:
             update();
            return enSaveResults::svSucceeded;
        case enMode::AddNewMode:
            if (clsAuthor::isAuthorExist(name)) {
                return enSaveResults::svFaildUserExists;
            }
            else {
                addNewAuthor();
                mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
    }


    bool Delete()
    {
        vector<clsAuthor>vAuthors;
        vAuthors = loadAuthorsFromFile();

        for (clsAuthor Author : vAuthors)
        {
            if (Author.name == name)
            {
                Author.MarkedFDeleted = true;
                break;
            }
        }
        SaveAuthorsDataToFile(vAuthors);
        *this = GetEmptyUserObject();
        return true;
    }

    static vector<clsAuthor>getAllAuthors()
    {
        return loadAuthorsFromFile();
    }
};
