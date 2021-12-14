cmake_minimum_required(VERSION 3.7)

set(SOURCE_TARGET Kings-And-Pigs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TMXPARSER_DIR "${CMAKE_SOURCE_DIR}/include/tmxparser")

set(CMAKE_PREFIX_PATH "${TMXPARSER_DIR}/lib/cmake")
set(ECS_engine  "Entity.h"
                "Systems.h"
                "Systems.cpp"
                "Components.h"
                "Scene.h"
                "Scene.cpp"
                "DebugRenderer.h"
                "DebugRenderer.cpp"
                "TextureLoader.cpp" 
                "TextureLoader.h")
file(GLOB all_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cpp
    *.h
)

list(REMOVE_ITEM all_sources ECS_engine)

add_library(ECS ${ECS_engine})
target_include_directories(ECS PUBLIC  ${CMAKE_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DLL_SOURCE_PATH ${CMAKE_SOURCE_DIR}/bin/debug CACHE INTERNAL "")
    set(LIB_SOURCE_PATH ${CMAKE_SOURCE_DIR}/lib/debug CACHE INTERNAL "")
    file(GLOB SFML_DLLS "${DLL_SOURCE_PATH}/*.dll")
    file(GLOB SFML_LIBS "${LIB_SOURCE_PATH}/*.a")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(DLL_INPUT_PATH ${CMAKE_SOURCE_DIR}/bin/release CACHE INTERNAL "")
    set(LIB_SOURCE_PATH ${CMAKE_SOURCE_DIR}/lib/release CACHE INTERNAL "")
    file(GLOB SFML_DLLS "${DLL_INPUT_PATH}/*.dll")
    file(GLOB SFML_LIBS "${LIB_SOURCE_PATH}/*.a")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

find_package(tmxparser REQUIRED)

add_executable(${SOURCE_TARGET} ${all_sources})


target_link_libraries(ECS PUBLIC ${SFML_LIBS})
target_link_libraries(${SOURCE_TARGET} PUBLIC ECS ${TMXPARSER_DIR}/lib/libtmxparser.dll.a)
target_link_libraries(${SOURCE_TARGET} PUBLIC ${SFML_LIBS})

target_include_directories(${SOURCE_TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/include ${TMXPARSER_DIR}/include)



#COPY RESOURCES POST_BUILD
add_custom_command(
    TARGET ${SOURCE_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
   ${CMAKE_CURRENT_SOURCE_DIR}/maps $<TARGET_FILE_DIR:${SOURCE_TARGET}>/maps
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
   ${CMAKE_CURRENT_SOURCE_DIR}/Sprites $<TARGET_FILE_DIR:${SOURCE_TARGET}>/Sprites)

#COPY DLLS
file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${TMXPARSER_DIR}/bin/libtmxparser.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})