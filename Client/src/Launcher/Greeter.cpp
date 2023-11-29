#include "Greeter.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info


#include <iostream>
#include <stdlib.h>
#include <QPixmap>
#include <QPalette>
Greeter::Greeter(QWidget *parent) : QWidget(parent) {
    // Instancio la configuracion generada por el designer y uic
    Ui::Greeter greeter;
    // Configuro este widget para use esa configuracion
    greeter.setupUi(this);
    QPixmap background_image("tuki.png");
    background_image = background_image.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background_image);
    this->setPalette(palette);
    connectEvents();
}

void Greeter::updateGreetings() {
    /**
     * findChild es un metodo de qObject que permite buscar un widget hijo
     * segun su nombre. Si observamos el codigo generado en ui_Greeter
     * cada uno de los objetos recibe un nombre mediante la funcion
     * setObjectName(QString nombre)
     **/
    QLineEdit* inputName = findChild<QLineEdit*>("changeName");
    QLabel* labelOut = findChild<QLabel*>("playerName");
    QString name = inputName->text();
    QString greetings = QString("Your name is: %1").arg(name);
    labelOut->setText(greetings);
}

void Greeter::updateNameRandom() {
    QLabel* labelOut = findChild<QLabel*>("playerName");

    QList<QString> names = {"gusanardo", "gusaman", "gusanito", "gusano bostero", "gusano gallina"};
    int randomIndex = rand() % names.size();

    QString name = names[randomIndex];
    QString greetings = QString("Your name is: %1").arg(name);

    labelOut->setText(greetings);
}

void Greeter::createGame() {
        CreateGame newGame;
        newGame.setModal(true);
        newGame.exec();
}

void Greeter::joinToGame() {
        JoinGame joinGame;
        joinGame.setModal(true);
        joinGame.exec();
}


void Greeter::connectEvents() {
    // Conecto el evento del boton
    QPushButton* button_select_name = findChild<QPushButton*>("selectNameButton");
    QObject::connect(button_select_name, &QPushButton::clicked,
                     this, &Greeter::updateGreetings);
    QPushButton *button_random_name = findChild<QPushButton*>("randomNameButton");
    QObject::connect(button_random_name, &QPushButton::clicked, this, &Greeter::updateNameRandom);

    QPushButton *button_create_game = findChild<QPushButton*>("createButton");
    QObject::connect(button_create_game, &QPushButton::clicked, this, &Greeter::createGame);

    QPushButton *button_join_game = findChild<QPushButton*>("joinButton");
    QObject::connect(button_join_game, &QPushButton::clicked, this, &Greeter::joinToGame);

}
