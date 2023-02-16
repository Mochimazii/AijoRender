#include <vector>
#include <iostream>
#include <limits>
#include "platform/win32.h"

#include "./core/macro.h"
#include "./core/tgaimage.h"
#include "./core/model.h"
#include "./core/camera.h"
#include "./core/pipeline.h"
#include "./platform/win32.h"
#include "./shader/shader.h"

//Model *model     = nullptr;
//const int width  = 800;
//const int height = 800;
//
//Vec3f light_dir(1,1,1);
//Vec3f       eye(1,1,3);
//Vec3f    center(0,0,0);
//Vec3f        up(0,1,0);

const vec3 Eye(0, 1, 5);
const vec3 Up(0, 1, 0);
const vec3 Target(0, 1, 0);

void update_matrix(Camera &camera, mat4 view_mat, mat4 perspective_mat, Shader *model_shader);

int main(int argc, char** argv) {
//    Model model("../obj/african_head/african_head.obj");
    Model model("../obj/floor.obj");
//    if (2==argc) {
//        model = new Model(argv[1]);
//    } else {
//        model = new Model();
//    }

    int width = 800, height = 600;
    // set color buffer and depth buffer
    renderbuffer frame_buffer(width, height);

    // create camera
    Camera camera(Eye, Target, Up, (float)width/height);

    // set mvp matrix
    mat4 model_mat = mat4::identity();
    mat4 view_mat = mat4_lookat(camera.eye, camera.target, camera.up);
    mat4 perspective_mat = mat4_perspective(60, (float)width/height, -0.1, -10000);

    // initialize model and shader
    size_t model_num = 1;
    Shader *model_shader = new PhongShader();
    model_shader->payload.camera = camera;
    model_shader->payload.camera_perp_matrix = perspective_mat;

    // initialize window
    window_init(width, height, "BanaRender");

    while (!window->is_close){
        float curr_time = platform_get_time();

        // clear buffer
        frame_buffer.renderbuffer_clear_depth(-std::numeric_limits<float>::max());
        frame_buffer.renderbuffer_clear_color(vec3(0, 0, 0));

        // handle events and update view, perspective matrix
        handle_events(camera);
        update_matrix(camera, view_mat, perspective_mat, model_shader);

        // draw models
        for (int m = 0; m < model_num; ++m) {
            // assign model data to shader
            model_shader->payload.model = model;
            DrawData drawData;
            drawData.model = model;
            drawData.shader = model_shader;
            drawData.render_buffer = frame_buffer;
            draw_triangles(drawData);
        }

        // reset mouse information
        window->mouse_info.wheel_delta = 0;
        window->mouse_info.orbit_delta = vec2(0,0);
        window->mouse_info.fv_delta = vec2(0, 0);

        // send framebuffer to window
        window_draw(frame_buffer.color_buffer);
        msg_dispatch();
    }

    frame_buffer.renderbuffer_release();
    window_destroy();

    system("pause");
    return 0;
}

void update_matrix(Camera &camera, mat4 view_mat, mat4 perspective_mat, Shader *model_shader)
{
    view_mat = mat4_lookat(camera.eye, camera.target, camera.up);
    mat4 mvp = perspective_mat * view_mat;
    model_shader->payload.camera_view_matrix = view_mat;
    model_shader->payload.mvp_matrix = mvp;
}