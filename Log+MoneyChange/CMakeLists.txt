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
    src/main.cpp src/hashutils.h 
    src/changebackground.cpp src/changebackground.h

    #controller
    src/controller/authcontroller.h src/controller/authcontroller.cpp

    #view
    src/view/mainwindow.cpp src/view/mainwindow.ui src/view/mainwindow.h
    src/view/moneywindow.cpp src/view/moneywindow.h src/view/moneywindow.ui
    src/view/errorwindow.cpp src/view/errorwindow.h src/view/errorwindow.ui
    src/view/moneychange.cpp src/view/moneychange.h src/view/moneychange.ui
    src/view/registrwindow.h src/view/registrwindow.cpp src/view/registrwindow.ui

    #model
    src/model/Users.cpp src/model/Users.h
    src/model/database.h src/model/database.cpp

    #resources
    resources/resources.qrc

)

# ==================== Исполняемый файл ====================
qt_add_executable(Log+MoneyChange
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}


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

add_subdirectory(tests)

