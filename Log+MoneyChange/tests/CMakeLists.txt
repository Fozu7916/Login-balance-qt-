find_package(Qt6 REQUIRED COMPONENTS Test Sql)

add_executable(tests
    test_auth_controller.cpp
)

target_link_libraries(tests PRIVATE
    Qt6::Test
    Qt6::Sql
)

target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

add_test(NAME tests COMMAND tests) 