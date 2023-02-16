//
// Created by Aijo on 2023/1/26.
//

#ifndef BANARENDER_SHADER_H
#define BANARENDER_SHADER_H

#include "../core/macro.h"
#include "../core/maths.h"
#include "../core/model.h"
#include "../core/camera.h"

typedef struct {
    Camera camera;
    Model model;

    // local space --> world space
    mat4 model_matrix;
    // world space --> view space
    mat4 camera_view_matrix;
    // view space --> clip space
    mat4 camera_perp_matrix;
    // local space --> clip space
    mat4 mvp_matrix;

    // vertex attribute
    vec3 normal_attri[3];
    vec2 uv_attri[3];
    vec3 worldcoord_attri[3];
    vec4 clipcoord_attri[3];
}payload_t;

class Shader {
public:
    payload_t payload;

    Shader() {}

    virtual void vertex_shader(int nfaces, int nvertex) {}
    virtual vec3 fragment_shader(float alpha, float beta, float gamma) { return vec3(0,0,0);}
};

class PhongShader:public Shader
{
public:
    void vertex_shader(int nfaces, int nvertex);
    vec3 fragment_shader(float alpha, float beta, float gamma);

};
#endif //BANARENDER_SHADER_H
