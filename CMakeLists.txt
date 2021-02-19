cmake_minimum_required(VERSION 3.17)
project(GayEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(box2d REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(SOURCE_FILES sources/Main.cpp sources/Draw.cpp sources/Input.cpp sources/Engine.cpp
        sources/Player.cpp sources/Update.cpp sources/World.cpp
        sources/Object.cpp sources/Layer.cpp )

add_executable(GayEngine ${SOURCE_FILES})

#target_include_directories(GayEngine PUBLIC
#	"include/"
#)

include_directories(include/)

target_link_libraries(GayEngine
	box2d::box2d
	nlohmann_json::nlohmann_json
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	sfml-network
)

set(CMAKE_CXX_FLAGS "-fpermissive")
