# Project definition
cmake_minimum_required(VERSION 3.1)
project(Bomberman)

# Color Setting
if(NOT WIN32)
	string(ASCII 27 Esc)
	set(ColourReset "${Esc}[m")
	set(ColourBold  "${Esc}[1m")
	set(Red         "${Esc}[31m")
	set(Green       "${Esc}[32m")
	set(Yellow      "${Esc}[33m")
	set(Blue        "${Esc}[34m")
	set(Magenta     "${Esc}[35m")
	set(Cyan        "${Esc}[36m")
	set(White       "${Esc}[37m")
	set(BoldRed     "${Esc}[1;31m")
	set(BoldGreen   "${Esc}[1;32m")
	set(BoldYellow  "${Esc}[1;33m")
	set(BoldBlue    "${Esc}[1;34m")
	set(BoldMagenta "${Esc}[1;35m")
	set(BoldCyan    "${Esc}[1;36m")
	set(BoldWhite   "${Esc}[1;37m")
endif()

set(GLEW_INCLUDE_DIR "$ENV{HOME}/.brew/Cellar/glew/2.1.0/include")
set(GLEW_LIBRARY "$ENV{HOME}/.brew/Cellar/glew/2.1.0/lib")

set(GLFW_LIBRARY "$ENV{HOME}/.brew/Cellar/glfw/3.2.1/lib")
set(GLFW_INCLUDE_DIRS "$ENV{HOME}/.brew/Cellar/glfw/3.2.1/include")

find_package(GLUT REQUIRED)
set(LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Libraries")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

file(GLOB_RECURSE BomberMan_SOURCES "*.cpp")
file(GLOB_RECURSE BomberMan_HEADERS "*.hpp")

# Recersivley itterate through the "Build" directory for all the sources and includes. 
set (BomberMan_INCLUDE_DIRS "Build")
foreach(_headerFile ${BomberMan_HEADERS})
	get_filename_component(_dir $(_headerFile) PATH)
	list(APPEND BomberMan_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES BomberMan_INCLUDE_DIRS)

SET(CMAKE_CXX_FLAGS "-O2 -std=c++11")
SET(CMAKE_EXE_LINKER_FLAGS "-lfreetype -lassimp")

add_executable(${PROJECT_NAME} ${BomberMan_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${BomberMan_INCLUDE_DIRS}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# Checking if Requeried Packages are installed

# GLEW
if(GLEW_FOUND)
	link_libraries(${PROJECT_NAME} glew ${GLEW_LIBRARIES})
	target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIR})
	target_compile_definitions(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_NONE})
else()
	message("${Red}Glew Package Not Found${ColourReset}")
endif()

# GLFW
if(GLFW_FOUND)
	message("${Green}Glfw Package Found - ${ColourReset}")
	include_directories(${GLFW_INCLUDE_DIRS})
	target_link_libraries(Bomberman glfw)
else()
	message("${Red}Glfw Package Not Found${ColourReset}")
endif()

# GLM
if(GLM_FOUND)
	message("${Green}GLM Package Found${ColourReset}")
	include_directories("$ENV{HOME}/.brew/Cellar/glm/0.9.9.0/include")
	link_libraries(${PROJECT_NAME} glm ${GLM_LIBRARIES})
else()
	message("${Red}GLM Package Not Found${ColourReset}")
endif()

#BREW INCLUDE DIR
include_directories("$ENV{HOME}/.brew/include")
link_libraries(${PROJECT_NAME} $ENV{HOME}/.brew/lib)

include(FindFreetype)
include_directories(${FREETYPE_INCLUDE_DIRS})

#GLAD
	include_directories(${LIBRARY_DIR}/glad/include)
	target_link_libraries(Bomberman ${LIBRARY_DIR}/glad/libglad.a)

#STB IMAGE
	include_directories(${LIBRARY_DIR}/stb)

#IrrkLang
	include_directories(${LIBRARY_DIR}/irrKlang-64bit-1.6.0/include)