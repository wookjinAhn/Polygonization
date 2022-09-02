cmake_minimum_required(VERSION 3.23)
project(Polygonization)

set(CMAKE_CXX_STANDARD 14)

add_executable(Polygonization main.cpp QuickHull/QuickHull.cpp ConvexHull/ConvexHull.cpp Point/Point2D.cpp Point/Point3D.cpp)

find_package(camel-euclid-vector REQUIRED)
target_link_libraries(Polygonization camel-euclid-vector)