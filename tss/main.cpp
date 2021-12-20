#include "INIReader.h"

#include "stage.h"
#include "train.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>
#include <map>
#include <cmath>

using namespace tss;

int main()
{
    using std::cout;
    using std::endl;

    cout << "Hello world!" << endl;

    {
        INIReader iniReader("default.ini");
        if (iniReader.ParseError() != 0)
        {
            cout << "ini parse error, bye" << endl;
            return 1;
        }
    }
    
    std::map<int, size_t> passengerDist;

    std::random_device r;
    std::mt19937 engine(r());
    std::normal_distribution<> normalDist(180, 8);
    for (size_t i = 0; i < 120; i++)
    {
        ++passengerDist[std::round(normalDist(engine))];
    }
    for (auto& p : passengerDist)
    {
        cout << p.first << ' ' << p.second << endl;
    }

    passengerDist.erase(passengerDist.begin());

    cout << passengerDist.begin()->first << endl;

    return 0;
}
