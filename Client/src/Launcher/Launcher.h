#ifndef LAUNCHER_H
#define LAUNCHER_H

// #include "CreateGame.h"
#include <QWidget>
// #include "ui_super_duper_tuki.h"
class Launcher : public QWidget {
public:
    explicit Launcher(QWidget *parent = 0);
private:
    void updateLauncher();
    void connectEvents();
    void updateNameRandom();
    void createGame();
};

#endif // LAUNCHER_H
