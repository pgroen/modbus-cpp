# ****************************************************************
# Copyright (c)2022 Peter M. Groen
# This file is licensed under the MIT license found in the 
# LICENSE file in the root directory of this source tree.
# ****************************************************************
add_executable(modbustest
    connectionconfigtest.cpp
    requesttest.cpp
)

target_include_directories(modbustest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(modbustest PRIVATE
    gmock_main
    gmock
    gtest
    modbus-cpp
)

add_test(NAME modbustest COMMAND modbustest)

set_tests_properties(modbustest PROPERTIES
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
