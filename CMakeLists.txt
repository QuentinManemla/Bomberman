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

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(LIB_DIR, "/goinfre/qmanamel/.brew/Cellar")

file(GLOB_RECURSE BomberMan_SOURCES "sources/*.cpp")
file(GLOB_RECURSE BomberMan_HEADERS "includes/*.hpp")

# Recersivley itterate through the "Sources" directory for all the sources and includes. 
set (BomberMan_INCLUDE_DIRS "Sources")
foreach(_headerFile ${BomberMan_HEADERS})
	get_filename_component(_dir $(_headerFile) PATH)
	list(APPEND BomberMan_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES BomberMan_INCLUDE_DIRS)

add_executable(${PROJECT_NAME} ${BomberMan_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${BomberMan_INCLUDE_DIRS}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# Checking if Requeried Packages are installed

# GLEW
if(GLEW_FOUND)
	message("${Green}Glew Package Found${ColourReset}")
	include_directories("/goinfre/qmanamel/.brew/Cellar/glew/2.1.0/include")
	link_libraries(${PROJECT_NAME} glew ${GLEW_LIBRARIES})
else()
	message("${Red}Glew Package Not Found${ColourReset}")
endif()

# GLFW
if(GLFW_FOUND)
	message("${Green}Glfw Package Found${ColourReset}")
	include_directories("/goinfre/qmanamel/.brew/Cellar/glfw/3.2.1/include")
	link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
else()
	message("${Red}Glfw Package Not Found${ColourReset}")
endif()

# GLM
if(GLM_FOUND)
	message("${Green}GLM Package Found${ColourReset}")
	include_directories("/goinfre/qmanamel/.brew/Cellar/glm/0.9.9.0/include")
	link_libraries(${PROJECT_NAME} glm ${GLM_LIBRARIES})
else()
	message("${Red}GLM Package Not Found${ColourReset}")
endif()

