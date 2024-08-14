if(BUILD_TESTING)
    set(THIS multithreded_logger_test)
    add_executable(${THIS} ${THIS}.cpp)

    target_link_libraries(${THIS}
        PRIVATE GTest::gtest_main
        PUBLIC ${PROJECT}
    )

    include(GoogleTest)
    gtest_discover_tests(${THIS})
endif()