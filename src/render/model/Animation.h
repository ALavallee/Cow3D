#ifndef EVOCLIENT_ANIMATION_H
#define EVOCLIENT_ANIMATION_H

#include <string>
#include <vector>
#include "TransformTrack.h"

namespace cow {

struct Animation {
    std::string name;
    std::vector<TransformTrack> tracks;
};

}

#endif //EVOCLIENT_ANIMATION_H
