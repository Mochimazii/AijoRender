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

const vec3 Eye(0, 1, 5);
const vec3 Up(0, 1, 0);
const vec3 Target(0, 0, 0);

void update_matrix(Camera &camera, mat4 view_mat, mat4 perspective_mat, Shader *model_shader);

int main(int argc, char** argv) {
    Model model("../obj/floor.obj");

    int width = 800, height = 600;
    // set color buffer and depth buffer
    renderbuffer frame_buffer(width, height);

    // create camera
    Camera camera(Eye, Target, Up, (float)width/height);

    // initialize  shader
    Shader *model_shader = new PhongShader();

    // initialize scene
    std::vector<Model> models;
    models.push_back(model);
    vec3 light(1,1,1);
    Scene scene(models, camera, light, model_shader, frame_buffer);

    // initialize window
    window_init(width, height, "BanaRender");

    while (!window->is_close){
        float curr_time = platform_get_time();

        // clear buffer
        frame_buffer.renderbuffer_clear_depth(-std::numeric_limits<float>::max());
        frame_buffer.renderbuffer_clear_color(vec3(0, 0, 0));

        handle_events(camera);

        // draw scene
        scene.tick(camera);
        draw_triangles(scene);

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
