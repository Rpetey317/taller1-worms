#ifndef JOINGAME_H
#define JOINGAME_H

#include <QWidget>
#include <QDialog>
#include "ui_unirse_a_partida.h"

class JoinGame : public QDialog {
public:
    explicit JoinGame();
private:
    void JoinGameByName();
    void connectEvents();
};

#endif // JOINGAME_H
