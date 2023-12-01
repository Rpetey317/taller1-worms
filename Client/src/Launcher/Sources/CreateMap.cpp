#include "../Headers/CreateMap.h"

#include <iostream>

#include <stdlib.h>

CreateMap::CreateMap() {
    Ui::CreateMap greeter;
    greeter.setupUi(this);
    connectEvents();
}

void CreateMap::CreateNewMap() { QDialog::accept(); }

void CreateMap::connectEvents() {
    QPushButton* button_join_game = findChild<QPushButton*>("pushButton");
    QObject::connect(button_join_game, &QPushButton::clicked, this, &CreateMap::CreateNewMap);
}
