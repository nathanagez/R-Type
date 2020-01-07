# specify CMake version
cmake_minimum_required(VERSION 3.11)

# set a name to the project and set it's language to C++
project(r-type_client CXX)

MESSAGE("> " ${PROJECT_NAME})

# a few settings for the executable
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

# add compilation flags (mainly used for the libraries)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio")

# load and setup conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# check for SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 EXACT REQUIRED COMPONENTS graphics window system)

# create sources list
file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/engine_src/*.cpp
        ${CMAKE_SOURCE_DIR}/common/src/*.cpp
)

# create the executable from the sources list
add_executable(${PROJECT_NAME} ${SOURCES})

# target linking settings
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

# include headers directory to the project
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/engine_include/
        ${CMAKE_SOURCE_DIR}/common/include/
)

# link conan libraries to the 'r-type_client' executable
target_link_libraries(${PROJECT_NAME}
        ${CONAN_LIBS}
        ${SFML_LIBRARIES}
        ${SFML_DEPENDENCIES}
)
