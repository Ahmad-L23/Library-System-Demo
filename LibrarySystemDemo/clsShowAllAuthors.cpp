#include<iostream>
#include"clsAuthor.cpp"
#include"clsScreen.cpp"

using namespace std;

class clsShowAllAuthorsScreen {

private:
     
    
	static void printAuthorData(clsAuthor& author)
	{
        int bookCounter = 1;
       cout << author.getName() << " info: " << endl;

       cout << "\nAuthor Name        :" << author.getName();
       cout << "\nAuthor Age         :" << author.getAge();
       cout << "\nAuthor Nationality :" << author.getNationality();
       cout << "\nAuthor Books       :";
       for (const auto& book : author.getBooks())
       {
           cout << "\n " << bookCounter << "-" << book;
           bookCounter++;
       }
         cout <<"\n-------------------------------------------\n\n";
	}


public:
    static void showAllAuthorsScreen()
    {
        clsScreen::showScreen("show all authors screen");
        vector<clsAuthor> AuthorsData = clsAuthor::getAllAuthors();
        if (!AuthorsData.empty()) {
            for (clsAuthor& author : AuthorsData)
                printAuthorData(author);
        }
        else
        {
            cout << "\nThere are no authors to show" << endl;
        }
    }
};
