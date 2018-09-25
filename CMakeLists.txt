cmake_minimum_required(VERSION 3.0)

project (BomberMan)
message (STATUS "####################################################")

#installing what is nessesry
message ("Installing libraries")
#execute_process(COMMAND brew install xquartz)
#execute_process(COMMAND brew install freeglut)
execute_process(COMMAND brew install glew)
message(STATUS "glew should be installed")
execute_process(COMMAND brew install pkgconfig)
message(STATUS "pkgconfig should be installed")


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
message (STATUS "glad Should be downloaded")


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
message (STATUS "The glfw lib should be downloaded")


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
message (STATUS "glm Should be downloaded")


FetchContent_Declare(
	assimp
	GIT_REPOSITORY https://github.com/assimp/assimp.git
	GIT_TAG		   v4.1.0
)

FetchContent_GetProperties(assimp)
if(NOT assimp_POPULATED)
	FetchContent_Populate(assimp)
	add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
endif()
message (STATUS "assimp Should be downloaded")

add_executable (BomberMan ${BomberMan_SOURCES})
#target_include_directories(BomberMan PRIVATE ${LIB_INCLUDE_DIRS} ${BomberMan_INCLUDE_DIRS})
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

