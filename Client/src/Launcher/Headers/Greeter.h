#ifndef GREETER_H
#define GREETER_H

#include "JoinGame.h"
#include "CreateGame.h"
#include <QWidget>
// #include "../ui_super_duper_tuki.h"
#include "../ui_launcher.h"
#include <string>
#include "../DataLoggin/DataLoggin.h"
#include "../../ClientProtocol/ClientProtocol.h"

class Greeter : public QWidget {
    
private:
    // Ui::Greeter *ui;
    ClientProtocol &protocol;
    void connectEvents();
    // void updateNameRandom();
    void createGame();
    void joinToGame();
    void createMap();
    // ~Greeter();

public:
    explicit Greeter(QWidget *parent, ClientProtocol &protocol);
    // DataLoggin dataLoggin;
    QString gameName;
    int mapNumber;
};

#endif // GREETER_H
