#include "../Headers/JoinGame.h"

#include <iostream>

#include <stdlib.h>

JoinGame::JoinGame() {
    Ui::JoinGame greeter;
    greeter.setupUi(this);
    connectEvents();
}

QString JoinGame::getEnteredText() const {
    QLineEdit* inputName = findChild<QLineEdit*>("gameName");
    // QString name = inputName->text();
    // std::cout << "New game created: " << name.toStdString() << std::endl;
    return inputName->text();
}

void JoinGame::JoinGameByName() { QDialog::accept(); }

void JoinGame::connectEvents() {
    QPushButton* button_join_game = findChild<QPushButton*>("acceptButton");
    QObject::connect(button_join_game, &QPushButton::clicked, this, &JoinGame::JoinGameByName);
}
