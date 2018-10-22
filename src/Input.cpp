#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <typeinfo>

using namespace std;

////from week 6 codio exercises -- lab_adaptive.cpp 
template<typename T>
T input(bool clear=false)
{
    try 
    {
        string buffer;
        getline(cin, buffer);

        stringstream ss(buffer);
        T input;
        if (ss >> input && ss.eof())
            if(clear) 
            {
                system("clear");
            }
            return input;
        throw std::runtime_error("error, invalid type entered");
    } 
    catch (runtime_error &e )
    {
        if(typeid(T) == typeid(int)) { return -1; }
        else if(typeid(T) == typeid(char) || typeid(T) == typeid(string)) { return 'x'; }

    }
}
//------------------------------------------------------
//

