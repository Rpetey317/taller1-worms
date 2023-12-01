#ifndef GREETER_H
#define GREETER_H

#include <QWidget>

#include "CreateGame.h"
#include "JoinGame.h"
// #include "../ui_super_duper_tuki.h"
#include <string>

#include "../../ClientProtocol/ClientProtocol.h"
#include "../DataLoggin/DataLoggin.h"
#include "../ui_launcher.h"

class Greeter: public QWidget {

private:
    // Ui::Greeter *ui;
    ClientProtocol& protocol;
    void connectEvents();
    // void updateNameRandom();
    void createGame();
    void joinToGame();
    void createMap();
    // ~Greeter();

public:
    explicit Greeter(QWidget* parent, ClientProtocol& protocol);
    // DataLoggin dataLoggin;
    QString gameName;
    QString mapName;
};

#endif  // GREETER_H
