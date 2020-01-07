# specify CMake version
cmake_minimum_required(VERSION 3.11)

# call the CMakes in client/ and server/
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/client")
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/server")
