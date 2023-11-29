#include <QApplication>
#include "Greeter.h"
#include <iostream>

int main(int argc, char *argv[]) {
    // Clase que contiene el loop principal
    QApplication app(argc, argv);
    // Instancio el greeter
    Greeter greeter;
    greeter.show();
    // std::string gameName = greeter.gameName;
    // std::cout << "Game name to join or created: " << gameName << std::endl;
    // Arranca el loop de la UI
    return app.exec();
}
