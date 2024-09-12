#include "Scene3D.h"
#include "Cow3D/render/shader/DefaultShader.h"
#include "Cow3D/render/Texture.h"

namespace cow {

Scene3D::Scene3D() {
    mGeoShader.loadFromSource(std::string(DefaultShader::GeometryVertex),
                              std::string(DefaultShader::GeometryFragment));

    mModelShader.loadFromSource(std::string(DefaultShader::ModelVertex),
                                std::string(DefaultShader::ModelFragment));
}

AnimationInstance *Scene3D::addAnimation(Vec3f pos, Model *model, float yScale) {
    auto animation = new AnimationInstance(model, yScale);
    animation->setPosition(pos);
    mAnimations.push_back(animation);
    return animation;
}

ModelInstance *Scene3D::addModel(Vec3f pos, cow::Model *model, float yScale) {
    auto newModel = new ModelInstance(model, yScale);
    newModel->setPosition(pos);
    mModels.push_back(newModel);
    return newModel;
}

Geometry *Scene3D::addGeometry(cow::Vec3f pos, std::vector<Vertex3D> &vertices) {
    auto newGeo = new Geometry(vertices);
    newGeo->setPosition(pos);
    mGeometries.push_back(newGeo);
    return newGeo;
}

Geometry *Scene3D::addGeometry(cow::Vec3f pos, std::vector<Vertex3DSimple> &vertices) {
    auto newGeo = new Geometry(vertices);
    newGeo->setPosition(pos);
    mGeometries.push_back(newGeo);
    return newGeo;
}

void Scene3D::draw(Camera &camera) {
    Texture::Default().use();
    mGeoShader.use();
    auto matrix = camera.getProjection() * camera.getView();
    mGeoShader.setUniformMat4("camera", matrix);
    for (auto &geo: mGeometries) {
        mGeoShader.setUniformVec4("color", geo->getColor().toVec());
        mGeoShader.setUniformMat4("model", Mat4::fromTranslation(geo->getPosition()));
        geo->getVa().draw();
    }


    mModelShader.use();
    mModelShader.setUniformMat4("camera", matrix);
    mModelShader.setUniformVec4("color", Color::white().toVec());
    for (auto &model: mModels) {
        float yScale = model->getModel()->getScalingFactorY(model->getYScale());
        mModelShader.setUniformMat4("model", Mat4::fromTranslation(model->getPosition()) *
                                             Mat4::fromScale(Vec3f(yScale, yScale, yScale)));
        std::vector<Mat4> jointsMatrix;
        jointsMatrix.resize(model->getModel()->getNodes().size());
        for (auto &it: jointsMatrix) {
            it = Mat4::identity();
        }
        mModelShader.setUniformMat4("joint_matrices", jointsMatrix);
        for (size_t i = 0; i < model->getModel()->getMeshesCount(); ++i) {
            Mesh *mesh = model->getModel()->getMesh(i);
            if (!mesh->vertices.empty()) {

                if (mesh->texture.isLoaded()) {
                    mesh->texture.use();
                } else if (model->getModel()->getTexture().isLoaded()) {
                    model->getModel()->getTexture().use();
                } else {
                    Texture::Default().use();
                }

                if (mesh->indices.empty()) {
                    VertexArray array(mesh->vertices);
                    array.draw();
                } else {
                    VertexArray array(mesh->vertices, mesh->indices);
                    array.draw();
                }
            }
        }
    }

    for (auto &model: mModels) {
        float yScale = model->getModel()->getScalingFactorY(model->getYScale());
        mModelShader.setUniformMat4("model", Mat4::fromTranslation(model->getPosition()) *
                                             Mat4::fromScale(Vec3f(yScale, yScale, yScale)));
        std::vector<Mat4> jointsMatrix;
        jointsMatrix.resize(model->getModel()->getNodes().size());
        for (auto &it: jointsMatrix) {
            it = Mat4::identity();
        }
        mModelShader.setUniformMat4("joint_matrices", jointsMatrix);
        for (size_t i = 0; i < model->getModel()->getMeshesCount(); ++i) {
            Mesh *mesh = model->getModel()->getMesh(i);
            if (!mesh->vertices.empty()) {

                if (mesh->texture.isLoaded()) {
                    mesh->texture.use();
                } else if (model->getModel()->getTexture().isLoaded()) {
                    model->getModel()->getTexture().use();
                } else {
                    Texture::Default().use();
                }

                if (mesh->indices.empty()) {
                    VertexArray array(mesh->vertices);
                    array.draw();
                } else {
                    VertexArray array(mesh->vertices, mesh->indices);
                    array.draw();
                }
            }
        }
    }

    for (auto &instance: mAnimations) {
        instance->update();
        float yScale = instance->getModel().getModel()->getScalingFactorY(instance->getYScale());
        Texture::Default().use();
        mModelShader.setUniformVec4("color", Color::white().toVec());
        mModelShader.setUniformMat4("model", Mat4::fromTranslation(instance->getPosition()) *
                                             Mat4::fromScale(Vec3f(yScale, yScale, yScale)));

        auto resultNodes = instance->getModel().computeResultNodes();

        for (size_t i = 0; i < instance->getModel().getModel()->getMeshesCount(); ++i) {
            std::vector<Mat4> jointsMatrix;
            jointsMatrix.resize(instance->getModel().getModel()->getNodes().size());

            Mesh *mesh = instance->getModel().getModel()->getMesh(i);
            Mat4 globalTransform = Node::computeGlobalTransform(mesh->parent, resultNodes);
            if (mesh->hasJoints) {
                globalTransform = globalTransform.inverse();
                for (size_t j = 0; j < resultNodes.size(); ++j) {
                    Mat4 join = Node::computeGlobalTransform(static_cast<int>(j), resultNodes);
                    jointsMatrix[j] = (globalTransform * join) * resultNodes[j].invBindMatrix;
                }
            } else {
                jointsMatrix[0] = globalTransform;
            }

            mModelShader.setUniformMat4("joint_matrices", jointsMatrix);

            if (mesh->texture.isLoaded()) {
                mesh->texture.use();
            } else if (instance->getModel().getModel()->getTexture().isLoaded()) {
                instance->getModel().getModel()->getTexture().use();
            } else {
                Texture::Default().use();
            }

            if (!mesh->vertices.empty()) {
                if (mesh->indices.empty()) {
                    VertexArray array(mesh->vertices);
                    array.draw();
                } else {
                    VertexArray array(mesh->vertices, mesh->indices);
                    array.draw();
                }
            }
        }
    }
}

}