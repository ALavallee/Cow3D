#ifndef COW3D_RESMANAGER_H
#define COW3D_RESMANAGER_H

#include <unordered_map>
#include <string>
#include "Cow3D/audio/Sound.h"
#include "Cow3D/render/Texture.h"
#include "Cow3D/render/model/Model.h"

namespace cow {

class ResManager {

public:

    ResManager();

    Model *getModel(const std::string &name);

    Texture *getTexture(const std::string &name);

    Sound *getSound(const std::string &name);

private:

    void loadResources(const std::string &directory, const std::string &type);

    void loadTexture(const std::string &name, const std::string &path);

    void loadSound(const std::string &name, const std::string &path);

    void loadModel(const std::string &name, const std::string &path);

    std::unordered_map<std::string, Texture> mTextures;
    std::unordered_map<std::string, Sound> mSounds;
    std::unordered_map<std::string, Model> mModels;


};


}

#endif //COW3D_RESMANAGER_H
