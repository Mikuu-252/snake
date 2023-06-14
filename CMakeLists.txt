cmake_minimum_required (VERSION 3.24)

# Tu wstawcie nazwę swojego projektu
project (snake-mw-sr17-272241)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )

IF (WIN32)
    set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


add_executable(snake main.cpp Snake.cpp Snake.h Game.cpp Game.h Food.cpp Food.h)
target_link_libraries(snake sfml-graphics)