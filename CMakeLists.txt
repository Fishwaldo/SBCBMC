cmake_minimum_required(VERSION 3.1.0)

project(sbcbmc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()



add_subdirectory(plugins)
add_subdirectory(agent)
add_subdirectory(client)
