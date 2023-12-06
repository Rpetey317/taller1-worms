#include "../Headers/CreateGame.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info

#include <iostream>

#include <qcombobox.h>
#include <stdlib.h>

CreateGame::CreateGame() {
    // Instancio la configuracion generada por el designer y uic
    Ui::CreateGame greeter;
    // Configuro este widget para use esa configuracion
    greeter.setupUi(this);
    connectEvents();
}

QString CreateGame::getEnteredGameName() const {
    QLineEdit* inputName = findChild<QLineEdit*>("gameName");
    return inputName->text();
}


QString CreateGame::getEnteredMapName() const {
    QLineEdit* inputMap = findChild<QLineEdit*>("mapName");
    return inputMap->text();
}

void CreateGame::createNewGame() {
    QDialog::accept();
}

void CreateGame::connectEvents() {
    QPushButton* button_create_game = findChild<QPushButton*>("acceptButton");
    QObject::connect(button_create_game, &QPushButton::clicked, this, &CreateGame::createNewGame);
}
