cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
cmake_policy(SET CMP0071 NEW)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

cmake_policy(SET CMP0071 NEW)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS RemoteObjects REQUIRED)



set(HEADERS
    include/thermal.h
    )
set(SOURCES
    source/thermal.cpp
    )
qt5_generate_repc(REPSOURCES
    source/thermal.rep
    SOURCE
    )



add_library(thermal
    STATIC
    ${SOURCES}
    ${HEADERS}
    ${REPSOURCES}
)

target_include_directories(thermal PRIVATE
                           "${PROJECT_BINARY_DIR}"
                           "${CMAKE_SOURCE_DIR}/car/include/"
                           )

target_include_directories(thermal PUBLIC
                           "${PROJECT_SOURCE_DIR}/thermal/"
                           "${PROJECT_SOURCE_DIR}/thermal/include/"
                           "${CMAKE_CURRENT_BINARY_DIR}"
                           )


target_link_libraries(thermal Qt5::Core Qt5::RemoteObjects)