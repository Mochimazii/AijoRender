cmake_minimum_required(VERSION 3.23)
project(AijoRender)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS
        core/macro.h
        core/tgaimage.h
        core/maths.h
        core/model.h
        core/camera.h
        shader/shader.h
        core/pipeline.h
        core/renderbuffer.h
        platform/win32.h
        core/Scene.h)

set(SOURCES
        core/tgaimage.cpp
        core/maths.cpp
        main.cpp
        core/model.cpp
        core/camera.cpp
        shader/phong_shader.cpp
        core/pipeline.cpp
        core/renderbuffer.cpp
        platform/win32.cpp
        core/Scene.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
