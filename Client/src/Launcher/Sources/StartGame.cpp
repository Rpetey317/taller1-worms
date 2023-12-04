#include "../Headers/StartGame.h"

#include <iostream>

#include <stdlib.h>

StartGame::StartGame() {
    Ui::StartGame greeter;
    greeter.setupUi(this);
    connectEvents();
}

void StartGame::StartNewGame() { QDialog::accept(); }

void StartGame::connectEvents() {
    QPushButton* button_join_game = findChild<QPushButton*>("startGameButton");
    QObject::connect(button_join_game, &QPushButton::clicked, this, &StartGame::StartNewGame);
}
