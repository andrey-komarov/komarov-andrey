cmake_minimum_required(VERSION 2.6)

project(segments_intersection)

add_definitions(-Wall -O3 -W -msse -msse2 -msse3 -msse4 -msse4.1 -Wno-sign-compare -std=c++0x)
link_libraries(boost_unit_test_framework)

set(common_src ./src/double_utils.cpp ./src/double_utils.h ./src/enum.cpp ./src/enum.h ./src/essa.h ./src/intersection.cpp ./src/intersection.h ./src/orientation.cpp ./src/orientation.h ./src/point.cpp ./src/point.h ./src/priority_queue.h ./src/segment.h ./src/segment.cpp)
#set(EXECUTABLE_OUTPUT_PATH ./bin)

set(slow_src ./slow/big_int.cpp ./slow/big_int.h ./slow/container.cpp ./slow/container.h ./slow/fraction.cpp ./slow/fraction.h ./slow/geom_config.h ./slow/point.cpp ./slow/point.h ./slow/predicates.cpp ./slow/predicates.h ./slow/segment.cpp ./slow/segment.h ./slow/utils.cpp ./slow/utils.h)

MESSAGE("PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")

add_executable(turn ./src/main.cpp ${common_src})
add_executable(test ./src/test.cpp ${common_src})
add_executable(slooow ./slow/main.cpp ${slow_src})
