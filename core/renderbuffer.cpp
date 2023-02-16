//
// Created by Aijo on 2023/1/26.
//

#include "renderbuffer.h"

renderbuffer::renderbuffer(int width, int height) {
    int color_buffer_size = width * height * 4;
    int depth_buffer_size = sizeof(float) * width * height;
    vec3 default_color = { 0, 0, 0 };
    float default_depth = 1;

    assert(width > 0 && height > 0);

    this->width = width;
    this->height = height;
    this->color_buffer = (unsigned char*)malloc(color_buffer_size);
    this->depth_buffer = (float*)malloc(depth_buffer_size);

    this->renderbuffer_clear_color(default_color);
    this->renderbuffer_clear_depth(default_depth);
}

vec3 renderbuffer::get_color(int x, int y) {
    vec3 color;
    int index = ((height - y - 1) * width + x) * 4;

    for (int i = 0; i < 3; i++)
        color[i] = color_buffer[index + i];

    return color;
}

void renderbuffer::set_color(int x, int y, vec3 color) {
    int index = ((height - y - 1) * width + x) * 4; // the origin for pixel is bottom-left, but the framebuffer index counts from top-left

    for (int i = 0; i < 3; i++)
        color_buffer[index + i] = color[i];
}

float renderbuffer::get_depth(int x, int y) {
    int index = (height - y - 1) * width + x;

    return depth_buffer[index];
}

void renderbuffer::set_depth(int x, int y, float depth) {
    int index = (height - y - 1) * width + x;
    depth_buffer[index] = depth;
}

void renderbuffer::renderbuffer_release() {
    free(color_buffer);
    free(depth_buffer);
    free(this);
}

void renderbuffer::renderbuffer_clear_color(vec3 color) {
    int num_pixels = this->width * this->height;
    int i;
    for (i = 0; i < num_pixels; i++) {
        this->color_buffer[i * 4 + 0] = color.x();
        this->color_buffer[i * 4 + 1] = color.y();
        this->color_buffer[i * 4 + 2] = color.z();
    }
}

void renderbuffer::renderbuffer_clear_depth(float depth) {
    int num_pixels = this->width * this->height;
    int i;
    for (i = 0; i < num_pixels; i++) {
        this->depth_buffer[i] = depth;
    }
}

renderbuffer::renderbuffer() {

}


