#ifndef COW3D_LOGGER_H
#define COW3D_LOGGER_H

#include <iostream>
#include <string>

namespace cow {

class Logger {

public:

    static void Log(std::string log) {
        std::cout << log << std::endl;
    }

};

}

#endif //COW3D_LOGGER_H
