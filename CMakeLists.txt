cmake_minimum_required(VERSION 3.13)
project(CG2 C)

set(CMAKE_C_STANDARD 99)

add_executable(CG2 main.c Color.c Color.h Image.c Image.h stb_image.h stb_image_write.h Mathematics.c Mathematics.h)

target_link_libraries(CG2 m)
