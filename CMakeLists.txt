# Project definition
cmake_minimum_required(VERSION 3.1)
project(Bomberman)

file(GLOB_RECURSE BomberMan_SOURCES "sources/*.cpp")
file(GLOB_RECURSE BomberMan_HEADERS "includes/*.hpp")

set (BomberMan_INCLUDE_DIRS "Sources")
foreach(_headerFile ${BomberMan_HEADERS})
	get_filename_component(_dir $(_headerFile) PATH)
	list(APPEND BomberMan_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES BomberMan_INCLUDE_DIRS)

add_executable(${PROJECT_NAME} ${BomberMan_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${BomberMan_INCLUDE_DIRS}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
