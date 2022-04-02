cmake_minimum_required(VERSION 3.16.3)

project(ciz2 C CXX)
set(CMAKE_C_STANDARD 99)


set(SOURCE_FILES "main.c")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(VECTOR_SEARCH "vector_search")

if(paral)

    set(VECTOR_SEARCH_SOURCE_DIR "./src/dynamic_paral")


    add_subdirectory(${VECTOR_SEARCH_SOURCE_DIR} lib)
    target_include_directories(${PROJECT_NAME} PUBLIC ${VECTOR_SEARCH_SOURCE_DIR})
    target_link_libraries(${PROJECT_NAME} ${VECTOR_SEARCH})
elseif(cons)

    set(VECTOR_SEARCH_SOURCE_DIR "./src/static_cons")

    add_subdirectory(${VECTOR_SEARCH_SOURCE_DIR} lib)
    target_include_directories(${PROJECT_NAME} PUBLIC ${VECTOR_SEARCH_SOURCE_DIR})
    target_link_libraries(${PROJECT_NAME} ${VECTOR_SEARCH})

endif()

add_subdirectory(tests)



