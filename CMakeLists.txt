cmake_minimum_required(VERSION 3.5)
project(BakerNumbers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:\\Users\\Kim\\Google Drive\\BakerNumbers\\bin")

set(SOURCE_FILES main.cpp)
add_executable(BakerNumbers ${SOURCE_FILES})