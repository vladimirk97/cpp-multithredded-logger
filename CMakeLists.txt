cmake_minimum_required(VERSION 3.22.1)

project(multithreded_logger)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC inc
)