cmake_minimum_required(VERSION 3.0.0)
##project(Abstract_VM VERSION 0.0.0)

##enable_testing()

#include headers
##include_directories ("${PROJECT_SOURCE_DIR}/hdr")

#message(STATUS "Your operating system is ${CMAKE_SYSTEM_NAME}")
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (APPLE)

endif()
if (LINUX)
        find_package(glfw REQUIRED)
        if(glfw_FOUND)
                message(STATUS "glfw is installed")
        endif()
endif()
if (WIN32)

endif()


#include source files
##file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#add compiling flags
##add_definitions("-Wall" "-Wextra" "-pedantic" "-std=c++0x")

#create the exacutable
##add_executable(Abstract_VM ${SRC_FILES})