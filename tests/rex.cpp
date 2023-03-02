#include <string>
#include <regex>
#include <iostream>

using namespace std;

auto main(int argc, char** argv) -> int 
{
    if (argc != 3) {
        cout << "Usage: rex string pattern" << endl;
        return -1;
    }

    cout << "String  : " << argv[1] << endl;
    cout << "Pattern : " << argv[2] << endl << endl;
    
    string str (argv[1]);
    regex str_expr (argv[2]);

    int counter = 0;
    const char *buffer = str.c_str();
    while (counter < str.length())
    {
        cmatch cm;

        while (buffer[counter] == ' ') counter++;

        regex_search (&buffer[counter], cm, str_expr);

        cout <<" The matches are: " << cm.size();
        for (unsigned i=0; i < cm.size(); ++i) {
            cout << " [" << cm[i] << "] ";
            counter += cm[i].length();
        }
    
        cout << endl;
    }
    
    return 0;
}