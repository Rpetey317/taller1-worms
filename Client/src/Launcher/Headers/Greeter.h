#ifndef GREETER_H
#define GREETER_H

#include "JoinGame.h"
#include "CreateGame.h"
#include <QWidget>
#include "../ui_super_duper_tuki.h"
#include <string>
#include "../DataLoggin/DataLoggin.h"
#include "../../ClientProtocol/ClientProtocol.h"

class Greeter : public QWidget {
    
private:
    // Ui::Greeter *ui;
    // ClientProtocol &protocol;
    void updateGreetings();
    void connectEvents();
    void updateNameRandom();
    void createGame();
    void joinToGame();
    // ~Greeter();

public:
    explicit Greeter(QWidget *parent = 0);
    // DataLoggin dataLoggin;
    QString gameName;
};

#endif // GREETER_H
