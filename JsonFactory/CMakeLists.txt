cmake_minimum_required(VERSION 3.5)
project(JsonFactory C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB JSON_HEADERS
        include/*.h
        include/*hpp
        )

file(GLOB JSON_SOURCE
        source/*.cpp
        )

find_package(Poco COMPONENTS Foundation Net REQUIRED)

add_library(${PROJECT_NAME} SHARED ${JSON_HEADERS} ${JSON_SOURCE})

target_compile_definitions(${PROJECT_NAME} PUBLIC ${Poco_DEFINITIONS})

target_link_directories(${PROJECT_NAME} PUBLIC ${Poco_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${Poco_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${Poco_LIBRARIES})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
        )

set(${PROJECT_NAME}_DEFINITIONS
        CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE
        )
