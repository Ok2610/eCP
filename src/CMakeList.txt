cmake_minimum_required(VERSION 3.27)

set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true eCP/containers/*.h eCP/containers/*.hpp eCP/descriptors/*.h eCP/descriptors/*.hpp eCP/*.h eCP/*.hpp eCP/*.cpp) 

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

target_link_libraries(${BINARY}_run PRIVATE hdf5::hdf5)
target_link_libraries(${BINARY}_run PRIVATE ${Python3_LIBRARIES})

add_library(${BINARY}_lib STATIC ${SOURCES})