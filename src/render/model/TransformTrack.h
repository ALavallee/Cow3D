#ifndef EVOCLIENT_TRANSFORMTRACK_H
#define EVOCLIENT_TRANSFORMTRACK_H

#include "Track.h"
#include "math/Transform.h"

namespace cow {

struct TransformTrack {

    TransformTrack() : targetNodeId(-1) {

    }

    Transform sample(float time, bool loop, Transform base) {
        Transform result;
        result.translation = position.sample(time, loop, base.translation);
        result.rotation = rotation.sample(time, loop, base.rotation);
        result.scale = scale.sample(time, loop, base.scale);
        return result;
    }

    int targetNodeId;
    Track<Vec3f> position;
    Track<Quat> rotation;
    Track<Vec3f> scale;

};

}

#endif //EVOCLIENT_TRANSFORMTRACK_H
