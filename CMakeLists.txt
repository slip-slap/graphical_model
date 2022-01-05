cmake_minimum_required(VERSION 3.5)

project(GM LANGUAGES CXX)

set(CMAKE_PREFIX_PATH /usr/local/Cellar/qt@5/5.15.2_1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(${CMAKE_SOURCE_DIR})


find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Boost 1.76.0 REQUIRED COMPONENTS ALL)

file(COPY "resource" DESTINATION ".")
set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        mainwindow.ui
        src/gmobject.h
        src/gmgraphicsview.cpp
        src/gmgraphicsview.h
        src/gmscene.cpp
        src/gmscene.h
        src/gmnode.cpp
        src/gmnode.h
        src/gmedge.cpp
        src/gmedge.h
        src/gmsocket.cpp
        src/gmsocket.h

        src/gmqtgraphicssocket.cpp
        src/gmqtgraphicssocket.h
        src/gmqtgraphicsscene.h
        src/gmqtgraphicsscene.cpp
        src/gmqtgraphicsnode.cpp
        src/gmqtgraphicsnode.h
        src/gmqtgraphicsedge.cpp
        src/gmqtgraphicsedge.h
        src/gmqtgraphicscuttingline.cpp
        src/gmqtgraphicscuttingline.h
        src/gmsocketinterface.h

        src/stocknodeinterface.h
        src/stockedgeinterface.h
        src/gmserializable.h
        src/stocksceneinterface.h

        src/gmserializable.h
)

include_directories(./src)
include_directories(./include)

qt5_add_resources(PROJECT_SOURCES resource.qrc)


add_executable(GM ${PROJECT_SOURCES})
target_include_directories(GM PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(GM PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(GM PRIVATE ${Boost_LIBRARIES})

#add_library(GMLIBRARY ${GM})

add_subdirectory(test)
