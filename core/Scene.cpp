//
// Created by 59741 on 2023/2/19.
//

#include "Scene.h"
/**
 * ��ʼ������(�ƹ�λ��/���߷���/ģ�;���/�۲����/ͶӰ����)
 * ģ��Ĭ������������(ģ�;���Ϊ��λ����)
 * ͶӰ����Ϊ͸��ͶӰ
 * @param models
 * @param camera
 * @param light
 * @param currShader
 * @param render_buffer
 */
Scene::Scene(std::vector<Model> models, Camera camera, vec3 light, Shader* currShader, renderbuffer &render_buffer):
models(models),camera(camera),light(light),shader(currShader),render_buffer(render_buffer){
    mat4 model_matrix = mat4::identity();
    mat4 view_matrix = mat4_lookat(camera.eye, camera.target, camera.up);
    mat4 perspective_mat = mat4_perspective(60, (float)render_buffer.width/render_buffer.height, -0.1, -10000);

    shader->shader_payload.light_Pos = light;
    shader->shader_payload.view_Pos = camera.eye;
    shader->shader_payload.model_matrix = model_matrix;
    shader->shader_payload.view_matrix = view_matrix;
    shader->shader_payload.projection_matrix = perspective_mat;

}
/**
 * ���³���״̬(�۲����/���߷���)
 * ���� MVP ����
 * @param camera
 */
void Scene::tick(Camera &camera) {
    mat4 view_mat = mat4_lookat(camera.eye, camera.target, camera.up);

    shader->shader_payload.view_Pos = camera.eye;
    shader->shader_payload.view_matrix = view_mat;
    shader->shader_payload.mvp_matrix = shader->shader_payload.projection_matrix * view_mat * shader->shader_payload.model_matrix;
}

void Scene::draw_call() {
    for (int i = 0; i < models.size(); ++i) {
        this->shader->shader_payload.diffuse_map = models[i].diffuse_map();
        this->shader->shader_payload.specular_map = models[i].specular_map();
        this->shader->shader_payload.normal_map = models[i].normal_map();
    }
}

size_t Scene::modelSize() {
    return this->models.size();
}
/**
 * ���ó����ж�Ӧģ�͵ĸ�����ͼ
 * @param model_index ��Ӧģ�͵��±�
 */
void Scene::set_model_sample2D(size_t model_index) {
    this->shader->shader_payload.diffuse_map = models[model_index].diffuse_map();
    this->shader->shader_payload.specular_map = models[model_index].specular_map();
    this->shader->shader_payload.normal_map = models[model_index].normal_map();
}

Model &Scene::model(size_t i) {
    return this->models[i];
}

Shader *Scene::get_shader() {
    return this->shader;
}

renderbuffer &Scene::get_render_buffer() {
    return this->render_buffer;
}

void Scene::set_render_buffer(renderbuffer &renderbuffer) {
    this->render_buffer = renderbuffer;
}
