cmake_minimum_required(VERSION 3.0)
project(modbus-cpp)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/submodules/cmake)

# ==============================================================================
# = Include build information
include(projectheader)
project_header(modbus-cpp)

add_subdirectory(modbus-master)
# add_subdirectory(modbus-slave)
