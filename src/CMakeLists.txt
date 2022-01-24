set(CMAKE_PREFIX_PATH /usr/local/Cellar/qt@5/5.15.2_1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Boost 1.76.0 REQUIRED COMPONENTS ALL)

file(COPY "../resource" DESTINATION ".")
set(PROJECT_SOURCES
        mainwindow.cpp
        mainwindow.ui
        gmgraphicsview.cpp
        gmscene.cpp
        gmnode.cpp
        gmedge.cpp
        gmsocket.cpp
        gmqtgraphicssocket.cpp
        gmqtgraphicsscene.cpp
        gmqtgraphicsnode.cpp
        gmqtgraphicsedge.cpp
        gmqtgraphicscuttingline.cpp

        gmqtlistwidget.cpp
)


qt5_add_resources(PROJECT_SOURCES ../resource.qrc)


add_executable(GM main.cpp ${PROJECT_SOURCES})
target_include_directories(GM INTERFACE .)
target_include_directories(GM INTERFACE ${GM_SOURCE_DIR}/include)
target_include_directories(GM INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(GM PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(GM PUBLIC ${Boost_LIBRARIES})



add_library(GMLIBRARY ${PROJECT_SOURCES})
target_include_directories(GMLIBRARY INTERFACE ${GM_SOURCE_DIR}/include)
target_include_directories(GMLIBRARY INTERFACE ${GM_SOURCE_DIR}/src)
target_link_libraries(GMLIBRARY PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(GMLIBRARY PUBLIC ${Boost_LIBRARIES})

