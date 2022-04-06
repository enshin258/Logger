cmake_minimum_required(VERSION 3.16)

project(Logger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED Sql)

qt_add_executable(Logger
    main.cpp
    src/templates/MyVector.h
    src/models/LoggerDataModel.h
    src/models/LoggerDataModel.cpp
    src/models/LoggerDataSortFilterProxyModel.h
    src/models/LoggerDataSortFilterProxyModel.cpp
    src/datasets/LogEntry.h
    src/datasets/LogEntry.cpp
    src/controllers/BasicController.h
    src/controllers/BasicController.cpp
    src/controllers/FileController.h
    src/controllers/FileController.cpp
    src/controllers/NetworkController.h
    src/controllers/NetworkController.cpp
    src/controllers/DatabaseController.h
    src/controllers/DatabaseController.cpp
    src/providers/ExternalAppProvider.h
    src/providers/ExternalAppProvider.cpp
)

qt_add_qml_module(Logger
    URI Logger
    VERSION 1.0
    QML_FILES
    qml/elements/AppText.qml
    qml/elements/AppButton.qml
    qml/utilities/Theme.qml
    qml/panels/LogsPanel.qml
    qml/panels/NetworkPanel.qml
    qml/panels/FilePanel.qml
    qml/panels/ExecutablePanel.qml
    qml/panels/SearchingAndFilteringPanel.qml
    qml/MainPage.qml
    main.qml
)

add_subdirectory(testApps)
add_subdirectory(server)

target_compile_definitions(Logger
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Logger
    PRIVATE Qt6::Quick Qt6::Sql)
