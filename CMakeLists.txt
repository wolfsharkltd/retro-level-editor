cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.22/x86_64-w64-mingw32")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(editor)

# Packages and includes
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories("lib")
include_directories("lib/imgui")

# Sources
set(SOURCE_FILES
        src/main.cpp
        lib/imgui/imconfig.h
        lib/imgui/imgui.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui.h
        lib/imgui/imgui_demo.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_internal.h
        lib/imgui/imgui_widgets.cpp
        lib/imgui/imstb_rectpack.h
        lib/imgui/imstb_textedit.h
        lib/imgui/imstb_truetype.h
        lib/imgui/backends/imgui_impl_sdlrenderer.cpp
        lib/imgui/backends/imgui_impl_sdlrenderer.h
        lib/imgui/backends/imgui_impl_sdl.cpp
        lib/imgui/backends/imgui_impl_sdl.h
        )

# Executable
add_executable(editor ${SOURCE_FILES})

# Add libs
target_link_libraries(editor ${SDL2_LIBRARIES})

# Copy SDL.dll to build output
if(WIN32)
    add_custom_command(TARGET editor POST_BUILD
            MAIN_DEPENDENCY "${SDL2_LIBRARY}"
            BYPRODUCTS "${SDL2_LIBRARY_NAME}"
            COMMENT "Copying SDL2 DLL"
            COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_DIR}/bin/SDL2.dll" "$<TARGET_FILE_DIR:editor>/${SDL2_LIBRARY_NAME}"
            )
endif()
