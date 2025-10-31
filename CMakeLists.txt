cmake_minimum_required(VERSION 3.20)
project(pong LANGUAGES CXX)

# Defaults: C++20, warnings on
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
add_executable(pong
  src/main.cpp
  src/sdlApp.cpp
  src/pong.cpp
)

target_include_directories(pong PRIVATE include)

# Find SDL2 installed from apt (libsdl2-dev)
find_package(SDL2 REQUIRED)                    # fails fast if not found
target_link_libraries(pong PRIVATE SDL2::SDL2 SDL2::SDL2main)
# include dirs come from the imported targets, so no manual include paths needed

# --- If you’ll use raylib later, uncomment these lines ---
# find_package(raylib QUIET) # works if libraylib-dev is installed
# if (raylib_FOUND)
#   target_link_libraries(pong PRIVATE raylib)
#   target_compile_definitions(pong PRIVATE USE_RAYLIB)
# endif()

