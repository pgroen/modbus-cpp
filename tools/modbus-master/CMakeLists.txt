cmake_minimum_required(VERSION 3.16)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/submodules/cmake)

include(projectheader)
project_header(modbus-master)

include(compiler)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

set(SRC_LIST
)

