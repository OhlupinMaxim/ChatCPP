cmake_minimum_required(VERSION 3.5)
project(Executable C CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_definitions(${PROJECT_NAME} PUBLIC ${Server_DEFINITIONS} ${CONAN_DEFINITIONS})

target_link_directories(${PROJECT_NAME} PUBLIC ${Server_INCLUDE_DIRS} ${CONAN_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${Server_INCLUDE_DIRS} ${CONAN_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${CONAN_LIBS} Server)