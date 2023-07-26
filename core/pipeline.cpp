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

static shader_struct_v2f interpolate_varyings(shader_struct_v2f* v2f, vec3 barycentric) {
    // todo:透视矫正插值
    shader_struct_v2f ret;
    float recip_w[3];
    /* reciprocals of w */
    for (int i = 0; i < 3; i++) {
        recip_w[i] = barycentric[i] / v2f[i].clip_pos[3];
    }
    float Z_n = 1. / (recip_w[0] + recip_w[1] + recip_w[2]);
    for (int i = 0; i < 3; ++i)
    {
        //求正确透视下插值的系数
        recip_w[i] *= Z_n;
    }
    barycentric = {recip_w[0], recip_w[1], recip_w[2]};
    ret.world_pos = v2f[0].world_pos * barycentric.x() + v2f[1].world_pos * barycentric.y() +v2f[2].world_pos * barycentric.z();
    ret.world_normal = v2f[0].world_normal * barycentric.x() + v2f[1].world_normal * barycentric.y() +v2f[2].world_normal * barycentric.z();
    ret.uv = v2f[0].uv * barycentric.x() + v2f[1].uv * barycentric.y() + v2f[2].uv * barycentric.z();
    return ret;
}

void draw_triangles(Scene& scene) {
    for (int x = 0; x < scene.modelSize(); ++x) {
        scene.set_model_sample2D(x);
        Model& currentModel = scene.model(x);
        // 三角形各个点的 v2f
        shader_struct_v2f v2fs[3];
        for (int i = 0; i < currentModel.faceSize(); ++i) {
            for (int j = 0; j < 3; ++j) {
                shader_struct_a2v a2v;
                a2v.obj_pos = currentModel.vert(i,j);
                a2v.obj_normal = currentModel.normal(i,j);
                a2v.uv = currentModel.uv(i,j);
                v2fs[j] = scene.get_shader()->vertex_shader(&a2v);
            }

            rasterize(scene, v2fs);
        }
    }
}

void rasterize(Scene &scene, shader_struct_v2f *v2fs) {

    auto &render_buffer = scene.get_render_buffer();
    // 齐次除法 x,y,z 坐标转换至 -1 -> 1
    vec3 ndc_coords[3];
    for (int i = 0; i < 3; ++i) {
        ndc_coords[i][0] = v2fs[i].clip_pos.x() / v2fs[i].clip_pos.w();
        ndc_coords[i][1] = v2fs[i].clip_pos.y() / v2fs[i].clip_pos.w();;
        ndc_coords[i][2] = v2fs[i].clip_pos.z() / v2fs[i].clip_pos.w();;
    }

    // 视口变换
    vec3 screen_coords[3];
    for (int i = 0; i < 3; ++i) {
        screen_coords[i] = viewport_transform(render_buffer.width, render_buffer.height, ndc_coords[i]);
    }
//    for (int i = 0; i < 3; ++i) {
//        screen_coords[i][2] = v2fs[i].clip_pos.w();
//    }

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
                //interpolate_varyings(drawData.shader->payload, barycentric);
                shader_struct_v2f interpolate_v2f = interpolate_varyings(v2fs, barycentric);
                // fragment shader
                //vec3 color = drawData.shader->fragment_shader(barycentric.x(), barycentric.y(), barycentric.z());
                vec3 color = scene.get_shader()->fragment_shader(&interpolate_v2f);
                // 绘制像素
                render_buffer.set_depth(Pixel.x(), Pixel.y(), frag_depth);
                render_buffer.set_color(Pixel.x(), Pixel.y(), color);
            }
        }
    }
}


