include_directories(include_directories(${Linux-Sysinternals_SOURCE_DIR}/src/procexp/helper))

add_executable(test_procexp_helper
    test_procexp_helper.cpp
    testhelper.cpp
)

target_link_libraries(test_procexp_helper
    helper
)
