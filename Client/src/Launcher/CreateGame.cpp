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

void CreateGame::connectEvents() {

}