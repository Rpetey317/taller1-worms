#ifndef GREETER_H
#define GREETER_H

#include <QWidget>

#include "CreateGame.h"
#include "JoinGame.h"
#include "StartGame.h"
// #include "../ui_super_duper_tuki.h"
#include <string>

#include "../../ClientProtocol/ClientProtocol.h"
#include "../ui_launcher.h"

#include "JoinGame.h"

class Greeter: public QWidget {

private:
    // Ui::Greeter *ui;
    ClientProtocol& protocol;
    void connectEvents();
    // void updateNameRandom();
    void createGame();
    void joinToGame();
    // ~Greeter();

public:
    explicit Greeter(QWidget* parent, ClientProtocol& protocol);
    // DataLoggin dataLoggin;
    QString gameName;
    QString mapName;
};

#endif  // GREETER_H
