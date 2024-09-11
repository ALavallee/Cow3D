#include "MeshBuilder.h"
#include "Color.h"

namespace cow {

void MeshBuilder::addPoint(Vec3f pos, Vec2f tex) {
    Vertex3D newVertex;
    newVertex.pos = pos;
    newVertex.tex_coord = tex;
    newVertex.joints = Vec4f(-1.f, -1.f, -1.f, -1.f);
    newVertex.weights = Vec4f(.25f, .25f, .25f, .25f);
    newVertex.color = Color::white().toVec();
    mVertices.push_back(newVertex);
}

void MeshBuilder::addTriangle(Triangle triangle) {
    addPoint(triangle.p0.to<float>(), Vec2f());
    addPoint(triangle.p1.to<float>(), Vec2f());
    addPoint(triangle.p2.to<float>(), Vec2f());
}

void MeshBuilder::addPlane(Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p3) {
    addPoint(p0, Vec2f(0, 0));
    addPoint(p1, Vec2f(1, 0));
    addPoint(p2, Vec2f(1, 1));

    addPoint(p2, Vec2f(1, 1));
    addPoint(p3, Vec2f(0, 1));
    addPoint(p0, Vec2f(0, 0));
}

void MeshBuilder::addPlane(Vec3f p0, Vec3f p1, Vec3f p2, Vec3f p3, Vec2f texBegin, Vec2f texEnd) {
    addPoint(p0, Vec2f(texBegin.x, texBegin.y));
    addPoint(p1, Vec2f(texEnd.x, texBegin.y));
    addPoint(p2, Vec2f(texEnd.x, texEnd.y));

    addPoint(p2, Vec2f(texEnd.x, texEnd.y));
    addPoint(p3, Vec2f(texBegin.x, texEnd.y));
    addPoint(p0, Vec2f(texBegin.x, texBegin.y));
}

void MeshBuilder::addCube(Vec3f middlePoint, float size) {
    float halfSize = size / 2.0f;

    Vec3f p0 = middlePoint + Vec3f(-halfSize, -halfSize, -halfSize);
    Vec3f p1 = middlePoint + Vec3f(halfSize, -halfSize, -halfSize);
    Vec3f p2 = middlePoint + Vec3f(halfSize, halfSize, -halfSize);
    Vec3f p3 = middlePoint + Vec3f(-halfSize, halfSize, -halfSize);
    Vec3f p4 = middlePoint + Vec3f(-halfSize, -halfSize, halfSize);
    Vec3f p5 = middlePoint + Vec3f(halfSize, -halfSize, halfSize);
    Vec3f p6 = middlePoint + Vec3f(halfSize, halfSize, halfSize);
    Vec3f p7 = middlePoint + Vec3f(-halfSize, halfSize, halfSize);

    // Front face
    addPlane(p0, p1, p2, p3);
    // Back face
    addPlane(p5, p4, p7, p6);
    // Left face
    addPlane(p4, p0, p3, p7);
    // Right face
    addPlane(p1, p5, p6, p2);
    // Top face
    addPlane(p3, p2, p6, p7);
    // Bottom face
    addPlane(p4, p5, p1, p0);
}

void MeshBuilder::addCube(Vec3f middlePoint, float halfSize, Vec2f texBegin, Vec2f texEnd) {

    Vec3f p0 = middlePoint + Vec3f(-halfSize, -halfSize, -halfSize);
    Vec3f p1 = middlePoint + Vec3f(halfSize, -halfSize, -halfSize);
    Vec3f p2 = middlePoint + Vec3f(halfSize, halfSize, -halfSize);
    Vec3f p3 = middlePoint + Vec3f(-halfSize, halfSize, -halfSize);
    Vec3f p4 = middlePoint + Vec3f(-halfSize, -halfSize, halfSize);
    Vec3f p5 = middlePoint + Vec3f(halfSize, -halfSize, halfSize);
    Vec3f p6 = middlePoint + Vec3f(halfSize, halfSize, halfSize);
    Vec3f p7 = middlePoint + Vec3f(-halfSize, halfSize, halfSize);

    // Front face
    addPlane(p0, p1, p2, p3, texBegin, texEnd);
    // Back face
    addPlane(p5, p4, p7, p6, texBegin, texEnd);
    // Left face
    addPlane(p4, p0, p3, p7, texBegin, texEnd);
    // Right face
    addPlane(p1, p5, p6, p2, texBegin, texEnd);
    // Top face
    addPlane(p3, p2, p6, p7, texBegin, texEnd);
    // Bottom face
    addPlane(p4, p5, p1, p0, texBegin, texEnd);
}

void MeshBuilder::addCubeWithTopAndBotUnique(Vec3f middlePoint, float halfSize, Vec2f texBegin,
                                             Vec2f texEnd, Vec2f topTexBegin, Vec2f topTexEnd,
                                             Vec2f botTexBegin, Vec2f botTexEnd) {

    Vec3f p0 = middlePoint + Vec3f(-halfSize, -halfSize, -halfSize);
    Vec3f p1 = middlePoint + Vec3f(halfSize, -halfSize, -halfSize);
    Vec3f p2 = middlePoint + Vec3f(halfSize, halfSize, -halfSize);
    Vec3f p3 = middlePoint + Vec3f(-halfSize, halfSize, -halfSize);
    Vec3f p4 = middlePoint + Vec3f(-halfSize, -halfSize, halfSize);
    Vec3f p5 = middlePoint + Vec3f(halfSize, -halfSize, halfSize);
    Vec3f p6 = middlePoint + Vec3f(halfSize, halfSize, halfSize);
    Vec3f p7 = middlePoint + Vec3f(-halfSize, halfSize, halfSize);

    // Front face
    addPlane(p0, p1, p2, p3, texBegin, texEnd);
    // Back face
    addPlane(p5, p4, p7, p6, texBegin, texEnd);
    // Left face
    addPlane(p4, p0, p3, p7, texBegin, texEnd);
    // Right face
    addPlane(p1, p5, p6, p2, texBegin, texEnd);
    // Top face
    addPlane(p3, p2, p6, p7, topTexBegin, topTexEnd);
    // Bottom face
    addPlane(p4, p5, p1, p0, botTexBegin, botTexEnd);
}

void MeshBuilder::addCubeWithTopBotAndFrontUnique(Vec3f middlePoint, float halfSize, Vec2f texBegin,
                                                  Vec2f texEnd, Vec2f topBotBegin, Vec2f topBotEnd, Vec2f frontBegin,
                                                  Vec2f frontEnd) {
    Vec3f p0 = middlePoint + Vec3f(-halfSize, -halfSize, -halfSize);
    Vec3f p1 = middlePoint + Vec3f(halfSize, -halfSize, -halfSize);
    Vec3f p2 = middlePoint + Vec3f(halfSize, halfSize, -halfSize);
    Vec3f p3 = middlePoint + Vec3f(-halfSize, halfSize, -halfSize);
    Vec3f p4 = middlePoint + Vec3f(-halfSize, -halfSize, halfSize);
    Vec3f p5 = middlePoint + Vec3f(halfSize, -halfSize, halfSize);
    Vec3f p6 = middlePoint + Vec3f(halfSize, halfSize, halfSize);
    Vec3f p7 = middlePoint + Vec3f(-halfSize, halfSize, halfSize);

    // Front face
    addPlane(p0, p1, p2, p3, frontBegin, frontEnd);
    // Back face
    addPlane(p5, p4, p7, p6, texBegin, texEnd);
    // Left face
    addPlane(p4, p0, p3, p7, texBegin, texEnd);
    // Right face
    addPlane(p1, p5, p6, p2, texBegin, texEnd);
    // Top face
    addPlane(p3, p2, p6, p7, topBotBegin, topBotEnd);
    // Bottom face
    addPlane(p4, p5, p1, p0, topBotBegin, topBotEnd);
}

std::vector<Vertex3D> &MeshBuilder::getVertices() {
    return mVertices;
}

std::vector<Vertex3DSimple> MeshBuilder::getSimpleVertices() {
    auto results = std::vector<Vertex3DSimple>();
    for (auto &vertices: mVertices) {
        results.emplace_back(vertices.pos, vertices.tex_coord, vertices.color);
    }
    return results;
}

}