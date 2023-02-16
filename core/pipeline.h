//
// Created by Aijo on 2023/1/26.
//

#ifndef BANARENDER_PIPELINE_H
#define BANARENDER_PIPELINE_H

#include "macro.h"
#include "maths.h"
#include <limits>
#include "../shader/shader.h"
#include "../platform/win32.h"
#include "renderbuffer.h"

struct DrawData {
    Model model;
    Shader *shader;
    renderbuffer render_buffer;
};

void draw_triangles(DrawData& drawData);
void rasterize(vec4 *clipcoord_attri, DrawData& drawData);

#endif //BANARENDER_PIPELINE_H
