cmake_minimum_required(VERSION 3.5)
project(ChatCPP C CXX)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(JsonFactory)
add_subdirectory(Server)
add_subdirectory(Executable)