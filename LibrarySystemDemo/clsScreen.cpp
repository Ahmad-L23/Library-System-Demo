#include<iostream>
using namespace std;
class clsScreen {
public:
    static void showScreen(const string& screenTitle)
    {
        cout << "\n==================================================================================";
        cout << "\n                              " << screenTitle << "                               ";
        cout << "\n==================================================================================\n";
    }
};