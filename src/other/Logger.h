#ifndef EVOSERVER_LOGGER_H
#define EVOSERVER_LOGGER_H

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

#endif //EVOSERVER_LOGGER_H
