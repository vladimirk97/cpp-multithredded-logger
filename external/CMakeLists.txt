set(CMAKE_CXX_STANDARD 17)

add_subdirectory(cpp-thread-safe-queue)

if(NOT TARGET gtest AND NOT TARGET gmock AND NOT TARGET gtest_main AND NOT TARGET gmock_main)
    # Include googletest or add it as a submodule if it’s not already included
    add_subdirectory(googletest)
endif()