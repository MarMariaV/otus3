cmake_minimum_required(VERSION 3.2)

project(otus3)

add_executable(otus3 main.cpp)

if (MSVC)
    target_compile_options(otus3 PRIVATE
        /W4
    )
else ()
    target_compile_options(otus3 PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

