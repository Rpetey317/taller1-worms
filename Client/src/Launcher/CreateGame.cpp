#include "CreateGame.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info

#include <iostream>
#include <stdlib.h>
CreateGame::CreateGame() {
    // Instancio la configuracion generada por el designer y uic
    Ui::CreateGame greeter;
    // Configuro este widget para use esa configuracion
    greeter.setupUi(this);
    connectEvents();
}

void CreateGame::createNewGame() {
    QLineEdit* inputName = findChild<QLineEdit*>("gameName");
    QLineEdit* inputPort = findChild<QLineEdit*>("portNumber");
    QString name = inputName->text();
    QString port = inputPort->text();
    std::cout << "Create new game: " << name.toStdString() << " " << port.toStdString() << std::endl;
    // Deberia devolver el puerto para que se cree el cliente. No hace falta nombre de partida o si?
}

void CreateGame::connectEvents() {
    QPushButton* button_create_game = findChild<QPushButton*>("acceptButton");
    QObject::connect(button_create_game, &QPushButton::clicked,
                     this, &CreateGame::createNewGame);
}
