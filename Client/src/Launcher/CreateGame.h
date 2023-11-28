#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QWidget>
#include <QDialog>
#include "ui_crear_partida_nueva.h"

class CreateGame : public QDialog {
public:
    explicit CreateGame();
private:
    void connectEvents();
};

#endif // CREATEGAME_H
