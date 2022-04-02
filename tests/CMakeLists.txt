
set(CMAKE_CXX_STANDARD 11)

add_executable(tests main.cpp tests.cpp)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tests PUBLIC ${GTEST_INCLUDE_DIRS})

target_link_libraries(tests ${VECTOR_SEARCH} ${GTEST_LIBRARIES} Threads::Threads )

