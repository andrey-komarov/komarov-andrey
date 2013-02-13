cmake_minimum_required(VERSION 2.6)

project(segments_intersection)

add_definitions(-Wall -O2 -Wno-sign-compare -std=c++0x)
link_libraries(gmp gmpxx)

set(common_src ./src/delaunay.cpp ./src/delaunay.h ./src/sign.cpp ./src/sign.h ./src/point.h ./src/point.cpp ./src/predicates.h ./src/predicates.cpp)

MESSAGE("PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")

add_executable(main ./src/main.cpp ${common_src})
add_executable(testgen ./src/testgen.cpp)
