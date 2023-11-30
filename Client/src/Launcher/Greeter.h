#ifndef GREETER_H
#define GREETER_H

#include "JoinGame.h"
#include "CreateGame.h"
#include <QWidget>
#include "ui_super_duper_tuki.h"
#include <string>
#include "DataLoggin/DataLoggin.h"

class Greeter : public QWidget {
public:
    explicit Greeter(QWidget *parent = 0);
    // DataLoggin dataLoggin;
    QString gameName;
    
private:
    // Ui::Greeter *ui;
    void updateGreetings();
    void connectEvents();
    void updateNameRandom();
    void createGame();
    void joinToGame();

    // ~Greeter();
};

#endif // GREETER_H
