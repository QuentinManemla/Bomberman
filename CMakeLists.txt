cmake_minimum_required(VERSION 3.11)

project (BomberMan)
message (STATUS "####################################################")


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
message ("Installing libraries")

#needs xquartz from the softwear managment center on mac
execute_process(COMMAND brew install assimp)
message (STATUS ">>>>>>>>>>>>>>>>assimp Should be downloaded")

execute_process(COMMAND brew install freeglut)
message (STATUS ">>>>>>>>>>>>>>>>freeglut Should be downloaded")

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
message (STATUS ">>>>>>>>>>>>>>>>glad Should be downloaded")


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
message (STATUS ">>>>>>>>>>>>>>>>The glfw lib should be downloaded")


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
message (STATUS ">>>>>>>>>>>>>>>>glm Should be downloaded")


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
message (STATUS ">>>>>>>>>>>>>>>>irrklang Should be downloaded")


FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_GetProperties(stb)
if(NOT stb)
	FetchContent_Populate(stb)
	#include the headerfiles and libs
endif()
message (STATUS ">>>>>>>>>>>>>>>>stb Should be downloaded")


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
message (STATUS ">>>>>>>>>>>>>>>>freetype Should be downloaded")

message ("The libraries are installed")

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
	message (STATUS "This is an apple machine")
endif()
if (LINUX)
	message(STATUS "This is a Linux Machine")
    find_package(glfw REQUIRED)
    if(glfw_FOUND)
        message(STATUS "glfw is installed")
    endif()
endif()
if (WIN32)
	message(STATUS "This is a windows machine")
endif()


message (STATUS "####################################################")

