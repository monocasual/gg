cmake_minimum_required(VERSION 3.2)

project(gg VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_COLOR_MAKEFILE ON)

# Enable C++17.
set(CMAKE_CXX_STANDARD 17)

# Debug mode for now
set(CMAKE_BUILD_TYPE Debug)

# Defines the variable GG_SOURCES.
set(GG_SOURCES
	src/core/gg_const.hh
	src/core/gg.hh src/core/gg.cc
    src/core/gg_events.hh src/core/gg_events.cc
	src/core/gg_renderer.hh src/core/gg_renderer.cc
    src/core/gg_element.hh src/core/gg_element.cc
	src/core/gg_window.hh src/core/gg_window.cc
    src/core/gg_utils.hh
	src/widgets/gg_button.hh src/widgets/gg_button.cc
    src/widgets/gg_box.hh src/widgets/gg_box.cc
    src/widgets/gg_slider.hh src/widgets/gg_slider.cc
    src/widgets/gg_alert.hh src/widgets/gg_alert.cc
	examples/main.cc)

# Adds a new (executable) target called gg.
add_executable(gg ${GG_SOURCES})

# Set compiler flags
target_compile_options(gg PRIVATE -Wall -Werror)

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