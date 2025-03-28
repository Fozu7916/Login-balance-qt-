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

# ==================== MySQL ====================
# Проверка наличия MySQL client library
if(WIN32)
    find_file(MYSQL_DLL libmysql.dll
        PATHS "C:/Program Files/MySQL/MySQL Server 8.0/lib"
        DOC "Path to MySQL client library"
    )
else()
    find_package(MySQL REQUIRED)
endif()

# ==================== Источники ====================
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp src/mainwindow.ui src/mainwindow.h
    src/moneywindow.cpp src/moneywindow.h src/moneywindow.ui
    src/Users.cpp src/Users.h
    src/errorwindow.cpp src/errorwindow.h src/errorwindow.ui
    src/moneychange.cpp src/moneychange.h src/moneychange.ui
    src/changebackground.h src/changebackground.cpp
    src/registrwindow.h src/registrwindow.cpp src/registrwindow.ui
    src/database.h src/database.cpp
    resources/resources.qrc
)

# ==================== Исполняемый файл ====================
qt_add_executable(Log+MoneyChange
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    src/authcontroller.h src/authcontroller.cpp


)

# ==================== Линковка ====================
target_link_libraries(Log+MoneyChange PRIVATE
    Qt6::Widgets
    Qt6::Sql
)

if(UNIX AND NOT APPLE)
    target_link_libraries(Log+MoneyChange PRIVATE mysqlclient)
endif()

# ==================== Копирование DLL (Windows) ====================
if(WIN32 AND MYSQL_DLL)
    add_custom_command(TARGET Log+MoneyChange POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${MYSQL_DLL}"
            "$<TARGET_FILE_DIR:Log+MoneyChange>"
        COMMENT "Copying MySQL DLL to output directory"
    )
endif()

# ==================== Настройки платформ ====================
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
