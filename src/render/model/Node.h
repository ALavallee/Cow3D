#ifndef EVOCLIENT_NODE_H
#define EVOCLIENT_NODE_H

#include <string>
#include "math/Transform.h"
#include "math/Mat4.h"

namespace cow {

struct Node {

    Node() : parent(-1), transform(Transform::Default()), invBindMatrix(Mat4::identity()) {

    }


    std::string name;
    int parent;
    Transform transform;
    Mat4 invBindMatrix;

    static Mat4 computeGlobalTransform(int nodeId, std::vector<Node> &nodes) {
        if (nodeId >= 0) {
            Node *node = &nodes[nodeId];
            Mat4 parent = computeGlobalTransform(node->parent, nodes);
            return parent * node->transform.toMat();
        }

        return Mat4::identity();
    }
};

}

#endif //EVOCLIENT_NODE_H
