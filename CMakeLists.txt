cmake_minimum_required(VERSION 3.14)
project(CG2)

set(CMAKE_CXX_STANDARD 11)

add_executable(CG2 main.cpp Color.cpp Color.h Image.cpp Image.h stb_image.h stb_image_write.h Mathematics.cpp Mathematics.h objFile.cpp objFile.h objects.cpp objects.h marchingCubes.h)

target_link_libraries(CG2 m)
