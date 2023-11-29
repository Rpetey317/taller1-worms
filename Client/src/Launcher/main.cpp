#include <QApplication>
#include "Greeter.h"
#include <iostream>

int main(int argc, char *argv[]) {
    // Clase que contiene el loop principal
    QApplication app(argc, argv);
    // Instancio el greeter
    Greeter greeter;
    greeter.show();
    
    // QString gameName = greeter.gameName;
    // std::cout << "Game name to join or created: " << gameName.toStdString() << std::endl;
    // Arranca el loop de la UI
    return app.exec();
}
