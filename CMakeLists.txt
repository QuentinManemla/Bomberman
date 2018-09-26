cmake_minimum_required(VERSION 3.11)

project (BomberMan)
message (STATUS "####################################################")


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

#Get all the Library headers directories
file(GLOB_RECURSE LIB_cHEADERS "Libraries/*.h")
file(GLOB_RECURSE LIB_cppHEADERS "Libraries/*.hpp")
list (APPEND LIB_cppHEADERS ${LIB_cHEADERS})
set (LIB_INCLUDE_DIRS "")
foreach (_headerFile ${LIB_cppHEADERS})
    #message(STATUS "The current path is ${_headerFile}")
	get_filename_component(_dir ${_headerFile} PATH)
	list(APPEND LIB_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES LIB_INCLUDE_DIRS)
#message (STATUS "The include Directories are: ${LIB_INCLUDE_DIRS}")


#installing what is nessesry
message ("Installing libraries")

#needs xquartz from the softwear managment center on mac
execute_process(COMMAND brew install assimp) #don't need this?
message (STATUS ">>>>>>>>>>>>>>>>assimp Should be downloaded")

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
  FetchContent_Populate(
	  glfw)
	  #SOURCE_DIR "")
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

FetchContent_Declare(
	freeglut
	GIT_REPOSITORY https://github.com/Jerome-Damhuis/glut-dep_for_bomberman.git
	#GIT_TAG		   VER-2-6-3 
)

FetchContent_GetProperties(freeglut)
if(NOT freeglut_POPULATED)
	FetchContent_Populate(freeglut)
	add_subdirectory(${freeglut_SOURCE_DIR} ${freeglut_BINARY_DIR})
endif()
message (STATUS ">>>>>>>>>>>>>>>>freeglut Should be downloaded")

message ("The libraries are installed")

add_executable (BomberMan ${BomberMan_SOURCES})
target_include_directories(BomberMan PRIVATE ${LIB_INCLUDE_DIRS} ${BomberMan_INCLUDE_DIRS})
target_include_directories(BomberMan PRIVATE $ENV{HOME}/.brew/Cellar/assimp/4.1.0/include/)
target_include_directories(BomberMan PRIVATE ${freetype_SOURCE_DIR}/include)
target_include_directories(BomberMan PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(BomberMan PRIVATE ${irrklang_SOURCE_DIR}/include)
target_include_directories(BomberMan PRIVATE ${stb_SOURCE_DIR})
target_include_directories(BomberMan PRIVATE ${glm_SOURCE_DIR})
target_include_directories(BomberMan PRIVATE ${freeglut_SOURCE_DIR}/include)

find_library(ASSIMP_LIB assimp HINTS $ENV{HOME}/.brew/Cellar/assimp/4.1.0/lib/)
#link_directories($ENV{HOME}/.brew/Cellar/assimp/4.1.0/lib/ )

target_link_libraries(BomberMan glfw freetype irrklang glad ${ASSIMP_LIB} glut)


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

