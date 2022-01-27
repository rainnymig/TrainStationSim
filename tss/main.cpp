#include "INIReader.h"

#include "station.h"
#include "passengerManager.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <memory>

using namespace tss;

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

        Station station;
        station.trainManager.loadSchedule("default_schedule.json");
        //  todo: create layout

        PassengerManager passengerManager;
        passengerManager.addPassengerSpawners(station.trainManager.getSpawnersFromTrain());

        while (station.clock.getTime() < 1440) 
        {
            station.clock.tick();
            for (auto t = station.clock.getLastTime() + 1; t <= station.clock.getTime(); t++)
            {
                passengerManager.update(station);
            }
        }
    }

}
