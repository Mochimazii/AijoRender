//
// Created by Aijo on 2023/1/26.
//
#include "./shader.h"

void PhongShader::vertex_shader(int nfaces, int nvertex) {
    vec4 temp_vert = to_vec4(payload.model.vert(nfaces, nvertex), 1.0f);
    vec4 temp_normal = to_vec4(payload.model.normal(nfaces, nvertex), 1.0f);
    // TODO:片段着色器里的计算都是在世界空间坐标中进行,法向量没有变换？？？
    payload.uv_attri[nvertex] = payload.model.uv(nfaces, nvertex);
    payload.clipcoord_attri[nvertex] = payload.mvp_matrix * temp_vert;

    for (int i = 0; i < 3; ++i) {
        payload.worldcoord_attri[nvertex][i] = temp_vert[i];
        payload.normal_attri[nvertex][i] = temp_normal[i];
    }
}

vec3 PhongShader::fragment_shader(float alpha, float beta, float gamma) {
    auto clip_coords = payload.clipcoord_attri;
    auto world_coords = payload.worldcoord_attri;
    auto normals = payload.normal_attri;
    auto uvs = payload.uv_attri;

    // interpolate attribute
    float Z = 1.0 / (alpha / clip_coords[0].w() + beta / clip_coords[1].w() + gamma / clip_coords[2].w());
    vec3 normal = (alpha*normals[0] / clip_coords[0].w() + beta * normals[1] / clip_coords[1].w() +
                   gamma * normals[2] / clip_coords[2].w()) * Z;
    vec2 uv = (alpha*uvs[0] / clip_coords[0].w() + beta * uvs[1] / clip_coords[1].w() +
               gamma * uvs[2] / clip_coords[2].w()) * Z;
    vec3 worldpos = (alpha*world_coords[0] / clip_coords[0].w() + beta * world_coords[1] / clip_coords[1].w() +
                     gamma * world_coords[2] / clip_coords[2].w()) * Z;

//    if (payload.model->normalmap)
//        normal = cal_normal(normal, world_coords, uvs, uv, payload.model->normalmap);

    // get ka,ks,kd
    vec3 ka(0.35, 0.35, 0.35);
    vec3 kd = payload.model.diffuse(uv);
    vec3 ks(0.8, 0.8, 0.8);

    // set light information
    float p = 150.0;
    vec3 l = normlize(vec3(1, 1, 1));
    vec3 light_ambient_intensity = kd;
    vec3 light_diffuse_intensity = vec3(0.9, 0.9, 0.9);
    vec3 light_specular_intensity = vec3(0.15, 0.15, 0.15);

    // calculate shading color in world space
    // the light simulates directional light here, you can modify to point light or spoit light
    // refer to: https://learnopengl.com/Lighting/Light-casters
    vec3 result_color(0, 0, 0);
    vec3 ambient, diffuse, specular;
    normal = normlize(normal);
    vec3 v = normlize(payload.camera.eye - worldpos);
    vec3 h = normlize(l + v);

    ambient = cwise_product(ka, light_ambient_intensity) ;
    diffuse = cwise_product(kd, light_diffuse_intensity) * std::max(0.0, dot(l, normal));
    specular = cwise_product(ks, light_specular_intensity) * std::max(0.0, pow(dot(normal, h), p));

    result_color = (ambient + diffuse + specular);
    return result_color * 255.f;
}