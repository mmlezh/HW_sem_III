cmake_minimum_required(VERSION 3.5)
## cmake .. cmake --build . ./main
project(main)

set(SOURCES 
		Main.cpp
		BitSet.cpp
)

add_executable(main ${SOURCES})

add_compile_options(
    -W
    -Wall
    -Wfloat-equal 
    -Wpointer-arith 
    -Wwrite-strings 
    -Wcast-align 
    -Wformat-security 
    -Wmissing-format-attribute 
    -Wformat=1
    -Wno-long-long 
    -Wcast-align 
    -Winline 
    -Werror 
    -pedantic 
    -pedantic-errors
    -Wunused 
    -Wuninitialized
    --param inline-unit-growth=1000000 
    --param max-inline-insns-single=10000000
)
