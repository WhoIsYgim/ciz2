
set(CMAKE_CXX_STANDARD 11)

file(GLOB TEST_FILE "test_vector.txt")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input/${TEST_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/input)

add_executable(tests main.cpp tests.cpp)



find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tests PUBLIC ${GTEST_INCLUDE_DIRS})

target_link_libraries(tests ${VECTOR_SEARCH} ${GTEST_LIBRARIES} Threads::Threads )

