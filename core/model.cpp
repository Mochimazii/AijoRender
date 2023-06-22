//
// Created by Aijo on 2023/1/25.
//

#include "model.h"
#include <io.h>
#include <iostream>
#include <fstream>
#include <sstream>

Model::Model(const char *filename) {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()){
        printf("load model failed\n");
        return;
    }

    std::string line;
    while (!in.eof()){
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")){
            iss >> trash;
            vec3 v;
            for (int i = 0; i < 3; ++i) {
                iss >> v[i];
            }
            verts.push_back(v);
        }
        else if (!line.compare(0, 3, "vn "))
        {
            iss >> trash >> trash;
            vec3 n;
            for (int i = 0; i < 3; i++)
                iss >> n[i];

            norms.push_back(n);
        }
        else if (!line.compare(0, 3, "vt "))
        {
            iss >> trash >> trash;
            vec2 uv;
            for (int i = 0; i < 2; i++)
                iss >> uv[i];

            uvs.push_back(uv);
        }
        else if (!line.compare(0, 2, "f "))
        {
            std::vector<vec3> f;
            vec3 tmp;
            iss >> trash;
            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2])
            {
                for (int i = 0; i < 3; i++)
                    tmp[i]--; // in wavefront obj all indices start at 1, not zero

                f.push_back(tmp);
            }
            faces.push_back(f);
        }
    }
    std::cerr << "# v# " << verts.size() << " f# "  << faces.size() << " vt# " << uvs.size() << " vn# " << norms.size() << std::endl;

    create_map(filename);

}

void Model::load_texture(std::string filename, const char *suffix, TGAImage &img) {
    std::string texturefile(filename);
    size_t dot = texturefile.find_last_of(".");
    if (dot != std::string::npos){
        texturefile = texturefile.substr(0, dot) + std::string(suffix);
        img.read_tga_file(texturefile.c_str());
        img.flip_vertically();
    }
}

void Model::create_map(const char *filename) {
    std::string texturefile(filename);
    size_t dot = texturefile.find_last_of(".");

    texturefile = texturefile.substr(0, dot) + std::string("_diffuse.tga");
    if (_access(texturefile.data(), 0) != -1){
        diffusemap = TGAImage();
        load_texture(filename, "_diffuse.tga", diffusemap);
    }

    texturefile = texturefile.substr(0, dot) + std::string("_normal.tga");
    if (_access(texturefile.data(), 0) != -1)
    {
        normalmap = TGAImage();
        load_texture(filename, "_normal.tga", normalmap);
    }

    texturefile = texturefile.substr(0, dot) + std::string("_spec.tga");
    if (_access(texturefile.data(), 0) != -1)
    {
        specularmap = TGAImage();
        load_texture(filename, "_spec.tga", specularmap);
    }
}

int Model::vertSize() {
    return this->verts.size();
}

int Model::faceSize() {
    return this->faces.size();
}

vec3 Model::vert(int i)
{
    return verts[i];
}

vec3 Model::vert(int iface, int nthvert)
{
    return verts[faces[iface][nthvert].x()];
}

vec3 Model::normal(int faceIndex, int nthvert) {
    return norms[faces[faceIndex][nthvert].z()];
}

vec3 Model::normal(vec2 uv) {
    uv[0] = fmod(uv[0], 1);
    uv[1] = fmod(uv[1], 1);
    int uv0 = uv[0] * normalmap.get_width();
    int uv1 = uv[1] * normalmap.get_height();
    TGAColor c = normalmap.get(uv0, uv1);
    vec3 res;
    for (int i = 0; i < 3; i++)
        res[2 - i] = (float)c[i] / 255.f*2.f - 1.f; //because the normap_map coordinate is -1 ~ +1
    return res;
}

vec2 Model::uv(int faceIndex, int nthvert) {
    return uvs[faces[faceIndex][nthvert].y()];
}

vec3 Model::diffuse(vec2 uv) {
    uv[0] = fmod(uv[0], 1);
    uv[1] = fmod(uv[1], 1);
    int uv0 = uv[0] * diffusemap.get_width();
    int uv1 = uv[1] * diffusemap.get_height();
    TGAColor c = diffusemap.get(uv0, uv1);
    vec3 res;
    for (int i = 0; i < 3; i++)
        res[2 - i] = (float)c[i] / 255.f;
    return res;
}

float Model::specular(vec2 uv) {
    int uv0 = uv[0] * specularmap.get_width();
    int uv1 = uv[1] * specularmap.get_height();
    return specularmap.get(uv0, uv1)[0] / 1.f;
}

TGAImage &Model::diffuse_map() {
    return this->diffusemap;
}

TGAImage &Model::normal_map() {
    return this->normalmap;
}

TGAImage &Model::specular_map() {
    return this->specularmap;
}
