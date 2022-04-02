add_library(vec_processing vector.c vector.h)

target_include_directories(vec_processing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vec_processing PRIVATE m)
