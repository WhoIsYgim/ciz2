cmake_minimum_required(VERSION 3.16.3)

project(ciz2 C )

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES "main.c")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(STATIC_EXEC "vector_search")
set(STATIC_EXEC_SOURCE_DIR "./src/static_cons")

set(DYNAMIC_EXEC "vector_search")
set(DYNAMIC_EXEC_SOURCE_DIR "./src/dynamic_paral")


if(cons)
    add_subdirectory(${STATIC_EXEC_SOURCE_DIR} lib)
    target_include_directories(${PROJECT_NAME} PUBLIC ${STATIC_EXEC_SOURCE_DIR})
    target_link_libraries(${PROJECT_NAME} ${STATIC_EXEC})

elseif(paral)
    add_subdirectory(${DYNAMIC_EXEC_SOURCE_DIR} lib)
    target_include_directories(${PROJECT_NAME} PUBLIC ${DYNAMIC_EXEC_SOURCE_DIR})
    target_link_libraries(${PROJECT_NAME} ${DYNAMIC_EXEC})
endif()

#add_subdirectory(src)

##target_link_libraries(${PROJECT_NAME} LINK_PUBLIC  static_exec)

##remove later
#target_link_libraries(${PROJECT_NAME} LINK_PUBLIC  vector_search)


