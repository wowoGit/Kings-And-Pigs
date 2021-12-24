cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Tests Tests)

set(Sources MyTest.cpp)

add_executable(${Tests} ${Sources})
message( "${LIB_SOURCE_PATH}")
file(GLOB SFML_DLLS "${DLL_SOURCE_PATH}/*.dll")
file(GLOB SFML_LIBS "${LIB_SOURCE_PATH}/*.a")
include(GoogleTest)
message(" libs ${SFML_LIBS}")
target_link_libraries(${Tests} PUBLIC ${SFML_LIBS} gtest gtest_main ECS)
target_include_directories( ${Tests} PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

gtest_discover_tests(${Tests})

file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})