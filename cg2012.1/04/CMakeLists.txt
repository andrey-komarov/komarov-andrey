cmake_minimum_required(VERSION 2.6)

project(segments_intersection)

# add_definitions(-Wall -O3 -W -msse -msse2 -msse3 -msse4 -msse4.1 -Wno-sign-compare -std=c++0x)
add_definitions(-Wall -O2 -Wno-sign-compare -std=c++0x)
#link_libraries(boost_unit_test_framework gmp gmpxx)

set(common_src ./src/double_utils.cpp ./src/double_utils.h ./src/enum.cpp ./src/enum.h ./src/essa.h ./src/orientation.cpp ./src/orientation.h ./src/point.cpp ./src/point.h ./src/priority_queue.h ./src/segment.h ./src/segment.cpp)
#set(EXECUTABLE_OUTPUT_PATH ./bin)

MESSAGE("PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")

add_executable(main ./src/main.cpp ${common_src})
