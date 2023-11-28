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


// void Greeter::connectEvents() {
//     // Conecto el evento del boton
//     QPushButton* button_select_name = findChild<QPushButton*>("selectNameButton");
//     QObject::connect(button_select_name, &QPushButton::clicked,
//                      this, &Greeter::updateGreetings);
//     QPushButton *button_random_name = findChild<QPushButton*>("randomNameButton");
//     QObject::connect(button_random_name, &QPushButton::clicked, this, &Greeter::updateNameRandom);

//     QPushButton *button_create_game = findChild<QPushButton*>("createButton");
//     QObject::connect(button_create_game, &QPushButton::clicked, this, &Greeter::createGame);

//     QPushButton *button_join_game = findChild<QPushButton*>("joinButton");
//     QObject::connect(button_join_game, &QPushButton::clicked, this, &Greeter::joinGame);

// }