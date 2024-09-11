#ifndef COW3D_ANIMATION_H
#define COW3D_ANIMATION_H

#include <string>
#include <vector>
#include "TransformTrack.h"

namespace cow {

struct Animation {
    std::string name;
    std::vector<TransformTrack> tracks;
};

}

#endif //COW3D_ANIMATION_H
