//
// Created by Aijo on 2023/1/26.
//

#include "pipeline.h"

/**
 * 屏幕空间求重心坐标
 * uAC + vAB + PA = 0
 * @param A
 * @param B
 * @param C
 * @param P
 * @return 分别为 A, B, C前的系数
 */
static vec3 compute_barycentric(vec2 A, vec2 B, vec2 C, vec2 P) {
    vec3 s[2];
    for (int i=2; i--; ) {
        s[i][0] = C[i]-A[i];
        s[i][1] = B[i]-A[i];
        s[i][2] = A[i]-P[i];
    }
    vec3 u = cross(s[0], s[1]);// u.x是AC系数, u.y是AB系数
    if (std::abs(u[2])>1e-2) // A, B, C系数
        return vec3(1.f-(u.x()+u.y())/u.z(), u.y()/u.z(), u.x()/u.z());
    return vec3(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

static float interpolate_depth(float A_depth, float B_depth, float C_depth, vec3 weights) {
    return A_depth * weights[0] + B_depth * weights[1] + C_depth * weights[2];
}

static void interpolate_varyings(payload_t &v2f, vec3 barycentric) {
    vec4 *clip_coords = v2f.clipcoord_attri;
    vec3 *world_coords = v2f.worldcoord_attri;
    vec3 *normals = v2f.normal_attri;
    vec2 *uvs = v2f.uv_attri;

    float Z = 1.0 / (barycentric.x() / clip_coords[0].w() + barycentric.y() / clip_coords[1].w() + barycentric.z() / clip_coords[2].w());
    vec3 normal = (barycentric.x()*normals[0] / clip_coords[0].w() + barycentric.y() * normals[1] / clip_coords[1].w() +
                   barycentric.z() * normals[2] / clip_coords[2].w()) * Z;
    vec2 uv = (barycentric.x()*uvs[0] / clip_coords[0].w() + barycentric.y() * uvs[1] / clip_coords[1].w() +
               barycentric.z() * uvs[2] / clip_coords[2].w()) * Z;
    vec3 worldpos = (barycentric.x()*world_coords[0] / clip_coords[0].w() + barycentric.y() * world_coords[1] / clip_coords[1].w() +
                     barycentric.z() * world_coords[2] / clip_coords[2].w()) * Z;
    return;
}

void draw_triangles(DrawData &drawData) {
    for (int i = 0; i < drawData.model.faceSize(); ++i) {
        for (int j = 0; j < 3; ++j) {
            drawData.shader->vertex_shader(i, j);
        }
        rasterize(drawData.shader->payload.clipcoord_attri, drawData);
    }
}

void rasterize(vec4 *clipcoord_attri, DrawData &drawData) {
    vec3 ndc_coords[3];
    vec3 screen_coords[3];
    auto &render_buffer = drawData.render_buffer;
    // 齐次除法
    for (int i = 0; i < 3; ++i) {
        ndc_coords[i][0] = clipcoord_attri[i][0] / clipcoord_attri[i].w();
        ndc_coords[i][1] = clipcoord_attri[i][1] / clipcoord_attri[i].w();
        ndc_coords[i][2] = clipcoord_attri[i][2] / clipcoord_attri[i].w();
    }

    // 视口变换
    for (int i = 0; i < 3; ++i) {
        screen_coords[i][0] = 0.5*(render_buffer.width-1)*(ndc_coords[i][0] + 1.0);
        screen_coords[i][1] = 0.5*(render_buffer.height-1)*(ndc_coords[i][1] + 1.0);
        screen_coords[i][2] = clipcoord_attri[i].w();	//view space z-value
    }

    // set bounding box
    vec2 bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    vec2 bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    vec2 clamp(render_buffer.width - 1, render_buffer.height - 1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            bboxmin[j] = std::max(0.f, std::min(bboxmin[j], screen_coords[i][j]));
            bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], screen_coords[i][j]));
        }
    }

    vec2 Pixel;
    for (Pixel[0] = (int)bboxmin.x(); Pixel[0] <= (int)bboxmax.x(); ++Pixel[0]) {
        for (Pixel[1] = (int)bboxmin.y(); Pixel[1] <= (int)bboxmax.y(); ++Pixel[1]) {
            vec2 A = vec2(screen_coords[0].x(), screen_coords[0].y());
            vec2 B = vec2(screen_coords[1].x(), screen_coords[1].y());
            vec2 C = vec2(screen_coords[2].x(), screen_coords[2].y());
            vec3 barycentric = compute_barycentric(A, B, C, Pixel);
            if (barycentric.x() < 0 || barycentric.y() < 0 || barycentric.z() < 0) continue;

            // 深度插值
            float frag_depth = interpolate_depth(screen_coords[0].z(), screen_coords[1].z(), screen_coords[2].z(), barycentric);

            // 深度测试
            if (frag_depth > render_buffer.get_depth(Pixel.x(), Pixel.y())) {
                // 变量插值
                interpolate_varyings(drawData.shader->payload, barycentric);
                // fragment shader
                vec3 color = drawData.shader->fragment_shader(barycentric.x(), barycentric.y(), barycentric.z());
                // 绘制像素
                render_buffer.set_depth(Pixel.x(), Pixel.y(), frag_depth);
                render_buffer.set_color(Pixel.x(), Pixel.y(), color);
            }
        }
    }
}
