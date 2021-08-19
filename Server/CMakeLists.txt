cmake_minimum_required(VERSION 3.10)
project(Server C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SERVER_HEADERS
        include/*.h
        include/*hpp
        )

file(GLOB SERVER_SOURCE
        source/*.cpp
        )

add_library(${PROJECT_NAME} SHARED ${SERVER_HEADERS} ${SERVER_SOURCE})

target_compile_definitions(${PROJECT_NAME} PUBLIC ${JsonFactory_DEFINITIONS})

target_link_directories(${PROJECT_NAME} PUBLIC ${JsonFactory_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${JsonFactory_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC JsonFactory)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
        )

set(${PROJECT_NAME}_DEFINITIONS
        CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE
        )
