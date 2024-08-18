if(BUILD_TESTING)
    set(THIS multithreaded_logger_test)

    file(GLOB_RECURSE test_files
        "${TOP_LEVEL_CMAKE_DIR}/test/*.cpp"
    )

    add_executable(${THIS} 
        ${test_files}
    )
    
    target_include_directories(${THIS} 
        PRIVATE 
            ${TOP_LEVEL_CMAKE_DIR}/source
            # ${TOP_LEVEL_CMAKE_DIR}/include
    )

    target_link_libraries(${THIS}
        PRIVATE GTest::gtest_main
        PUBLIC ${PROJECT_NAME}
    )

    include(GoogleTest)
    gtest_discover_tests(${THIS})
endif()