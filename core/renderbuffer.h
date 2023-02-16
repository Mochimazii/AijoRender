//
// Created by Aijo on 2023/1/26.
//

#ifndef BANARENDER_RENDERBUFFER_H
#define BANARENDER_RENDERBUFFER_H

#include "maths.h"
#include "cassert"

class renderbuffer {
public:
    renderbuffer();
    renderbuffer(int width, int height);

    int width, height;
    unsigned char* color_buffer;
    float* depth_buffer;

    float get_depth(int x, int y);
    void set_depth(int x, int y, float depth);
    vec3 get_color(int x, int y);
    void set_color(int x, int y, vec3 color);

    void renderbuffer_release();
    void renderbuffer_clear_color(vec3 color);
    void renderbuffer_clear_depth(float depth);
};


#endif //BANARENDER_RENDERBUFFER_H
