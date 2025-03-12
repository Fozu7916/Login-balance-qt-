cmake_minimum_required(VERSION 3.16)

project(Log+MoneyChange VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==================== Qt ====================
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# ==================== Источники ====================
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp src/mainwindow.ui src/mainwindow.h
    src/moneywindow.cpp src/moneywindow.h src/moneywindow.ui
    src/Users.cpp src/Users.h
    src/errorwindow.cpp src/errorwindow.h src/errorwindow.ui
    src/moneychange.cpp src/moneychange.h src/moneychange.ui
    resources/resources.qrc
)

# ==================== Исполняемый файл ====================
qt_add_executable(Log+MoneyChange
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    src/changebackground.h
    src/changebackground.cpp
)

# ==================== Линковка ====================
target_link_libraries(Log+MoneyChange PRIVATE
    Qt6::Widgets
    Qt6::Sql
)

set_target_properties(Log+MoneyChange PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Log+MoneyChange
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Log+MoneyChange)
endif()
