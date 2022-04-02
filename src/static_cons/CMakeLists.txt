cmake_minimum_required(VERSION 3.16.3)

project(vector_search C )

set(VEC_PROC_DIR "vec_processing")

add_subdirectory(${VEC_PROC_DIR})

add_library(${PROJECT_NAME} STATIC ${PROJECT_NAME}.c ${PROJECT_NAME}.h)

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} ${VEC_PROC_DIR})