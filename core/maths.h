//
// Created by Aijo on 2023/1/24.
//

#ifndef BANARENDER_MATHS_H
#define BANARENDER_MATHS_H

#include <cmath>
#include <iostream>
#include "macro.h"

class vec2 {
public:
    vec2();
    vec2(float x, float y);

    float x() const;
    float y() const;
    float& operator[](const int i);
    float operator[](int i) const;

    vec2 operator-() const;
    vec2& operator+=(const vec2 &v);
    vec2& operator*=(const float t);
    vec2& operator/=(const float t);

    // 模长
    float norm() const;
    // 模长平方
    float norm2() const;
private:
    float element[2];
};

class vec3 {
public:
    vec3();
    vec3(float x, float y, float z);

    float x() const;
    float y() const;
    float z() const;
    float& operator[](const int i);
    float operator[](int i) const;

    vec3 operator-() const;
    vec3& operator+=(const vec3 &v);
    vec3& operator*=(const float t);
    vec3& operator/=(const float t);

    // 模长
    float norm() const;
    // 模长平方
    float norm2() const;
private:
    float element[3];
};

class vec4 {
public:
    vec4();
    vec4(float x, float y, float z, float w);

    float x() const;
    float y() const;
    float z() const;
    float w() const;
    float& operator[](const int i);
    float operator[](int i) const;

    vec4& operator*=(const float t);
    vec4& operator/=(const float t);

private:
    float element[4];
};

class mat3 {
public:
    mat3();

    vec3& operator[](int i);
    vec3 operator[](int i) const;
    // 转置
    mat3 transpose() const;
    // 逆矩阵
    mat3 inverse() const;
    // 求逆再转置
    mat3 inverse_transpose() const;
    // 伴随矩阵
    mat3 adjoint() const;
    // 行列式
    float determinant() const;
    // 单位矩阵
    static mat3 identity();

private:
    // 每行一个vec3
    vec3 rows[3];
};

class mat4 {
public:
    mat4();

    vec4& operator[](int i);
    vec4 operator[](int i) const;

    // 转置
    mat4 transpose() const;
    // 逆矩阵
    mat4 inverse() const;
    // 求逆再转置
    mat4 inverse_transpose() const;
    // 余子式
    float minor(const int r, const int c) const;
    // 代数余子式
    float cofactor(const int r, const int c) const;
    // 伴随矩阵
    mat4 adjoint() const;
    // 单位矩阵
    static mat4 identity();

public:
    vec4 rows[4];
};

/*
 * vec2 related functions
 */
std::ostream& operator<<(std::ostream &out, const vec2 &v);
vec2 operator+(const vec2 &u, const vec2 &v);
vec2 operator-(const vec2 &u, const vec2 &v);
vec2 operator*(const vec2 &u, const vec2 &v);
vec2 operator*(double t, const vec2 &v);
vec2 operator*(const vec2 &v, double t);
vec2 operator/(vec2 v, double t);

/* vec3 related functions */
std::ostream& operator<<(std::ostream &out, const vec3 &v);
vec3 to_vec3(const vec4 &u);
vec3 operator+(const vec3 &u, const vec3 &v);
vec3 operator-(const vec3 &u, const vec3 &v);
vec3 operator*(const vec3 &u, const vec3 &v);
vec3 operator*(double t, const vec3 &v);
vec3 operator*(const vec3 &v, double t);
vec3 operator/(vec3 v, double t);
double dot(const vec3 &u, const vec3 &v);
vec3 cross(const vec3 &u, const vec3 &v);
vec3 normlize(const vec3 &v);
vec3 cwise_product(const vec3& a, const vec3& b);

/* vec4 related functions */
std::ostream& operator<<(std::ostream &out, const vec4 &v);
vec4 to_vec4(const vec3 &u, float w);
vec4 operator-(const vec4 &u, const vec4 &v);
vec4 operator+(const vec4 &u, const vec4 &v);
vec4 operator*(double t, const vec4 &v);
vec4 operator*(const vec4 &v, double t);

/* mat related functions */
std::ostream& operator<<(std::ostream &out, const mat3 &m);
std::ostream& operator<<(std::ostream &out, const mat4 &m);
vec4 operator*(const mat4 &m, const vec4 v);
mat4 operator*(const mat4 &m1, const mat4 &m2);

/* transformation related functions */
mat4 mat4_translate(float tx, float ty, float tz);
mat4 mat4_scale(float sx, float sy, float sz);
mat4 mat4_rotate_x(float angle);
mat4 mat4_rotate_y(float angle);
mat4 mat4_rotate_z(float angle);
mat4 mat4_lookat(vec3 eye, vec3 target, vec3 up);
mat4 mat4_ortho(float left, float right, float bottom, float top, float near, float far);
mat4 mat4_perspective(float fovy, float aspect, float near, float far);
vec3 viewport_transform(int width, int height, vec3 ndc_coord);

/* untility functions */
template <typename T>
T lerp(const T& start, const T& end, float alpha);
#endif //BANARENDER_MATHS_H
