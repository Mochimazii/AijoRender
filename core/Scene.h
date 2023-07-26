//
// Created by 59741 on 2023/2/19.
//

#ifndef BANARENDER_SCENE_H
#define BANARENDER_SCENE_H

#include "model.h"
#include "../shader/shader.h"
#include "renderbuffer.h"
#include "camera.h"
#include <vector>

class Scene {
    std::vector<Model> models;
    Camera camera;
    vec3 light;
    Shader *shader;
    renderbuffer render_buffer;
public:
    Scene() = default;
    Scene(std::vector<Model> models, Camera camera, vec3 light, Shader* currShader, renderbuffer &render_buffer);

    size_t modelSize();
    void set_model_sample2D(size_t model_index);
    Model& model(size_t i);
    Shader* get_shader();
    renderbuffer& get_render_buffer();
    void set_render_buffer(renderbuffer &renderbuffer);

    void tick(Camera &camera);
    // todo
    void draw_call();

};


#endif //BANARENDER_SCENE_H
