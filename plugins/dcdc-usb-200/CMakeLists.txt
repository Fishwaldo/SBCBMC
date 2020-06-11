cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

cmake_policy(SET CMP0071 NEW)


find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS RemoteObjects REQUIRED)
find_package(PkgConfig REQUIRED) 

pkg_check_modules(LibUSB REQUIRED libusb)


set(HEADERS
    include/dcdc-usb.h
    include/dcdc-usb-200.h
    )
set(SOURCES
    source/dcdc-usb-comm.c
    source/dcdc-usb-parse.c
    source/dcdc-usb-proto.c
    source/dcdc-usb-200.cpp
    )
qt5_generate_repc(REPSOURCES
    source/dcdc_usb_200.rep
    SOURCE
    )
#qt5_generate_repc(REPSOURCES
#    source/dcdc_usb_200.rep
#    REPLICA
#    )    



add_library(dcdc-usb-200
    STATIC
    ${SOURCES}
    ${HEADERS}
    ${REPSOURCES}
)

target_include_directories(dcdc-usb-200 PRIVATE
                           "${PROJECT_BINARY_DIR}"
                           "${CMAKE_SOURCE_DIR}/car/include/"
                           ${LibUSB_INCLUDE_DIRS}
                           )

target_include_directories(dcdc-usb-200 PUBLIC
                            "${PROJECT_SOURCE_DIR}/dcdc-usb-200/"
                            "${PROJECT_SOURCE_DIR}/dcdc-usb-200/include/"
                            "${CMAKE_CURRENT_BINARY_DIR}"
                            )

target_link_libraries(dcdc-usb-200 ${LibUSB_LIBRARIES})
target_link_libraries(dcdc-usb-200 Qt5::Core Qt5::RemoteObjects)