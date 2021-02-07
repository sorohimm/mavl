cmake_minimum_required(VERSION 3.17)
project(GayEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(box2d REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
pkg_check_modules(TINYXML tinyxml)


set(SOURCE_FILES sources/main.cpp sources/Draw.cpp sources/Input.cpp sources/Engine.cpp
        sources/Player.cpp sources/Update.cpp sources/Level.cpp)

add_executable(GayEngine ${SOURCE_FILES})

if(APPLE)
    include_directories("/usr/local/include/")
endif()

target_include_directories(GayEngine PUBLIC
	"include/"
	${BOX2D_INCLUDE_DIR}
)

target_link_libraries(GayEngine
  nlohmann_json::nlohmann_json
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	sfml-network
	${TINYXML_LINK_LIBRARIES}
	${BOX2D_LINK_LIBRARIES}
)


set(CMAKE_CXX_FLAGS "-fpermissive")


