cmake_minimum_required(VERSION 3.15.0)

project("orbitalsim")

set(CMAKE_CXX_STANDARD 11)

# From "Working with CMake" documentation:
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # AddressSanitizer (ASan)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # UndefinedBehaviorSanitizer (UBSan)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
endif()

add_executable(orbitalsim main.cpp OrbitalSim.cpp View.cpp)

# Raylib
find_package(raylib CONFIG REQUIRED)

target_include_directories(orbitalsim PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(orbitalsim PRIVATE ${raylib_LIBRARIES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # From "Working with CMake" documentation:
    target_link_libraries(orbitalsim PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(orbitalsim PRIVATE m ${CMAKE_DL_LIBS} pthread GL rt X11)
endif()
