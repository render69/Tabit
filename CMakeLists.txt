cmake_minimum_required(VERSION 3.5)
project(Tabit)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)
set(SOURCES
    main.cpp
    browserwindow.cpp
    customwebpage.cpp
)
set(HEADERS
    browserwindow.h
    customwebpage.h
)
qt6_wrap_cpp(MOC_SOURCES ${HEADERS})
add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES})
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::WebEngineWidgets)
