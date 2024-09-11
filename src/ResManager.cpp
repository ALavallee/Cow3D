#include "ResManager.h"
#include <filesystem>

namespace cow {

ResManager::ResManager() {
    loadResources("./res/", "model");
    loadResources("./res/", "texture");
    loadResources("./res/", "sound");
}

Model *ResManager::getModel(const std::string &name) {
    auto it = mModels.find(name);
    if (it != mModels.end()) {
        return &it->second;
    }
    return nullptr;
}

Texture *ResManager::getTexture(const std::string &name) {
    auto it = mTextures.find(name);
    if (it != mTextures.end()) {
        return &it->second;
    }
    return nullptr;
}

Sound *ResManager::getSound(const std::string &name) {
    auto it = mSounds.find(name);
    if (it != mSounds.end()) {
        return &it->second;
    }
    return nullptr;
}

void ResManager::loadResources(const std::string &directory, const std::string &type) {
    for (const auto &entry: std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            std::string filename = entry.path().stem().string(); // Get file name without extension

            if (type == "model" && (entry.path().extension() == ".glb" || entry.path().extension() == ".gltf")) {
                loadModel(filename, path);
            } else if (type == "texture" &&
                       (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")) {
                loadTexture(filename, path);
            } else if (type == "sound" && entry.path().extension() == ".wav") {
                loadSound(filename, path);
            }
        }
    }
}

void ResManager::loadTexture(const std::string &name, const std::string &path) {
    mTextures[name].load(path);
}

void ResManager::loadSound(const std::string &name, const std::string &path) {
    mSounds[name].load(path);
}

void ResManager::loadModel(const std::string &name, const std::string &path) {
    mModels[name].loadFromFile(path);
}

}