#include <QApplication>
#include <iostream>
#include <string>

#include <string.h>

#include "GameProcessing/GameProcessing.h"
#include "src/Launcher/Headers/Greeter.h"
#include "src/SdlManager/Editor.h"
#include "src/SdlManager/SdlManager.h"

int main(int argc, char* argv[]) {

    // Queue<int> commands;
    // Queue<std::vector<int>> positions;

    // SdlManager manager(commands, positions);

    // manager.run();


    // // Algo asi deberia ir:

    try {
        int ret = -1;

        if (argc == 2) {
            std::string map_name(argv[1]);
            MapEditor editor(map_name);
            editor.run();
            return 0;


            return ret;
        }

        if (argc != 3) {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
            return ret;
        }

        const char* hostname = argv[1];
        const char* port = argv[2];

        Socket skt(Socket(hostname, port));
        ClientProtocol protocol(std::move(skt));
        // Primero deberia crearse el Launcher, que es el que se encarga de crear la partida o
        // unirse a una
        QApplication app(argc, argv);
        // Instancio el greeter
        Greeter greeter(0, protocol);
        greeter.show();
        // QString gameName = greeter.gameName;
        // std::cout << "Game name to join or created: " << gameName.toStdString() << std::endl;
        // Arranca el loop de la UI
        app.exec();

        QString gameName = greeter.gameName;
        std::cout << "Game name to join or created: " << gameName.toStdString() << std::endl;

        Queue<std::shared_ptr<Action>> commands(10000);
        Queue<std::shared_ptr<Event>> events(10000);

        GameProcessing client(protocol, commands, events);

        client.run();

        SdlManager manager(commands, events, 1);
        manager.run("../Images/TerrainSprites/back1.png", "mapita.yaml");
        std::cout << "CERRANDO SDL" << std::endl;

        client.end();

        ret = 0;
        return ret;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }

    // Queue<Action> commands;
    // Queue<std::vector<int>> positions; // or std::map<int, std::vector<int>> positions; // Primer
    // int es el id del jugador, el vector es la posicion

    // GameProssesing client(hostname, port, commands);
    // client.run();

    // SdlManager manager(commands, positions);

    // manager.run();


    // try {
    //     int ret = -1;

    //     if (argc != 3) {
    //         std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
    //         return ret;
    //     }

    //     const char* hostname = argv[1];
    //     const char* port = argv[2];
    //     Queue<Action*> commands(10000);

    //     GameProcessing client(hostname, port, commands);
    //     client.run();
    //     ret = 0;
    //     return ret;
    // } catch (const std::exception& err) {
    //     std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
    //     return -1;
    // } catch (...) {
    //     std::cerr << "Something went wrong and an unknown exception was caught.\n";
    //     return -1;
    // }
}
