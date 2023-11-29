#include "JoinGame.h"

#include <iostream>
#include <stdlib.h>

JoinGame::JoinGame() {
    Ui::JoinGame greeter;
    greeter.setupUi(this);
    connectEvents();
}

void JoinGame::JoinGameByName() {
    QLineEdit* inputName = findChild<QLineEdit*>("gameName");
    QString name = inputName->text();
    std::cout << "Joined to game: " << name.toStdString() << std::endl;
}

void JoinGame::connectEvents() {
    QPushButton* button_join_game = findChild<QPushButton*>("acceptButton");
    QObject::connect(button_join_game, &QPushButton::clicked,
                     this, &JoinGame::JoinGameByName);
}
