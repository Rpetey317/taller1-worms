#ifndef DATALOGGIN_H
#define DATALOGGIN_H

#include <string>

class DataLoggin {

    public:
    std::string gameName;
    std::string playerName;
    DataLoggin();
    std::string getGameName();
    ~DataLoggin();


};

#endif  // DATALOGGIN_H
