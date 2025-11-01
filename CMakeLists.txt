cmake_minimum_required(VERSION 3.20)
project(pong LANGUAGES CXX)

# ---- Language / warnings ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Sources ----
add_executable(pong
  src/main.cpp
  src/sdlApp.cpp
  src/pong.cpp
)
target_include_directories(pong PRIVATE include)

set(_sdl2_found_targets OFF)
find_package(SDL2 QUIET CONFIG)   
if (SDL2_FOUND AND TARGET SDL2::SDL2)
  set(_sdl2_found_targets ON)
  target_link_libraries(pong PRIVATE SDL2::SDL2)
  if (TARGET SDL2::SDL2main)
    target_link_libraries(pong PRIVATE SDL2::SDL2main)
  endif()
endif()

if (NOT _sdl2_found_targets)
  # Try module mode (older CMake/OS packagers); may expose legacy vars.
  find_package(SDL2 REQUIRED)            # Module mode
  if (TARGET SDL2::SDL2)
    target_link_libraries(pong PRIVATE SDL2::SDL2)
    if (TARGET SDL2::SDL2main)
      target_link_libraries(pong PRIVATE SDL2::SDL2main)
    endif()
  else()
    # Legacy variables path (older FindSDL2)
    # SDL2_INCLUDE_DIRS, SDL2_LIBRARIES are expected.
    target_include_directories(pong PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(pong PRIVATE ${SDL2_LIBRARIES})
  endif()
endif()

# On Windows/MSVC, if you don’t want to link SDL2main, define SDL_MAIN_HANDLED
# and provide your own 'int main(...)'. Uncomment if you choose that route:
# if (WIN32)
#   target_compile_definitions(pong PRIVATE SDL_MAIN_HANDLED)
# endif()

# If you later add raylib, keep it optional and harmless when missing:
# find_package(raylib QUIET)
# if (raylib_FOUND)
#   target_link_libraries(pong PRIVATE raylib)
#   target_compile_definitions(pong PRIVATE USE_RAYLIB)
# endif()

