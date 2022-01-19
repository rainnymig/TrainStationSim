#include "INIReader.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <memory>

int main()
{
    using std::cout;

    cout << "Hello world!" << '\n';

    {
        INIReader iniReader("default.ini");
        if (iniReader.ParseError() != 0)
        {
            cout << "ini parse error, bye" << '\n';
            return 1;
        }
    }

}
