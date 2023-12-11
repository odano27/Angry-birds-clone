cmake_minimum_required(VERSION 3.22.1)

project(AngryBirds VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SOURCES_CPP CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE SOURCES_H CONFIGURE_DEPENDS "src/*.h")
file(GLOB_RECURSE SOURCES_HPP CONFIGURE_DEPENDS "src/*.hpp")
set(SOURCES ${SOURCES_CPP} ${SOURCES_H} ${SOURCES_HPP})

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME})

target_sources(${EXECUTABLE_NAME} PUBLIC ${SOURCES})
target_include_directories(${EXECUTABLE_NAME} PUBLIC "src")
target_include_directories(${EXECUTABLE_NAME} PUBLIC "src/include")
target_include_directories(${EXECUTABLE_NAME} PUBLIC "src/Core")
target_include_directories(${EXECUTABLE_NAME} PUBLIC "src/Level")
target_include_directories(${EXECUTABLE_NAME} PUBLIC "src/Entities")
target_include_directories(${EXECUTABLE_NAME} PUBLIC "src/UI")

# Add Box2d
find_library(LIBBOX2D box2d HINTS "libs/box2d/lib" REQUIRED)
target_include_directories(${EXECUTABLE_NAME} PUBLIC "libs/box2d/include/box2d")
target_link_libraries(${EXECUTABLE_NAME} ${LIBBOX2D})

# Add SFML
set(SFML_DIR "libs/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS audio graphics window system REQUIRED)
if (SFML_FOUND)
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
endif()

find_library(FLAC_LIBRARY NAMES FLAC PATHS "/libs/FLAC" REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} ${FLAC_LIBRARY})

# Get a lot of warnings and make all warnings into errors
if(MSVC)
    target_compile_options(${EXECUTABLE_NAME} PRIVATE /Wall /WX)
else()
    target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wno-missing-field-initializers -Werror -pedantic)
endif()

# Debug output
get_target_property(include_dirs ${EXECUTABLE_NAME} INCLUDE_DIRECTORIES)
foreach(dir ${include_dirs})
    message(STATUS "include='${dir}'")
endforeach()
foreach(file_h ${SOURCES_H})
    message(STATUS "header='${file_h}'")
endforeach()
foreach(file_hpp ${SOURCES_HPP})
    message(STATUS "header='${file_hpp}'")
endforeach()
foreach(file_cpp ${SOURCES_CPP})
    message(STATUS "source='${file_cpp}'")
endforeach()

file(GLOB_RECURSE assets "src/Assets/*")
foreach(asset ${assets})
    file(RELATIVE_PATH asset_rel ${CMAKE_SOURCE_DIR} ${asset})
    configure_file(${asset} ${CMAKE_BINARY_DIR}/${asset_rel} COPYONLY)
endforeach()