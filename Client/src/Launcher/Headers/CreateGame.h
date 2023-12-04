#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QDialog>
#include <QWidget>

#include "../ui_crear_partida_nueva.h"

class CreateGame: public QDialog {
public:
    CreateGame();
    QString getEnteredGameName() const;
    QString getEnteredMapName() const;

private slots:
    void createNewGame();

private:
    void connectEvents();
};

#endif  // CREATEGAME_H
