cmake_minimum_required(VERSION 3.20)

project(OGLBF)

#set c++ properties
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set _DEBUG FLAG
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_definitions(-D_DEBUG)
endif()

#build thirdyParty libraries
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/thirdParty")

file(GLOB MAIN_SRCS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
message("main srcs: ${MAIN_SRCS}")

add_executable(${PROJECT_NAME} ${MAIN_SRCS})