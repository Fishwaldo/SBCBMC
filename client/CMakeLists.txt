cmake_minimum_required(VERSION 3.1.0)

project(sbcbmc-client VERSION 0.0.1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

cmake_policy(SET CMP0071 NEW)


find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS RemoteObjects REQUIRED)
find_package(Qt5 COMPONENTS Qml REQUIRED)
find_package(Qt5 COMPONENTS Quick REQUIRED)
find_package(Qt5 COMPONENTS QuickControls2 REQUIRED)
find_package(Qt5 COMPONENTS Charts REQUIRED)

find_package(PkgConfig REQUIRED) 

#configure_file(include/config.h.in include/config.h)

set(HEADERS
    include/client.hpp
    )
set(SOURCES
    source/main.cpp
    source/client.cpp
    )
qt5_generate_repc(REPSOURCES
    ${CMAKE_SOURCE_DIR}/plugins/dcdc-usb-200/source/dcdc_usb_200.rep
    REPLICA
    )
qt5_generate_repc(REPSOURCES
    ${CMAKE_SOURCE_DIR}/plugins/thermal/source/thermal.rep
    REPLICA
    )


add_executable(sbcbmc-client
    ${SOURCES}
    ${HEADERS}
    ${REPSOURCES}
    sbcbmc-client.qrc
    qml/qml.qrc
    imagine-assets/imagine-assets.qrc
    icons/icons.qrc
)

target_include_directories(sbcbmc-client PRIVATE
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/include/"
                           "${PROJECT_SOURCE_DIR}/plugins/dcdc-usb-200/include/"
                           "${PROJECT_SOURCE_DIR}/plugins/thermal/include/"
                           ${LibUSB_INCLUDE_DIRS}
                           )

target_link_libraries(sbcbmc-client Qt5::Core Qt5::RemoteObjects Qt5::Qml Qt5::Quick Qt5::Charts)