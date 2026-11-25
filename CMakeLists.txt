cmake_minimum_required(VERSION 3.16)
project(hello_systemc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SystemCLanguage CONFIG REQUIRED HINTS /opt/systemc)

add_executable(hello_systemc src/main.cpp)

target_link_libraries(hello_systemc PRIVATE SystemC::systemc m)

add_executable(aritmetic_s src/aritmetic_mod.cpp)

target_link_libraries(aritmetic_s PRIVATE SystemC::systemc m)

add_executable(timer_s src/timer_mod.cpp)

target_link_libraries(timer_s PRIVATE SystemC::systemc m)

add_executable(adc_s src/adc_mod.cpp)

target_link_libraries(adc_s PRIVATE SystemC::systemc m)
