cmake_minimum_required(VERSION 2.6)

project(minpath)

add_definitions(-Wall -O2 -Wno-sign-compare -std=c++0x)
link_libraries(gmp gmpxx)

set(common_src ./src/graph.cpp ./src/graph.h ./src/sign.cpp ./src/sign.h ./src/point.h ./src/point.cpp ./src/predicates.h ./src/predicates.cpp ./src/vizibility.cpp ./src/vizibility.h)

MESSAGE("PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")

add_executable(main ./src/main.cpp ${common_src})
