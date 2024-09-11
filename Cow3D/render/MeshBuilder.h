#ifndef COW3D_MESHBUILDER_H
#define COW3D_MESHBUILDER_H

#include <vector>
#include "math/Vec3.h"
#include "math/Vec2.h"
#include "math/Triangle.h"
#include "VertexArray.h"

namespace cow {

class MeshBuilder {

public:

    void addPoint(Vec3f pos, Vec2f tex);

    void addTriangle(Triangle triangle);

    void addPlane(Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p3);

    void addPlane(Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p3, Vec2f texBegin, Vec2f texEnd);

    void addCube(Vec3f middlePoint, float size);

    void addCube(Vec3f middlePoint, float halfSize, Vec2f texBegin, Vec2f texEnd);

    void addCubeWithTopAndBotUnique(Vec3f middlePoint, float halfSize, Vec2f texBegin,
                                    Vec2f texEnd, Vec2f topTexBegin, Vec2f topTexEnd, Vec2f botTexBegin,
                                    Vec2f botTexEnd);

    void addCubeWithTopBotAndFrontUnique(Vec3f middlePoint, float halfSize, Vec2f texBegin,
                                         Vec2f texEnd, Vec2f topBotBegin, Vec2f topBotEnd, Vec2f frontBegin,
                                         Vec2f frontEnd);

    std::vector<Vertex3D> &getVertices();

    std::vector<Vertex3DSimple> getSimpleVertices();

private:
    std::vector<Vertex3D> mVertices;

};
}

#endif //COW3D_MESHBUILDER_H
