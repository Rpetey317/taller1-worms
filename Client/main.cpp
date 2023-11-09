#include <iostream>

#include "GameProcessing/GameProcessing.h"
#include "src/SdlManager/SdlManager.h"

int main(int argc, char* argv[]) {

    // Queue<int> commands;
    // Queue<std::vector<int>> positions;

    // SdlManager manager(commands, positions);

    // manager.run();

    try {
        int ret = -1;

        if (argc != 3) {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
            return ret;
        }

        const char* hostname = argv[1];
        const char* port = argv[2];

        GameProcessing client(hostname, port);
        client.run();
        ret = 0;
        return ret;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
