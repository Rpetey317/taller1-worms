#ifndef DATALOGGIN_H
#define DATALOGGIN_H

#include <string>

class DataLoggin {

    public:
    std::string gameName;
    int mapNumber;
    DataLoggin();
    std::string getGameName();
    ~DataLoggin();


};

#endif  // DATALOGGIN_H
