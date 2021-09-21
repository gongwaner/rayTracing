cmake_minimum_required(VERSION 3.20)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(ray_tracing main.cpp Vec3.cpp Vec3.h Colorf.cpp Colorf.h Ray.cpp Ray.h Hittable.h Sphere.cpp Sphere.h Camera.cpp Camera.h)
