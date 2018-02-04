cmake_minimum_required(VERSION 3.8.2)
project(bdbvu)

if(NOT ${CMAKE_VERSION} VERSION_LESS "3.10.0")
  cmake_policy(SET CMP0071 NEW)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(BerkeleyDB REQUIRED)

set(SOURCES
    main.cpp
    mainwindow.cpp
    database.cpp
)

set(HEADERS
    mainwindow.h
    database.h
)

set(FORMS
  mainwindow.ui
)

qt5_wrap_ui(FORM_GENERATED_FILES
  ${FORMS}
)

add_definitions(
  -DHAVE_CXX_STDHEADERS
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORM_GENERATED_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${BERKELEY_DB_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets ${BERKELEY_DB_LIBRARY_DIR}/${BERKELEY_DB_LIBRARIES})
