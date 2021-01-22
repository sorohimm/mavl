#cmake_minimum_required(VERSION 3.17)
#project(GayEngine)
#
#set(CMAKE_CXX_STANDARD 20)
#
#find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
#find_package(box2d REQUIRED)
#find_package(tinyxml REQUIRED)
#set(SOURCE_FILES sources/main.cpp sources/Draw.cpp sources/Input.cpp sources/Engine.cpp
#        sources/Player.cpp sources/Update.cpp sources/Level.cpp)
#
#add_executable(GayEngine ${SOURCE_FILES})
#
#include_directories("include/")
#include_directories(${SFML_INCLUDE_DIRS})
#
#target_link_libraries(GayEngine sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
#target_link_libraries(GayEngine box2d)
#target_link_libraries(GayEngine tinyxml)

cmake_minimum_required(VERSION 3.17)
project(GayEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
#find_package(box2d REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(tinyxml tinyxml)


set(SOURCE_FILES sources/main.cpp sources/Draw.cpp sources/Input.cpp sources/Engine.cpp
        sources/Player.cpp sources/Update.cpp sources/Level.cpp)

add_executable(GayEngine ${SOURCE_FILES})

include_directories("include/")
include_directories(
        ${SFML_INCLUDE_DIRS} )

target_link_libraries(GayEngine sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
#target_link_libraries(GayEngine box2d)
target_link_libraries(GayEngine tinyxml)


set(CMAKE_CXX_FLAGS "-fpermissive")


