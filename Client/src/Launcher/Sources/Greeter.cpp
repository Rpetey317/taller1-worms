#include "../Headers/Greeter.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info


#include <QPalette>
#include <QPixmap>
#include <iostream>

#include <stdlib.h>

Greeter::Greeter(QWidget* parent, ClientProtocol& protocol):
        QWidget(parent), protocol(protocol), gameName("") {
    // Instancio la configuracion generada por el designer y uic
    // Ui::Greeter greeter;
    Ui::Greeter greeter;
    // Configuro este widget para use esa configuracion
    greeter.setupUi(this);
    QPixmap background_image("../Images/Launcher/tuki.png");
    background_image = background_image.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background_image);
    this->setPalette(palette);
    connectEvents();
}

// void Greeter::updateNameRandom() {
//     QLabel* labelOut = findChild<QLabel*>("playerName");

//     QList<QString> names = {"gusanardo", "gusaman", "gusanito", "gusano bostero", "gusano
//     gallina"}; int randomIndex = rand() % names.size();

//     QString name = names[randomIndex];
//     QString greetings = QString("Your name is: %1").arg(name);

//     labelOut->setText(greetings);
// }

void Greeter::createGame() {
    CreateGame newGame;
    newGame.setModal(true);
    if (newGame.exec() == QDialog::Accepted) {
        this->gameName = newGame.getEnteredGameName();
        this->mapName = newGame.getEnteredMapName();
        // this->dataLoggin.gameName = this->gameName.toStdString();
        // std::cout << "Game created succesfully with name: " << gameName.toStdString()
        //           << " and map name: " << mapName.toStdString() << std::endl;

        std::string gameNameString(this->gameName.toStdString());
        std::string mapNameString(this->mapName.toStdString());

        this->protocol.create_new_game(gameNameString, mapNameString);

        //Crear otro QDialog que espere a un accept
        StartGame startGame;
        startGame.setModal(true);
        if (startGame.exec() == QDialog::Accepted) {
            std::cout << "Game started succesfully with name: " << gameName.toStdString()
                      << " and map name: " << mapName.toStdString() << std::endl;
            close();
        }

    };
}

void Greeter::joinToGame() {
    JoinGame joinGame;
    joinGame.setModal(true);
    if (joinGame.exec() == QDialog::Accepted) {
        this->gameName = joinGame.getEnteredText();
        // this->dataLoggin.gameName = this->gameName.toStdString();
        std::cout << "Joined succesfully to game: " << gameName.toStdString() << std::endl;
        close();
    };
}


void Greeter::createMap() {
    CreateMap createMap;
    createMap.setModal(true);
    if (createMap.exec() == QDialog::Accepted) {
        std::cout << "Map created succesfully with name: " << std::endl;
    };
}

void Greeter::connectEvents() {
    // Conecto el evento del boton

    QPushButton* button_create_game = findChild<QPushButton*>("createButton");
    QObject::connect(button_create_game, &QPushButton::clicked, this, &Greeter::createGame);

    QPushButton* button_join_game = findChild<QPushButton*>("joinButton");
    QObject::connect(button_join_game, &QPushButton::clicked, this, &Greeter::joinToGame);

    QPushButton* button_create_map = findChild<QPushButton*>("createMapButton");
    QObject::connect(button_create_map, &QPushButton::clicked, this, &Greeter::createMap);
}
