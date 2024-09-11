#ifndef EVOCLIENT_FILE_H
#define EVOCLIENT_FILE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

namespace cow {

class File {
public:

    static std::string LoadEntireStringFromPath(const std::string& path) {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    static std::vector<char> LoadEntireBufferFromPath(const std::string& path) {
        std::ifstream file(path, std::ios::binary);

        if (!file) {
            return {};
        }

        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        file.read(buffer.data(), size);
        return buffer;
    }

};

}

#endif //EVOCLIENT_FILE_H
