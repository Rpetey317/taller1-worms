#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QWidget>
#include <QDialog>
#include "../ui_crear_partida_nueva.h"

class CreateGame : public QDialog {
public:
    explicit CreateGame();
    QString getEnteredText() const;
    int getEnteredMap() const;

private slots:
    void createNewGame();

private:
    void connectEvents();
};

#endif // CREATEGAME_H
