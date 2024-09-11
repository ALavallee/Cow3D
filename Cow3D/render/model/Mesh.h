#ifndef COW3D_MESH_H
#define COW3D_MESH_H

#include <vector>
#include "render/VertexArray.h"

namespace cow {

struct Mesh {

    Mesh() : parent(-1), hasJoints(false) {

    }


    std::string name;
    int parent;
    Texture texture;
    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;
    bool hasJoints;
    Vec3f min, max;
};

}

#endif //COW3D_MESH_H
