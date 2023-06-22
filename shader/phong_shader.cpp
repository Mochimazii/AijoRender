//
// Created by Aijo on 2023/1/26.
//
#include "./shader.h"


shader_struct_v2f PhongShader::vertex_shader(shader_struct_a2v *a2v) {
    shader_struct_v2f v2f;
    v2f.clip_pos = ObjectToClipPos(a2v->obj_pos);
    v2f.world_pos = ObjectToWorldPos(a2v->obj_pos);
    v2f.world_normal = ObjectToWorldNormal(a2v->obj_normal);
    v2f.uv = a2v->uv;
    return v2f;
}

vec3 PhongShader::fragment_shader(shader_struct_v2f *v2f) {
    auto clip_coords = v2f->clip_pos;
    auto world_pos = v2f->world_pos;
    auto normal = v2f->world_normal;
    auto uv = v2f->uv;

    // get ka,ks,kd
    vec3 ka(0.35, 0.35, 0.35);
    vec3 kd = tex_diffuse(uv);
    vec3 ks(0.8, 0.8, 0.8);

    // set light information
    float p = 150.0;
    // 光线方向
    vec3 l = normlize(shader_payload.light_Pos);
    // 光源信息
    vec3 light_ambient_intensity = kd;
    vec3 light_diffuse_intensity = vec3(0.9, 0.9, 0.9);
    vec3 light_specular_intensity = vec3(0.15, 0.15, 0.15);

    // calculate shading color in world space
    // the light simulates directional light here, you can modify to point light or spoit light
    // refer to: https://learnopengl.com/Lighting/Light-casters
    vec3 result_color(0, 0, 0);
    vec3 ambient, diffuse, specular;
    normal = normlize(normal);
    vec3 v = normlize(shader_payload.view_Pos - world_pos);
    vec3 h = normlize(l + v);

    ambient = cwise_product(ka, light_ambient_intensity) ;
    diffuse = cwise_product(kd, light_diffuse_intensity) * std::max(0.0, dot(l, normal));
    specular = cwise_product(ks, light_specular_intensity) * std::max(0.0, pow(dot(normal, h), p));

    result_color = (ambient + diffuse + specular);
    return result_color * 255.f;
}
