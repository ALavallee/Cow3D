#include "VertexArray.h"


template<typename T, typename M>
static std::size_t offset_of(M T::*member) {
    return reinterpret_cast<std::size_t>(&(reinterpret_cast<T *>(0)->*member));
}

namespace cow {

VertexArray::VertexArray() : mVao(0), mVbo(0), mEbo(0), mIndicesCount(0) {

}

VertexArray::VertexArray(VertexArray &&other) noexcept: mVao(other.mVao), mVbo(other.mVbo), mEbo(other.mEbo),
                                                        mIndicesCount(other.mIndicesCount) {
    other.mVao = 0;
    other.mVbo = 0;
    other.mEbo = 0;
    other.mIndicesCount = 0;
}

VertexArray::VertexArray(std::vector<Vertex3D> &vertices) : VertexArray() {
    glGenVertexArrays(1, &mVao);
    glGenBuffers(1, &mVbo);

    glBindVertexArray(mVao);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::pos));
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::tex_coord));
    glEnableVertexAttribArray(1);

    // Color attribute
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::color));
    glEnableVertexAttribArray(2);

    // Joint attributes
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::joints));
    glEnableVertexAttribArray(3);

    // Weights attribute
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::weights));
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mIndicesCount = vertices.size();
}

VertexArray::VertexArray(std::vector<Vertex3DSimple> &vertices) : mVao(0), mVbo(0), mEbo(0) {
    glGenVertexArrays(1, &mVao);
    glGenBuffers(1, &mVbo);

    glBindVertexArray(mVao);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3DSimple) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DSimple), (void *) offset_of(&Vertex3DSimple::pos));
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DSimple),
                          (void *) offset_of(&Vertex3DSimple::texCoord));
    glEnableVertexAttribArray(1);

    // Color attribute
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3DSimple), (void *) offset_of(&Vertex3DSimple::color));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mIndicesCount = vertices.size();
}

VertexArray::VertexArray(std::vector<Vertex3D> &vertices, std::vector<unsigned int> indices) : VertexArray() {
    // Generate and bind the Vertex Array Object (VAO)
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    // Generate and bind the Vertex Buffer Object (VBO) for vertices
    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Generate and bind the Element Buffer Object (EBO) for indices
    glGenBuffers(1, &mEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::pos));
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::tex_coord));
    glEnableVertexAttribArray(1);

    // Color attribute
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::color));
    glEnableVertexAttribArray(2);

    // Joint attributes
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::joints));
    glEnableVertexAttribArray(3);

    // Weights attribute
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *) offset_of(&Vertex3D::weights));
    glEnableVertexAttribArray(4);

    // Unbind the VBO and VAO to leave a clean state
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mIndicesCount = indices.size();
}

VertexArray::VertexArray(std::vector<Vertex2D> &vertices) : mEbo(0) {
    glGenVertexArrays(1, &mVao);
    glGenBuffers(1, (GLuint *) &mVbo);

    glBindVertexArray(mVao);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *) offset_of(&Vertex2D::pos));
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *) offset_of(&Vertex2D::texCoord));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // unbind

    mIndicesCount = vertices.size();
}

VertexArray::~VertexArray() {
    glDeleteBuffers(1, &mVbo);

    if (mEbo) {
        glDeleteBuffers(1, &mEbo);
    }

    glDeleteVertexArrays(1, &mVao);
}

void VertexArray::use() const {
    glBindVertexArray(mVao);
}

void VertexArray::draw() const {
    use();
    if (mEbo) {
        glDrawElements(GL_TRIANGLES, (GLsizei) mIndicesCount, GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei) mIndicesCount);
    }
    glBindVertexArray(0); // unbind
}

VertexArray &VertexArray::operator=(VertexArray &&other) noexcept {
    if (this != &other) {
        glDeleteVertexArrays(1, &mVao);
        glDeleteBuffers(1, &mVbo);
        if (mEbo) {
            glDeleteBuffers(1, &mEbo);
        }

        mVao = other.mVao;
        mVbo = other.mVbo;
        mEbo = other.mEbo;
        mIndicesCount = other.mIndicesCount;

        other.mVao = 0;
        other.mVbo = 0;
        other.mEbo = 0;
        other.mIndicesCount = 0;
    }
    return *this;
}

}