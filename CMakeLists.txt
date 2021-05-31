cmake_minimum_required(VERSION 3.2)

project(gg VERSION 0.0.0 LANGUAGES CXX)

# ------------------------------------------------------------------------------
# Lists definition
#
# GG_SOURCES - contains the source files
# GG_PREPROCESSOR_DEFS - preprocessor definitions
# GG_INCLUDE_DIRS - include directories (e.g. -I)
# GG_COMPILER_OPTIONS - additional flags for the compiler
# GG_LIBRARIES - external dependencies to link
# GG_COMPILER_FEATURES - e.g. C++17
# GG_TARGET_PROPERTIES - additional properties for the main target.
# ------------------------------------------------------------------------------

list(APPEND GG_SOURCES)
list(APPEND GG_PREPROCESSOR_DEFS)
list(APPEND GG_INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src)
list(APPEND GG_COMPILER_OPTIONS)
list(APPEND GG_LIBRARIES)
list(APPEND GG_COMPILER_FEATURES cxx_std_17)
list(APPEND GG_TARGET_PROPERTIES)

# ------------------------------------------------------------------------------

list(APPEND GG_SOURCES
	${CMAKE_SOURCE_DIR}/src/core/gg.cc
	${CMAKE_SOURCE_DIR}/src/core/gg_events.cc
	${CMAKE_SOURCE_DIR}/src/core/gg_renderer.cc
	${CMAKE_SOURCE_DIR}/src/core/gg_element.cc
	${CMAKE_SOURCE_DIR}/src/core/gg_window.cc
	${CMAKE_SOURCE_DIR}/src/widgets/atoms/gg_button.cc
	${CMAKE_SOURCE_DIR}/src/widgets/atoms/gg_box.cc
	${CMAKE_SOURCE_DIR}/src/widgets/atoms/gg_slider.cc
	${CMAKE_SOURCE_DIR}/src/widgets/atoms/gg_input.cc
	${CMAKE_SOURCE_DIR}/src/widgets/gg_alert.cc
)

# ------------------------------------------------------------------------------

if(MSVC)
	list(APPEND GG_COMPILER_OPTIONS /W4)
else()
	list(APPEND GG_COMPILER_OPTIONS -Wall -Wextra -Wpedantic)
endif()

# ------------------------------------------------------------------------------

# Options

option(GG_BUILD_EXAMPLES "Build examples." ON)

if(GG_BUILD_EXAMPLES)
  add_subdirectory (examples)
endif()

# ------------------------------------------------------------------------------

# Dependencies

find_library(LIB_SDL2 SDL2)
find_library(LIB_SDL2_TTF SDL2_ttf)

if (NOT LIB_SDL2)
	message(FATAL_ERROR "SDL2 not found")
endif()
if (NOT LIB_SDL2_TTF)
	message(FATAL_ERROR "SDL2_ttf not found")
endif()

find_package(SDL2 REQUIRED)
list(APPEND GG_LIBRARIES SDL2 SDL2_ttf)

# ------------------------------------------------------------------------------

add_library(gg)
target_compile_features(gg PRIVATE ${GG_COMPILER_FEATURES})
target_sources(gg PRIVATE ${GG_SOURCES})
target_compile_definitions(gg PRIVATE ${GG_PREPROCESSOR_DEFS})
target_include_directories(gg PRIVATE ${GG_INCLUDE_DIRS})
target_link_libraries(gg PRIVATE ${GG_LIBRARIES})
target_compile_options(gg PRIVATE ${GG_COMPILER_OPTIONS})

set_target_properties(gg PROPERTIES VERSION ${PROJECT_VERSION})