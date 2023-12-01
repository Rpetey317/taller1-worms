#ifndef JOINGAME_H
#define JOINGAME_H

#include <QDialog>
#include <QWidget>

#include "../ui_unirse_a_partida.h"

class JoinGame: public QDialog {
public:
    explicit JoinGame();
    QString getEnteredText() const;

private slots:
    void JoinGameByName();

private:
    void connectEvents();
};

#endif  // JOINGAME_H
