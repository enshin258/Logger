cmake_minimum_required(VERSION 3.16)

project(Logger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(Logger
    main.cpp
    src/models/LoggerDataModel.h
    src/models/LoggerDataModel.cpp
    src/models/LoggerDataSortFilterProxyModel.h
    src/models/LoggerDataSortFilterProxyModel.cpp
    src/datasets/LogEntry.h
    src/datasets/LogEntry.cpp
    src/controllers/ExternalAppsController.h
    src/controllers/ExternalAppsController.cpp
)

qt_add_qml_module(Logger
    URI Logger
    VERSION 1.0
    QML_FILES
    qml/utilities/Theme.qml
    qml/panels/LogsPanel.qml
    qml/MainPage.qml
    main.qml
)

add_subdirectory(testApps)

set_target_properties(Logger PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(Logger
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Logger
    PRIVATE Qt6::Quick)
