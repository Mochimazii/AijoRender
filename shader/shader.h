//
// Created by Aijo on 2023/1/26.
//

#ifndef BANARENDER_SHADER_H
#define BANARENDER_SHADER_H

#include "../core/macro.h"
#include "../core/maths.h"
#include "../core/model.h"
#include "../core/camera.h"

struct shader_struct_a2v {
    vec3 obj_pos;
    vec3 obj_normal;
    vec2 uv;
};
// vertex shader -> fragment shader
struct shader_struct_v2f {
    vec4 clip_pos;
    vec3 world_pos;
    vec3 world_normal;
    vec2 uv;
};

typedef struct {
    // sample 2D
    TGAImage diffuse_map;
    TGAImage normal_map;
    TGAImage specular_map;

    vec3 view_Pos;
    vec3 light_Pos;
    mat4 model_matrix;
    mat4 view_matrix;
    mat4 projection_matrix;
    mat4 mvp_matrix;
}shader_payload;

class Shader {
public:
    shader_payload shader_payload;

    Shader() {}

    virtual void vertex_shader(int nfaces, int nvertex) {}
    virtual vec3 fragment_shader(float alpha, float beta, float gamma) { return vec3(0,0,0);}
    virtual shader_struct_v2f vertex_shader(shader_struct_a2v* a2v) = 0;
    virtual vec3 fragment_shader(shader_struct_v2f* v2f) { return vec3(0,0,0);}

    vec4 ObjectToClipPos(vec3 pos) {
        return shader_payload.mvp_matrix * to_vec4(pos, 1.f);
    }

    vec3 ObjectToWorldPos(vec3 pos) {
        return to_vec3(shader_payload.model_matrix * to_vec4(pos, 1.f));
    }
    // ∑®œﬂæÿ’Û
    vec3 ObjectToWorldNormal(vec3 normal) {
        mat4 normal_mat = shader_payload.model_matrix.inverse().transpose();
        return to_vec3(normal_mat * to_vec4(normal, 1.f));
    }

    vec3 tex_diffuse(vec2 uv) {
        TGAImage &tex = shader_payload.diffuse_map;
        uv[0] = fmod(uv[0], 1);
        uv[1] = fmod(uv[1], 1);
        int uv0 = uv[0] * tex.get_width();
        int uv1 = uv[1] * tex.get_height();
        TGAColor c = tex.get(uv0, uv1);
        vec3 res;
        for (int i = 0; i < 3; i++)
            res[2 - i] = (float)c[i] / 255.f;
        return res;
    }
};

class PhongShader:public Shader
{
public:
    shader_struct_v2f vertex_shader(shader_struct_a2v* a2v) override;
    vec3 fragment_shader(shader_struct_v2f* v2f) override;
};
#endif //BANARENDER_SHADER_H
