project(gg LANGUAGES CXX)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_COLOR_MAKEFILE ON)

# Defines the variable GG_SOURCES
set(GG_SOURCES
	src/core/gg.hh src/core/gg.cc	
	src/core/gg_element.hh src/core/gg_element.cc
	src/core/gg_window.hh src/core/gg_window.cc
	src/widgets/gg_button.hh src/widgets/gg_button.cc
	examples/main.cc
)

# Adds a new (executable) target called gg
add_executable(gg ${GG_SOURCES})

# Specify libraries or flags to use when linking the target gg
target_link_libraries(gg SDL2 SDL2_ttf)
