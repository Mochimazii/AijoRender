//
// Created by Aijo on 2023/1/24.
//

#include "maths.h"
#include "cassert"

/* vec2 class member functions */
vec2::vec2() : element{ 0,0 } {}
vec2::vec2(float x, float y) : element{ x,y} {}
float vec2::x() const { return element[0]; }
float vec2::y() const { return element[1]; }
vec2 vec2::operator-() const { return vec2(-element[0], -element[1]); }
float vec2::operator[](int i) const { return element[i]; }
float& vec2::operator[](int i) { return element[i]; }
vec2& vec2::operator+=(const vec2 &v) { element[0] += v[0]; element[1] += v[1]; return *this; }
vec2& vec2::operator*=(const float t) { element[0] *= t; element[1] *= t;  return *this; }
vec2& vec2::operator/=(const float t) { return *this *= 1 / t; }
float vec2::norm2() const { return element[0] * element[0] + element[1] * element[1]; }
float vec2::norm() const { return sqrt(norm2()); }

/* vec2 related functions */
std::ostream& operator<<(std::ostream &out, const vec2 &v)
{
    return out << v.x() << ' ' << v.y() ;
}

vec2 operator+(const vec2 &u, const vec2 &v)
{
    return vec2(u.x() + v.x(), u.y() + v.y());
}

vec2 operator-(const vec2 &u, const vec2 &v)
{
    return vec2(u.x() - v.x(), u.y() - v.y());
}

vec2 operator*(const vec2 &u, const vec2 &v)
{
    return vec2(u.x() * v.x(), u.y() * v.y());
}

vec2 operator*(double t, const vec2 &v)
{
    return vec2(t*v.x(), t*v.y());
}

vec2 operator*(const vec2 &v, double t)
{
    return t * v;
}

vec2 operator/(vec2 v, double t)
{
    return (1 / t) * v;
}

/* vec3 class member functions */
vec3::vec3() : element{ 0,0,0 } {}
vec3::vec3(float x, float y, float z) : element{ x,y,z } {}
float vec3::x() const { return element[0]; }
float vec3::y() const { return element[1]; }
float vec3::z() const { return element[2]; }
vec3 vec3::operator-() const { return vec3(-element[0], -element[1], -element[2]); }
float vec3::operator[](int i) const { return element[i]; }
float& vec3::operator[](int i) { return element[i]; }
vec3& vec3::operator+=(const vec3 &v) { element[0] += v[0]; element[1] += v[1]; element[2] += v[2]; return *this; }
vec3& vec3::operator*=(const float t) { element[0] *= t; element[1] *= t; element[2] *= t; return *this; }
vec3& vec3::operator/=(const float t){	return *this *= 1 / t;}
float vec3::norm2() const{	return element[0] * element[0] + element[1] * element[1] + element[2] * element[2];}
float vec3::norm() const{	return sqrt(norm2());}

/* vec3 related functions */
std::ostream& operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

vec3 operator*(double t, const vec3 &v)
{
    return vec3(t*v.x(), t*v.y(), t*v.z());
}

vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}

double dot(const vec3 &u, const vec3 &v)
{
    return u.x() * v.x()
           + u.y() * v.y()
           + u.z() * v.z();
}

vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

vec3 normlize(const vec3 &v)
{
    return v / v.norm();
}

vec3 cwise_product(const vec3& a, const vec3& b)
{
    return vec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
}

/* vec4 class member functions */
vec4::vec4() : element{ 0,0,0,0 } {}
vec4::vec4(float x, float y, float z, float w) : element{ x,y,z,w } {}
float vec4::x() const { return element[0]; }
float vec4::y() const { return element[1]; }
float vec4::z() const { return element[2]; }
float vec4::w() const { return element[3]; }
float vec4::operator[](int i) const { return element[i]; }
float& vec4::operator[](int i) { return element[i]; }
vec4& vec4::operator*=(const float t) { element[0] *= t; element[1] *= t; element[2] *= t; element[3] *= t; return *this; }
vec4& vec4::operator/=(const float t) { return *this *= 1 / t; }

/* vec4 related functions */
vec4 to_vec4(const vec3 &u, float w)
{
    return vec4(u[0], u[1], u[2], w);
}

std::ostream& operator<<(std::ostream &out, const vec4 &v)
{
    return out << v[0] << " " << v[1] << " " << v[2] << " " << v[3];
}

vec4 operator-(const vec4 &u, const vec4 &v)
{
    return vec4(u.x() - v.x(), u.y() - v.y(), u.z() - v.z(), u.w()-v.w());
}

vec4 operator+(const vec4 &u, const vec4 &v)
{
    return vec4(u.x() + v.x(), u.y() + v.y(), u.z() + v.z(), u.w() + v.w());
}

vec4 operator*(double t, const vec4 &v)
{
    return vec4(t*v.x(), t*v.y(), t*v.z(),t*v.w());
}

vec4 operator*(const vec4 &v, double t)
{
    return t * v;
}

/* mat3 class member functions */
mat3::mat3() {}
vec3 mat3::operator[](int i)const { return rows[i]; }
vec3& mat3::operator[](int i) { return rows[i]; }

/*
 * for matrix's determinant, adjoint, and inverse
 * ref: 3D Math Primer for Graphics and Game Development, 2nd Edition, Chapter 6
 */
float mat3::determinant() const {
    auto m = this->rows;
    float a = +m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
    float b = -m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
    float c = +m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    return a + b + c;
}

mat3 mat3::adjoint() const {
    auto m = this->rows;
    mat3 adjoint;
    adjoint[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]);
    adjoint[0][1] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);
    adjoint[0][2] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]);
    adjoint[1][0] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]);
    adjoint[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]);
    adjoint[1][2] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]);
    adjoint[2][0] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]);
    adjoint[2][1] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]);
    adjoint[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]);
    return adjoint;
}

mat3 mat3::identity() {
    mat3 mat;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            mat[i][j] = (i == j);
    return mat;
}

mat3 mat3::transpose() const {
    mat3 transpose;
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            transpose[i][j] = rows[j][i];
    return transpose;
}

mat3 mat3::inverse_transpose() const {
    int i, j;
    mat3 inverse_transpose, adjoint;
    float determinant, inv_determinant;

    adjoint = this->adjoint();
    determinant = this->determinant();
    inv_determinant = 1 / determinant;

    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            inverse_transpose[i][j] = adjoint[i][j] * inv_determinant;

    return inverse_transpose;
}

mat3 mat3::inverse() const {
    return ((*this).inverse_transpose()).transpose();
}

std::ostream& operator<<(std::ostream &out, const mat3 &m)
{
    return out << m[0] << "\n" << m[1] << "\n" << m[2];
}

/* mat4 class member functions */
mat4::mat4() {}
vec4 mat4::operator[](int i)const {	return rows[i];}
vec4& mat4::operator[](int i) {	return rows[i];}

mat4 mat4::transpose() const {
    mat4 transpose;
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            transpose[i][j] = rows[j][i];
    return transpose;
}

mat4 mat4::inverse() const {
    return ((*this).inverse_transpose()).transpose();
}

mat4 mat4::inverse_transpose() const {
    int i, j;
    float determinant, inv_determinant;
    mat4 adjoint, inverse_transpose;

    adjoint = this->adjoint();
    determinant = 0;
    for (i = 0; i < 4; i++)
    {
        determinant += rows[0][i] * adjoint[0][i];
    }
    inv_determinant = 1 / determinant;

    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            inverse_transpose[i][j] = adjoint[i][j] * inv_determinant;

    return inverse_transpose;
}

float mat4::minor(const int r, const int c) const {
    mat3 cut_down;
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            int row = i < r ? i : i + 1;
            int col = j < c ? j : j + 1;
            cut_down[i][j] = this->rows[row][col];
        }
    }
    return cut_down.determinant();
}

float mat4::cofactor(const int r, const int c) const {
    float sign = (r + c) % 2 == 0 ? 1.0f : -1.0f;
    float minor = this->minor(r, c);
    return sign * minor;
}

mat4 mat4::adjoint() const {
    mat4 adjoint;
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            adjoint[i][j] = this->cofactor(i, j);
    return adjoint;
}

mat4 mat4::identity() {
    mat4 mat;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            mat[i][j] = (i == j);
    return mat;
}

std::ostream& operator<<(std::ostream &out, const mat4 &m)
{
    return out << m[0] << "\n" << m[1] << "\n" << m[2] << "\n" << m[3];
}

vec4 operator*(const mat4 &m, const vec4 v)
{
    float product[4];
    int i;
    for (i = 0; i < 4; i++)
    {
        float a = m[i][0] * v[0];
        float b = m[i][1] * v[1];
        float c = m[i][2] * v[2];
        float d = m[i][3] * v[3];
        product[i] = a + b + c + d;
    }
    return vec4(product[0], product[1], product[2], product[3]);
}

mat4 operator*(const mat4 &m1, const mat4 &m2)
{
    mat4 m;
    int i, j, k;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            for (k = 0; k < 4; k++)
                m[i][j] += m1[i][k] * m2[k][j];
    return m;
}

/**
 *  1  0  0 tx
 *  0  1  0 ty
 *  0  0  1 tz
 *  0  0  0  1
 *
 * @param tx 沿x轴平移的距离
 * @param ty 沿y轴平移的距离
 * @param tz 沿z轴平移的距离
 * @return 用来左乘的平移矩阵
 */
mat4 mat4_translate(float tx, float ty, float tz) {
    mat4 m = mat4().identity();
    m.rows[0][3] = tx;
    m.rows[1][3] = ty;
    m.rows[2][3] = tz;
    return m;
}

/**
 * sx  0  0  0
 *  0 sy  0  0
 *  0  0 sz  0
 *  0  0  0  1
 *
 * @param sx 沿x轴放大的比例
 * @param sy 沿y轴放大的比例
 * @param sz 沿z轴放大的比例
 * @return 用来左乘的缩放矩阵
 */
mat4 mat4_scale(float sx, float sy, float sz) {
    mat4 m = mat4().identity();
    assert(sx != 0 && sy != 0 && sz != 0);
    m.rows[0][0] = sx;
    m.rows[1][1] = sy;
    m.rows[2][2] = sz;
    return m;
}

/**
 *  1  0  0  0
 *  0  c -s  0
 *  0  s  c  0
 *  0  0  0  1
 *
 * @param angle 逆时针旋转弧度
 * @return 用于左乘的绕x轴旋转的矩阵
 */
mat4 mat4_rotate_x(float angle) {
    float c = (float)cos(angle);
    float s = (float)sin(angle);
    mat4 m = mat4().identity();
    m.rows[1][1] = c;
    m.rows[1][2] = -s;
    m.rows[2][1] = s;
    m.rows[2][2] = c;
    return m;
}

/**
 *  c  0  s  0
 *  0  1  0  0
 * -s  0  c  0
 *  0  0  0  1
 *
 * @param angle 逆时针旋转弧度
 * @return 用于左乘的绕y轴旋转的矩阵
 */
mat4 mat4_rotate_y(float angle) {
    float c = (float)cos(angle);
    float s = (float)sin(angle);
    mat4 m = mat4().identity();
    m.rows[0][0] = c;
    m.rows[0][2] = s;
    m.rows[2][0] = -s;
    m.rows[2][2] = c;
    return m;
}

/**
 *  c -s  0  0
 *  s  c  0  0
 *  0  0  1  0
 *  0  0  0  1
 *
 * @param angle 逆时针旋转弧度
 * @return 用于左乘的绕z轴旋转的矩阵
 */
mat4 mat4_rotate_z(float angle) {
    float c = (float)cos(angle);
    float s = (float)sin(angle);
    mat4 m = mat4().identity();
    m.rows[0][0] = c;
    m.rows[0][1] = -s;
    m.rows[1][0] = s;
    m.rows[1][1] = c;
    return m;
}

/**
 * x_axis.x  x_axis.y  x_axis.z  -dot(x_axis,eye)
 * y_axis.x  y_axis.y  y_axis.z  -dot(y_axis,eye)
 * z_axis.x  z_axis.y  z_axis.z  -dot(z_axis,eye)
 *        0         0         0                 1
 *
 * @param eye 摄像机位置向量
 * @param target 摄像机指向的目标的位置向量
 * @param up 摄像机上方位置向量
 * @return 用于左乘的 世界空间->摄像机空间 矩阵
 *
 * z_axis: normalize(eye-target), the backward vector
 * x_axis: normalize(cross(up,z_axis)), the right vector
 * y_axis: cross(z_axis,x_axis), the up vector
 */
mat4 mat4_lookat(vec3 eye, vec3 target, vec3 up) {
    //
    vec3 z_axis = normlize((eye - target));
    vec3 x_axis = normlize(cross(up, z_axis));
    vec3 y_axis = cross(z_axis, x_axis);
    mat4 m = mat4::identity();

    m.rows[0][0] = x_axis.x();
    m.rows[0][1] = x_axis.y();
    m.rows[0][2] = x_axis.z();

    m.rows[1][0] = y_axis.x();
    m.rows[1][1] = y_axis.y();
    m.rows[1][2] = y_axis.z();

    m.rows[2][0] = z_axis.x();
    m.rows[2][1] = z_axis.y();
    m.rows[2][2] = z_axis.z();

    m.rows[0][3] = -dot(x_axis, eye);
    m.rows[1][3] = -dot(y_axis, eye);
    m.rows[2][3] = -dot(z_axis, eye);

    return m;
}

/*
 * left, right: the coordinates for the left and right clipping planes
 * bottom, top: the coordinates for the bottom and top clipping planes
 * near, far: the coordinates for the near and far clipping planes
 *
 * 2/(r-l)        0         0  -(r+l)/(r-l)
 *       0  2/(t-b)         0  -(t+b)/(t-b)
 *       0        0   2/(n-f)  -(f+n)/(n-f)
 *       0        0         0             1
 * see http://docs.gl/gl2/glOrtho
 *
 * note: opgenl map the near plane to -1, far plane to 1,
 *       but i map the near plane to 1, far plane to -1.
 *       And if near and far is positive it means the plane is behind viewer.
 */
mat4 mat4_ortho(float left, float right, float bottom, float top, float near, float far) {
    float x_range = right - left;
    float y_range = top - bottom;
    float z_range = near - far;
    mat4 m = mat4::identity();
    m[0][0] = 2 / x_range;
    m[1][1] = 2 / y_range;
    m[2][2] = 2 / z_range;
    m[0][3] = -(left + right) / x_range;
    m[1][3] = -(bottom + top) / y_range;
    m[2][3] = -(near + far) / z_range;
    return m;
}


/*
 * fovy: the field of view angle in the y direction, in degrees
 * aspect: the aspect ratio, defined as width divided by height
 * near, far: the coordinates for the near and far clipping planes
 *
 * 1/(aspect*tan(fovy/2))              0             0           0
 *                      0  1/tan(fovy/2)             0           0
 *                      0              0  -(f+n)/(f-n)  -2fn/(f-n)
 *                      0              0            -1           0
 *
 * this is the same as
 *     float half_h = near * (float)tan(fovy / 2);
 *     float half_w = half_h * aspect;
 *     mat4_frustum(-half_w, half_w, -half_h, half_h, near, far);
 *
 * see http://www.songho.ca/opengl/gl_projectionmatrix.html
 *
 * note: my implementation is based on right-handed system, so it is a little different
 */
mat4 mat4_perspective(float fovy, float aspect, float near, float far) {
    mat4 m = mat4::identity();
    fovy = fovy / 180.0 * PI;
    float t = fabs(near) * tan(fovy / 2);
    float r = aspect * t;

    m[0][0] = near / r;
    m[1][1] = near / t;
    m[2][2] = (near+far)/(near-far);
    m[2][3] = 2*near*far / (far-near);
    m[3][2] = 1;
    m[3][3] = 0;
    return m;
}

template<typename T>
T lerp(const T &start, const T &end, float alpha) {
    return start + (end - start) * alpha;
}

