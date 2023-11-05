cmake_minimum_required(VERSION 3.22.1)

project(AngryBirds VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCES_CPP CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB SOURCES_H CONFIGURE_DEPENDS "src/*.h")
set(SOURCES ${SOURCES_CPP} ${SOURCES_H})

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME})

target_sources(${EXECUTABLE_NAME} PUBLIC ${SOURCES})

# Add SFML
set(SFML_DIR "libs/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS audio graphics window system REQUIRED)
if (SFML_FOUND)
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
endif()

# Get a lot of warnings and make all warnings into errors
if(MSVC)
    target_compile_options(${EXECUTABLE_NAME} PRIVATE /Wall /WX)
else()
    target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wno-missing-field-initializers -Werror -pedantic)
endif()