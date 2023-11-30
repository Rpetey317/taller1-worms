#include "../Headers/CreateGame.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info

#include <iostream>
#include <stdlib.h>
#include <qcombobox.h>

CreateGame::CreateGame() {
    // Instancio la configuracion generada por el designer y uic
    Ui::CreateGame greeter;
    // Configuro este widget para use esa configuracion
    greeter.setupUi(this);
    connectEvents();
}

QString CreateGame::getEnteredText() const { 
    QLineEdit* inputName = findChild<QLineEdit*>("gameName");
    // QString name = inputName->text();
    // std::cout << "New game created: " << name.toStdString() << std::endl;
    return inputName->text();
}


int CreateGame::getEnteredMap() const { 
    QSpinBox* inputMap = findChild<QSpinBox*>("mapNumber");
    return inputMap->value();
}

void CreateGame::createNewGame() {
    // Deberia devolver el puerto para que se cree el cliente. No hace falta nombre de partida o si?
    QDialog::accept();
}

void CreateGame::connectEvents() {
    QPushButton* button_create_game = findChild<QPushButton*>("acceptButton");
    QObject::connect(button_create_game, &QPushButton::clicked,
                     this, &CreateGame::createNewGame);
}
