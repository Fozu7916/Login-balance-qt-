cmake_minimum_required(VERSION 3.16)
project(LoginBalanceTests)

# Находим необходимые пакеты Qt
find_package(Qt6 REQUIRED COMPONENTS Test Sql Core Widgets)

# Включаем автоматическую обработку MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Устанавливаем путь для генерации moc-файлов
set(CMAKE_AUTOMOC_MOC_OPTIONS "-o${CMAKE_CURRENT_BINARY_DIR}")

# Добавляем путь к исходному коду
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Добавляем исполняемый файл тестов
add_executable(tests
    test_auth_controller.cpp
    ../src/model/database.cpp
    ../src/model/users.cpp
    ../src/controller/authcontroller.cpp
    ../src/view/errorwindow.cpp
)

# Подключаем библиотеки
target_link_libraries(tests PRIVATE
    Qt6::Test
    Qt6::Sql
    Qt6::Core
    Qt6::Widgets
)

# Добавляем тест
add_test(NAME tests COMMAND tests) 
