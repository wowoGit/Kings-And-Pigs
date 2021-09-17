cmake_minimum_required(VERSION 3.7)

file(GLOB all_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cpp
    *.h
)

add_executable(${CMAKE_PROJECT_NAME} ${all_sources})

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/lib/libsfml-graphics-d.a
    ${CMAKE_SOURCE_DIR}/lib/libsfml-audio-d.a
    ${CMAKE_SOURCE_DIR}/lib/libsfml-window-d.a
    ${CMAKE_SOURCE_DIR}/lib/libsfml-system-d.a)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
${PROJECT_SOURCE_DIR}/tinyxml2
)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC tinyxml2)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)