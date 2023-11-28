#ifndef GREETER_H
#define GREETER_H

#include "CreateGame.h"
#include <QWidget>
#include "ui_super_duper_tuki.h"
class Greeter : public QWidget {
public:
    explicit Greeter(QWidget *parent = 0);
private:
    void updateGreetings();
    void connectEvents();
    void updateNameRandom();
    void createGame();
    void joinGame();
};

#endif // GREETER_H
