cmake_minimum_required(VERSION 3.11)

project (BomberMan)

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

message(STATUS "${Magenta} # - Starting Cmake Build - # ${ColourReset}")


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

#Get all project source files
file(GLOB_RECURSE BomberMan_SOURCES "Build/*.cpp")

#get all the project header directories
file(GLOB_RECURSE BomberMan_HEADERS "Build/*.hpp")
set (BomberMan_INCLUDE_DIRS "")
foreach (_headerFile ${BomberMan_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND BomberMan_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES BomberMan_INCLUDE_DIRS)

#installing what is nessesry
message(STATUS "${Yellow} Installing Libraries ${ColourReset}")

#needs xquartz from the softwear managment center on mac
execute_process(COMMAND brew install assimp)
message(STATUS "${Green} Assimp Should Be Downloaded ${ColourReset}")

execute_process(COMMAND brew install freeglut)
message(STATUS "${Green} FreeGlut Should Be Downloaded ${ColourReset}")

include("FetchContent")

FetchContent_Declare(
	glad
	GIT_REPOSITORY https://github.com/Dav1dde/glad.git
	GIT_TAG		   v0.1.27
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
	FetchContent_Populate(glad)
	add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()
message(STATUS "${Green} Glad Should Be Downloaded ${ColourReset}")


FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.2.1
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
	FetchContent_Populate(glfw)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()
message(STATUS "${Green} GLFW Should Be Downloaded ${ColourReset}")


FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG		   0.9.9.2
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
	FetchContent_Populate(glm)
	set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
	add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()
message(STATUS "${Green} GLM Should Be Downloaded ${ColourReset}")


FetchContent_Declare(
	irrklang
	GIT_REPOSITORY https://github.com/Jerome-Damhuis/irrKlang-dep_for_Bomberman.git
	GIT_TAG		   1.0.0
)

FetchContent_GetProperties(irrklang)
if(NOT irrklang_POPULATED)
	FetchContent_Populate(irrklang)
	link_directories(${irrklang_SOURCE_DIR}/bin/macosx-gcc)
	#include the headerfiles and libs
endif()
message(STATUS "${Green} IirKlang Should Be Downloaded ${ColourReset}")


FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_GetProperties(stb)
if(NOT stb)
	FetchContent_Populate(stb)
	#include the headerfiles and libs
endif()
message(STATUS "${Green} STB Should Be Downloaded ${ColourReset}")


FetchContent_Declare(
	freetype
	GIT_REPOSITORY https://github.com/aseprite/freetype2.git
	GIT_TAG		   VER-2-6-3 
)

FetchContent_GetProperties(freetype)
if(NOT freetype_POPULATED)
	FetchContent_Populate(freetype)
	add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
endif()
message(STATUS "${Green} FreeType Should Be Downloaded ${ColourReset}")

message(STATUS "${Green} # - Library Installation Compelete - # ${ColourReset}")

add_executable (BomberMan ${BomberMan_SOURCES})
target_include_directories(BomberMan PRIVATE ${LIB_INCLUDE_DIRS} ${BomberMan_INCLUDE_DIRS})
target_include_directories(BomberMan PRIVATE ${freetype_SOURCE_DIR}/include)
target_include_directories(BomberMan PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(BomberMan PRIVATE ${irrklang_SOURCE_DIR}/include)
target_include_directories(BomberMan PRIVATE ${stb_SOURCE_DIR})
target_include_directories(BomberMan PRIVATE ${glm_SOURCE_DIR})
target_include_directories(BomberMan PRIVATE $ENV{HOME}/.brew/Cellar/assimp/4.1.0/include/)
target_include_directories(BomberMan PRIVATE $ENV{HOME}/.brew/Cellar/freeglut/3.0.0/include)

find_library(ASSIMP_LIB assimp HINTS $ENV{HOME}/.brew/Cellar/assimp/4.1.0/lib/)
#link_directories($ENV{HOME}/.brew/Cellar/assimp/4.1.0/lib/ )
find_library(GLUT_LIB glut HINTS $ENV{HOME}/.brew/Cellar/freeglut/3.0.0/lib/)
find_library(OPENGL GL HINTS /System/Library/Frameworks/OpenGL.framework/Libraries)

execute_process(COMMAND install_name_tool -id "${irrklang_SOURCE_DIR}/bin/macosx-gcc/libirrklang.dylib" ${irrklang_SOURCE_DIR}/bin/macosx-gcc/libirrklang.dylib)

target_link_libraries(BomberMan glfw freetype irrklang glad ${ASSIMP_LIB} ${GLUT_LIB} ${OPENGL})

set_target_properties( BomberMan PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR} )

#add compiling flags
target_compile_options(BomberMan PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-std=c++11")

#message(STATUS "Your operating system is ${CMAKE_SYSTEM_NAME}")
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (APPLE)
	message(STATUS "${Green} # - This Is an Apple Machine - # ${ColourReset}")
endif()
if (LINUX)
	message(STATUS "${Green} # - This Is a Linux Machine - # ${ColourReset}")
	find_package(glfw REQUIRED)
	if(glfw_FOUND)
		message(STATUS "${Green} # - GLFW is Installed - # ${ColourReset}")
	endif()
endif()
if (WIN32)
	message(STATUS "${Green} # - This Is a Windows Machine - # ${ColourReset}")
endif()


message(STATUS "${Green} # - Build Complete - # ${ColourReset}")
