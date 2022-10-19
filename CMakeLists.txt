cmake_minimum_required (VERSION 3.7.2)
project (SDL2-SpaceInvaders)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)

include(FindPkgConfig)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)

file(GLOB SOURCES src/*.cpp)

include_directories(
	include
	${SDL2_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
)

add_executable(space_invaders ${SOURCES})

target_link_libraries(space_invaders
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
)

file(COPY spritesheet.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
