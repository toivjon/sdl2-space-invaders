cmake_minimum_required (VERSION 3.7.2)
project (SDL2-SpaceInvaders)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)

file(GLOB SOURCES src/*.cpp)

include_directories(
	include
	${SDL2_INCLUDE}
	${SDL2_TTF_INCLUDE}
)

add_executable(space_invaders ${SOURCES})

target_link_libraries(space_invaders
	${SDL2_LIBRARY}
	${SDL2_TTF_LIBRARY}
)

file(COPY ${SDL2_BINARY_PATH}/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_TTF_BINARY_PATH}/SDL2_ttf.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_TTF_BINARY_PATH}/zlib1.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_TTF_BINARY_PATH}/libfreetype-6.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})