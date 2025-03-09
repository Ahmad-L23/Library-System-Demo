#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

class clsString
{
    
public:
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

};