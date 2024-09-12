#include "Model.h"

#define CGLTF_IMPLEMENTATION

#include "ext/cgltf/cgltf.h"
#include "Track.h"
#include "Cow3D/other/Logger.h"
#include "Cow3D/other/File.h"

static cgltf_result
LoadFileGLTFCallback(const struct cgltf_memory_options *memoryOptions, const struct cgltf_file_options *fileOptions,
                     const char *path, cgltf_size *size, void **data) {
    return cgltf_result_io_error;
}

static void
ReleaseFileGLTFCallback(const struct cgltf_memory_options *memoryOptions, const struct cgltf_file_options *fileOptions,
                        void *data) {
    free(data);
}

int static getNodeIndex(cgltf_node *target, cgltf_node *all_nodes, size_t num_nodes) {
    if (target == nullptr) {
        return -1;
    }

    for (size_t i = 0; i < num_nodes; ++i) {
        if (target == &all_nodes[i]) {
            return (int) i;
        }
    }
    return -1;
}

namespace cow {

static Transform getLocalTransform(cgltf_node *node) {
    Transform result;

    if (node->has_matrix) {
        Mat4 matrix;
        memcpy(&matrix, &node->matrix, sizeof(matrix));
        //result = mat4_to_transform(matrix);
    }

    if (node->has_rotation) {
        result.rotation = (Quat) {node->rotation[0], node->rotation[1], node->rotation[2], node->rotation[3]};
    } else {
        result.rotation = Quat::identity();
    }

    if (node->has_translation) {
        result.translation = Vec3f(node->translation[0], node->translation[1], node->translation[2]);
    } else {
        result.translation = Vec3f();
    }

    if (node->has_scale) {
        result.scale = Vec3f(node->scale[0], node->scale[1], node->scale[2]);
    } else {
        result.scale = Vec3f(1, 1, 1);
    }

    return result;
}

template<class T>
Track<T> trackFromChannel(cgltf_animation_channel *channel) {
    cgltf_animation_sampler *sampler = channel->sampler;
    Track<T> result;

    if (sampler->interpolation == cgltf_interpolation_type_step) {
        result.interpolation = Interpolation::Constant;
    } else if (sampler->interpolation == cgltf_interpolation_type_cubic_spline) {
        result.interpolation = Interpolation::Cubic;
    } else if (sampler->interpolation == cgltf_interpolation_type_linear) {
        result.interpolation = Interpolation::Linear;
    }

    size_t num_frames = sampler->input->count;
    result.frames.resize(num_frames);

    for (size_t i = 0; i < num_frames; ++i) {
        cgltf_accessor_read_float(sampler->input, i, &result.frames[i].time, 1);
    }

    size_t num_values = sampler->output->count;
    for (size_t i = 0; i < num_values; ++i) {
        cgltf_type track_type = sampler->output->type;
        if (track_type == cgltf_type_vec3) {
            if (sizeof(T) != sizeof(Vec3f)) {
                Logger::Log("Size error for track");
            }
            cgltf_accessor_read_float(sampler->output, i,
                                      (float *) &result.frames[i].v, 3);
        } else if (track_type == cgltf_type_vec4) {
            if (sizeof(T) != sizeof(Vec4f)) {
                Logger::Log("Size error for track");
            }
            cgltf_accessor_read_float(sampler->output, i,
                                      (float *) &result.frames[i].v, 4);
        } else {
            Logger::Log("Unknown format for track");
        }
    }

    return result;
}

std::vector<Animation> loadAnimations(cgltf_data *data) {
    std::vector<Animation> results;
    results.resize(data->animations_count);

    for (size_t i = 0; i < data->animations_count; ++i) {
        size_t num_channels = data->animations[i].channels_count;
        results[i].name = data->animations[i].name != nullptr ? std::string(data->animations[i].name) : "";
        results[i].tracks.resize(num_channels);
        for (size_t j = 0; j < num_channels; ++j) {
            cgltf_animation_channel *channel = &data->animations[i].channels[j];
            cgltf_node *target = channel->target_node;
            if (channel->target_path == cgltf_animation_path_type_translation) {
                results[i].tracks[j].position = trackFromChannel<Vec3f>(channel);
            } else if (channel->target_path == cgltf_animation_path_type_scale) {
                results[i].tracks[j].scale = trackFromChannel<Vec3f>(channel);
            } else if (channel->target_path == cgltf_animation_path_type_rotation) {
                results[i].tracks[j].rotation = trackFromChannel<Quat>(channel);
            }

            int node_id = getNodeIndex(target, data->nodes, data->nodes_count);
            results[i].tracks[j].targetNodeId = node_id;
        }
    }

    return results;
}

static std::vector<Node> loadNodes(cgltf_data *data) {
    std::vector<Node> nodes;
    nodes.resize(data->nodes_count);

    if (data->nodes_count >= 150) {
        Logger::Log("Max node exceeded");
        return {};
    }

    for (size_t i = 0; i < data->nodes_count; ++i) {
        cgltf_node *gltf_node = &data->nodes[i];
        int node_id = getNodeIndex(gltf_node->parent, data->nodes, data->nodes_count);
        if (node_id >= 0) {
            nodes[i].parent = node_id;
        } else {
            nodes[i].parent = -1;
        }
        nodes[i].transform = getLocalTransform(gltf_node);
        nodes[i].invBindMatrix = Mat4::identity();
        nodes[i].name = gltf_node->name != nullptr ? std::string(gltf_node->name) : "";
    }

    return nodes;
}

static void loadJoints(Model *model, cgltf_data *data) {
    if (data->skins_count > 1) {
        Logger::Log("Only support one skin");
        return;
    } else if (data->skins_count == 0) {
        return;
    }

    cgltf_skin *skin = &data->skins[0];
    for (size_t i = 0; i < skin->joints_count; ++i) {
        int node_id = getNodeIndex(skin->joints[i], data->nodes, data->nodes_count);
        Mat4 inv_bind;
        cgltf_accessor_read_float(skin->inverse_bind_matrices, i, (float *) &inv_bind, 16);
        model->getNodes()[node_id].invBindMatrix = inv_bind;
    }
}

GLenum convertWrapModeToOpenGL(cgltf_int gltf_wrap_mode) {
    switch (gltf_wrap_mode) {
        case 33071:
            return GL_CLAMP_TO_EDGE;
        case 33648:
            return GL_MIRRORED_REPEAT;
        case 10497:
        default:
            return GL_REPEAT;
    }
}

GLenum convertMinFilterToOpenGL(cgltf_int gltf_min_filter) {
    switch (gltf_min_filter) {
        case 9728:
            return GL_NEAREST;
        case 9729:
            return GL_LINEAR;
        case 9984:
            return GL_NEAREST_MIPMAP_NEAREST;
        case 9985:
            return GL_LINEAR_MIPMAP_NEAREST;
        case 9986:
            return GL_NEAREST_MIPMAP_LINEAR;
        case 9987:
            return GL_LINEAR_MIPMAP_LINEAR;
        default:
            return GL_LINEAR;
    }
}

GLenum convertMagFilterToOpenGL(cgltf_int gltf_mag_filter) {
    switch (gltf_mag_filter) {
        case 9728:
            return GL_NEAREST;
        case 9729:
        default:
            return GL_LINEAR;
    }
}

Texture loadMeshTexture(cgltf_primitive *primitive) {
    Texture texture = Texture::Default();
    if (primitive->material != nullptr && primitive->material->has_pbr_metallic_roughness) {
        cgltf_texture *gltf_texture = primitive->material->pbr_metallic_roughness.base_color_texture.texture;
        if (gltf_texture != nullptr && gltf_texture->image->buffer_view != nullptr) {
            char *texture_data = (char *) cgltf_buffer_view_data(gltf_texture->image->buffer_view);
            texture.load(texture_data, gltf_texture->image->buffer_view->size);
            if (gltf_texture->sampler != nullptr) {
                texture.setFilter(convertMinFilterToOpenGL(gltf_texture->sampler->min_filter),
                                  convertMagFilterToOpenGL(gltf_texture->sampler->mag_filter));
                texture.setWrap(convertWrapModeToOpenGL(gltf_texture->sampler->wrap_s),
                                convertWrapModeToOpenGL(gltf_texture->sampler->wrap_t));
            }
        } else {
            cgltf_float *factor = primitive->material->pbr_metallic_roughness.base_color_factor;
            Color color = Color::fromFloats(factor[0], factor[1], factor[2], factor[3]);
            texture.load({color}, 1, 1);
        }
    }

    return texture;
}

std::vector<Mesh> loadMesh(cgltf_node *node, cgltf_skin *skin, cgltf_mesh *gltf_mesh, cgltf_data *data) {
    std::vector<Mesh> meshes;
    for (size_t j = 0; j < gltf_mesh->primitives_count; ++j) {

        cgltf_primitive *primitive = &gltf_mesh->primitives[j];

        meshes.emplace_back();
        Mesh *mesh = &meshes[meshes.size() - 1];
        mesh->min = Vec3f(std::numeric_limits<float>::max());
        mesh->max = Vec3f(std::numeric_limits<float>::min());
        mesh->name = gltf_mesh->name != nullptr ? std::string(gltf_mesh->name) : "";
        mesh->parent = getNodeIndex(node, data->nodes, data->nodes_count);
        mesh->texture = loadMeshTexture(primitive);

        size_t vertices_count = 0;
        for (size_t k = 0; k < primitive->attributes_count; ++k) {
            vertices_count = std::max(vertices_count, primitive->attributes[k].data->count);
        }

        mesh->vertices.resize(vertices_count);

        if (primitive->indices != nullptr) {
            mesh->indices.resize(primitive->indices->count);
            if (!mesh->indices.empty()) {
                for (size_t k = 0; k < primitive->indices->count; ++k) {
                    cgltf_accessor_read_uint(primitive->indices, k, &mesh->indices[k], 1);
                }
            }
        }

        bool has_color = false;
        mesh->hasJoints = false;

        if (primitive->type == cgltf_primitive_type_triangles) {
            for (size_t k = 0; k < primitive->attributes_count; ++k) {
                cgltf_attribute *attribute = &primitive->attributes[k];
                if (attribute->type == cgltf_attribute_type_position) {
                    for (size_t l = 0; l < attribute->data->count; ++l) {
                        Vec3f position;
                        cgltf_accessor_read_float(attribute->data, l, (float *) &position, 3);
                        mesh->vertices[l].pos = position;
                        mesh->min = mesh->min.min(position);
                        mesh->max = mesh->max.max(position);
                    }
                } else if (attribute->type == cgltf_attribute_type_normal) {
                    for (size_t l = 0; l < attribute->data->count; ++l) {
                        Vec3f normal;
                        cgltf_accessor_read_float(attribute->data, l, (float *) &normal, 3);
                    }
                } else if (attribute->type == cgltf_attribute_type_texcoord) {
                    for (size_t l = 0; l < attribute->data->count; ++l) {
                        Vec2f coord;
                        cgltf_accessor_read_float(attribute->data, l, (float *) &coord, 2);
                        mesh->vertices[l].tex_coord = coord;
                    }
                } else if (attribute->type == cgltf_attribute_type_color) {
                    has_color = true;
                    for (size_t l = 0; l < attribute->data->count; ++l) {
                        Vec4f color;
                        cgltf_accessor_read_float(attribute->data, l, (float *) &color, 4);
                        mesh->vertices[l].color = color;
                    }
                } else if (attribute->type == cgltf_attribute_type_joints) {
                    for (size_t l = 0; l < attribute->data->count; ++l) {
                        mesh->hasJoints = true;
                        // these indices are skin relative
                        Vec4i r;
                        cgltf_accessor_read_uint(attribute->data, l, (unsigned int *) &r, 4);
                        Vec4f s;
                        s.x = (float) getNodeIndex(skin->joints[r.x], data->nodes, data->nodes_count);
                        s.y = (float) getNodeIndex(skin->joints[r.y], data->nodes, data->nodes_count);
                        s.z = (float) getNodeIndex(skin->joints[r.z], data->nodes, data->nodes_count);
                        s.w = (float) getNodeIndex(skin->joints[r.w], data->nodes, data->nodes_count);
                        mesh->vertices[l].joints = s;
                    }
                } else if (attribute->type == cgltf_attribute_type_weights) {
                    for (size_t l = 0; l < attribute->data->count; ++l) {
                        Vec4f weight;
                        cgltf_accessor_read_float(attribute->data, l, (float *) &weight, 4);
                        mesh->vertices[l].weights = weight;
                    }
                }
            }
        } else {
            Logger::Log("Unsupported primitive type for model");
        }

        if (!has_color) {
            for (size_t k = 0; k < vertices_count; ++k) {
                mesh->vertices[k].color = Color::white().toVec();
            }
        }

        if (!mesh->hasJoints) {
            for (size_t k = 0; k < vertices_count; ++k) {
                mesh->vertices[k].joints = Vec4f(0, 0, 0, 0);
                mesh->vertices[k].weights = Vec4f(0.25f, 0.25f, 0.25f, 0.25f);
            }
        }
    }

    return meshes;
}

std::vector<Mesh> loadScenes(cgltf_data *data) {
    std::vector<Mesh> meshes;
    for (size_t i = 0; i < data->meshes_count; ++i) {
        cgltf_mesh *mesh = &data->meshes[i];
        cgltf_node *node = nullptr;
        cgltf_skin *skin = nullptr;

        // find the node
        for (size_t j = 0; j < data->nodes_count; ++j) {
            if (data->nodes[j].mesh == mesh) {
                node = &data->nodes[j];
                skin = node->skin;
            }
        }

        auto loadedMesh = loadMesh(node, skin, mesh, data);
        meshes.insert(meshes.end(), loadedMesh.begin(), loadedMesh.end());
    }

    return meshes;
}

Texture loadMaterial(cgltf_data *data) {
    Texture texture = Texture::Default();
    if (data->textures_count > 0) {
        cgltf_texture *gltf_texture = &data->textures[0];
        if (gltf_texture != nullptr && gltf_texture->image->buffer_view != nullptr) {
            char *texture_data = (char *) cgltf_buffer_view_data(gltf_texture->image->buffer_view);
            texture.load(texture_data, gltf_texture->image->buffer_view->size);
            if (gltf_texture->sampler != nullptr) {
                texture.setFilter(convertMinFilterToOpenGL(gltf_texture->sampler->min_filter),
                                  convertMagFilterToOpenGL(gltf_texture->sampler->mag_filter));
                texture.setWrap(convertWrapModeToOpenGL(gltf_texture->sampler->wrap_s),
                                convertWrapModeToOpenGL(gltf_texture->sampler->wrap_t));
            }
        }
    }

    return texture;
}


Model::Model() {
}

bool Model::loadFromFile(std::string path) {
    // glTF file loading
    auto fileData = File::LoadEntireBufferFromPath(path);

    // glTF data loading
    cgltf_options options{};
    options.file.read = LoadFileGLTFCallback;
    options.file.release = ReleaseFileGLTFCallback;
    cgltf_data *data = nullptr;
    cgltf_result result = cgltf_parse(&options, fileData.data(), fileData.size(), &data);

    if (result == cgltf_result_success && cgltf_validate(data) == cgltf_result_success &&
        cgltf_load_buffers(&options, data, path.c_str()) == cgltf_result_success) {
        mNodes = loadNodes(data);
        loadJoints(this, data);
        mMeshes = loadScenes(data);
        mAnimations = loadAnimations(data);
        mTexture = loadMaterial(data);
    } else {
        Logger::Log("Failed to load glTF data");
        return false;
    }

    cgltf_free(data);
    return true;
}

Vec3f Model::getMinPos() {
    Vec3f pos(std::numeric_limits<float>::max());
    for (auto &mesh: mMeshes) {
        pos = pos.min(mesh.min);
    }
    return pos;
}

Vec3f Model::getMaxPos() {
    Vec3f pos(std::numeric_limits<float>::min());
    for (auto &mesh: mMeshes) {
        pos = pos.max(mesh.max);
    }
    return pos;
}

float Model::getScalingFactorY(float y) {
    float diff = getMaxPos().y - getMinPos().y;
    return y / diff;
}

size_t Model::getMeshesCount() {
    return mMeshes.size();
}

Mesh *Model::getMesh(size_t i) {
    return &mMeshes[i];
}

Texture &Model::getTexture() {
    return mTexture;
}
}