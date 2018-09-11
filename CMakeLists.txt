cmake_minimum_required(VERSION 3.2)

project(gg VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_COLOR_MAKEFILE ON)

# Defines the variable GG_SOURCES.
set(GG_SOURCES
	src/core/gg.hh src/core/gg.cc	
	src/core/gg_element.hh src/core/gg_element.cc
	src/core/gg_window.hh src/core/gg_window.cc
	src/widgets/gg_button.hh src/widgets/gg_button.cc
	examples/main.cc)

# Adds a new (executable) target called gg.
add_executable(gg ${GG_SOURCES})

# Finds the required libraries. 
find_library(SDL2_FOUND SDL2)
find_library(SDL2_TTF_FOUND SDL2_ttf)

# Fatal error if a library is missing from the system.
if (NOT SDL2_FOUND)
	message(FATAL_ERROR "SDL2 not found")
endif()
if (NOT SDL2_TTF_FOUND)
	message(FATAL_ERROR "SDL2_ttf not found")
endif()

# Specify libraries or flags to use when linking the target gg.
target_link_libraries(gg SDL2 SDL2_ttf)


