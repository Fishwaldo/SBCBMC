cmake_minimum_required(VERSION 3.1.0)

project(sbcbmc-agent VERSION 0.0.1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS RemoteObjects REQUIRED)

find_package(PkgConfig REQUIRED) 

pkg_check_modules(LibUSB REQUIRED libusb)

configure_file(include/config.h.in include/config.h)

set(HEADERS
    include/daemon.h
    include/pluginbase.h
    )
set(SOURCES
    source/main.cpp
    source/daemon.cpp
    source/pluginbase.cpp
    )

add_executable(sbcbmc-agent
    ${SOURCES}
    ${HEADERS}
    ${REPSOURCES}
)

target_include_directories(sbcbmc-agent PRIVATE
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/include/"
                           "${CMAKE_SOURCE_DIR}/plugins/thermal/include/"
                           "${CMAKE_SOURCE_DIR}/plugins/thermal/"
                           ${LibUSB_INCLUDE_DIRS}
                           )

target_link_libraries(sbcbmc-agent ${LibUSB_LIBRARIES})
target_link_libraries(sbcbmc-agent Qt5::Core Qt5::RemoteObjects)
target_link_libraries(sbcbmc-agent thermal dcdc-usb-200)