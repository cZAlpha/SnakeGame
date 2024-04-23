cmake_minimum_required(VERSION 3.27)
project(Trash)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

# Start of OS dependant logic flow
if(CMAKE_SYSTEM_NAME MATCHES "Windows") # Windows
    message(STATUS "Configuring for Windows...")
    set(SDL2_PATH "C:/Users/Parents/Desktop/SDL2-2.30.0/x86_64-w64-mingw32") # Path to 'x86_64-w64-mingw32'
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin") # Mac
    find_package(SDL2 REQUIRED)
    include_directories("/usr/local/include/SDL2") # Adjust this path according to your installation
endif()

# Files to make the executable 'Trashman'
add_executable(Trash
        main.cpp
        Trashbag.cpp
        Trashbag.h
        Trashman.cpp
        Trashman.h
        Sprite.cpp
        Sprite.h
        )

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
