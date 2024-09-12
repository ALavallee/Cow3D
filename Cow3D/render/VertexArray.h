#ifndef COW3D_VERTEXARRAY_H
#define COW3D_VERTEXARRAY_H

#include <vector>
#include "GlLoader.h"
#include "Cow3D/math/Vec2.h"
#include "Cow3D/math/Vec3.h"
#include "Cow3D/math/Vec4.h"
#include "Cow3D/math/Mat4.h"

namespace cow {

struct Vertex3D {
    Vec3f pos;
    Vec2f tex_coord;
    Vec4f color;
    Vec4f joints;
    Vec4f weights;
};

struct Vertex3DSimple {
    Vec3f pos;
    Vec2f texCoord;
    Vec4f color;

    Vertex3DSimple(Vec3f pos, Vec2f tex, Vec4f color) : pos(pos), texCoord(tex), color(color) {

    }
};

struct Vertex2D {
    Vec2f pos;
    Vec2f texCoord;

    Vertex2D(Vec2f pos, Vec2f texCoord) : pos(pos), texCoord(texCoord) {

    }
};


class VertexArray {

public:

    VertexArray();

    VertexArray(VertexArray &&other) noexcept;

    explicit VertexArray(std::vector<Vertex3D> &vertices);

    explicit VertexArray(std::vector<Vertex3DSimple> &verticesSimple);

    VertexArray(std::vector<Vertex3D> &vertices, std::vector<unsigned int> indices);

    explicit VertexArray(std::vector<Vertex2D> &vertices);

    ~VertexArray();

    void use() const;

    void draw() const;

    VertexArray &operator=(VertexArray &&other) noexcept;


private:

    GLuint mVao;
    GLuint mVbo;
    GLuint mEbo;
    size_t mIndicesCount;
};

}

#endif //COW3D_VERTEXARRAY_H
