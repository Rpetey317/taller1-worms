#ifndef STARTGAME_H
#define STARTGAME_H

#include <QDialog>
#include <QWidget>

#include "../ui_start_game.h"

class StartGame: public QDialog {
public:
    explicit StartGame();

private slots:
    void StartNewGame();

private:
    void connectEvents();
};

#endif  // STARTGAME_H
