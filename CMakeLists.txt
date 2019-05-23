cmake_minimum_required(VERSION 3.2)

project(gg VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_COLOR_MAKEFILE ON)

# Debug mode for now
set(CMAKE_BUILD_TYPE Debug)

# Defines the variable GG_SOURCES.
set(GG_SOURCES
	src/core/gg.hh src/core/gg.cc
    src/core/gg_events.hh src/core/gg_events.cc
	src/core/gg_renderer.hh src/core/gg_renderer.cc
    src/core/gg_element.hh src/core/gg_element.cc
	src/core/gg_window.hh src/core/gg_window.cc
	src/widgets/gg_button.hh src/widgets/gg_button.cc
	examples/main.cc)

# Adds a new (executable) target called gg.
add_executable(gg ${GG_SOURCES})

# Finds the required libraries. 
find_library(LIB_SDL2 SDL2)
find_library(LIB_SDL2_TTF SDL2_ttf)

# Fatal error if a library is missing from the system.
if (NOT LIB_SDL2)
	message(FATAL_ERROR "SDL2 not found")
endif()
if (NOT LIB_SDL2_TTF)
	message(FATAL_ERROR "SDL2_ttf not found")
endif()

# Specify libraries or flags to use when linking the target gg. These will 
# become linker flags such as -lSDL2 and -lSDL2_ttf.
target_link_libraries(gg SDL2 SDL2_ttf)


