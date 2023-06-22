//
// Created by Aijo on 2023/1/25.
//

#ifndef BANARENDER_MODEL_H
#define BANARENDER_MODEL_H
#include <string>
#include <vector>

#include "maths.h"
#include "tgaimage.h"

class Model {
private:
    std::vector<vec3> verts;
    // f 1575/1514/1569 1581/1520/1575 1576/1515/1570
    // f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
    // vec3:顶点索引/纹理坐标索引/法向量索引
    std::vector<std::vector<vec3>> faces;
    std::vector<vec3> norms;
    std::vector<vec2> uvs;
    // map
    TGAImage diffusemap;
    TGAImage normalmap;
    TGAImage specularmap;

    void load_texture(std::string filename, const char *suffix, TGAImage &img);
    void create_map(const char *filename);
public:
    Model() = default;
    Model(const char *filename);
    /* 模型基础信息 */
    int vertSize();
    int faceSize();
    // 模型的法线信息
    vec3 normal(int faceIndex, int nthvert);
    vec3 vert(int i);
    vec3 vert(int faceIndex, int nthvert);
    vec2 uv(int faceIndex, int nthvert);
    std::vector<vec3> face(int index);

    /* 贴图信息 */
    TGAImage& diffuse_map();
    TGAImage& normal_map();
    TGAImage& specular_map();
    vec3 normal(vec2 uv);
    vec3 diffuse(vec2 uv);
    float specular(vec2 uv);

};


#endif //BANARENDER_MODEL_H
