cmake_minimum_required(VERSION 3.16)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/submodules/cmake)

include(projectheader)
project_header(modbus-cpp)

include(compiler)

set(SRC_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/modbusbase.h
    ${CMAKE_CURRENT_SOURCE_DIR}/modbusbase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/modbustcp.h
    ${CMAKE_CURRENT_SOURCE_DIR}/modbustcp.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/modbusrtu.h
    #${CMAKE_CURRENT_SOURCE_DIR}/modbusrtu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/connectionconfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/connectionconfig.cpp
)

include(library)
add_libraries(PUBLIC
)

include(installation)
install_component()

