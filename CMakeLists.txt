cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
#set(SDL2_DIR "${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.22/x86_64-w64-mingw32")
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.22")



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(editor)

message("Lib: ${SDL2_DIR}")

# Packages and includes
find_package(SDL2 REQUIRED)
#find_package(nlohmann_json 3.2.0 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories("lib/SDL2_image-2.0.5/include")
include_directories("lib")
include_directories("lib/imgui")
include_directories("lib/json/single_include")

include_directories("lib/nativefiledialog/src/include")
include_directories("lib/imnodes")

message("Lib: ${SDL2_LIBRARY}")



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

        lib/nativefiledialog/src/nfd_common.c
        lib/nativefiledialog/src/nfd_win.cpp

        lib/imnodes/imnodes.cpp

        src/model/Map.cpp
        src/model/Palette.cpp
        src/ProjectManager.cpp
        src/model/Project.cpp src/model/Texture.cpp include/model/Texture.h)

# Executable
add_executable(editor ${SOURCE_FILES})

if(WIN32 AND NOT MSVC)
    set(APPFLAGS "${FLAGS} -municode -mconsole")
    set(APPFLAGS "${FLAGS} -mconsole --static -static-libgcc -static-libstdc++")
    set_target_properties(editor PROPERTIES LINK_FLAGS "${APPFLAGS}")
#    set(CMAKE_EXE_LINK_DYNAMIC_C_FLAGS)
#    set(CMAKE_EXE_LINK_DYNAMIC_CXX_FLAGS)
endif()

# Main headers
target_include_directories(editor PRIVATE "include")

# Add libs
target_link_libraries(editor
        ${SDL2_LIBRARIES}
        "${CMAKE_SOURCE_DIR}/lib/SDL2_image-2.0.5/lib/x64/SDL2_image.lib"
        )

# Copy SDL.dll to build output
if(WIN32)
    add_custom_command(TARGET editor POST_BUILD
            MAIN_DEPENDENCY "${SDL2_LIBRARY}"
            BYPRODUCTS "${SDL2_LIBRARY_NAME}"
            COMMENT "Copying SDL2 DLL"
            #COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_DIR}/bin/SDL2.dll" "$<TARGET_FILE_DIR:editor>/${SDL2_LIBRARY_NAME}"
            COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_DIR}/lib/x64/SDL2.dll" "$<TARGET_FILE_DIR:editor>/${SDL2_LIBRARY_NAME}"
            )
    add_custom_command(TARGET editor POST_BUILD
            COMMENT "Copying SDL2 DLL"
            COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_SOURCE_DIR}/lib/SDL2_image-2.0.5/lib/x64/SDL2_image.dll" "$<TARGET_FILE_DIR:editor>/SDL2_image.dll"
            )
    add_custom_command(TARGET editor POST_BUILD
            COMMENT "Copying SDL2 DLL"
            COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_SOURCE_DIR}/lib/SDL2_image-2.0.5/lib/x64/libpng16-16.dll" "$<TARGET_FILE_DIR:editor>/libpng16-16.dll"
            )
    add_custom_command(TARGET editor POST_BUILD
            COMMENT "Copying SDL2 DLL"
            COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_SOURCE_DIR}/lib/SDL2_image-2.0.5/lib/x64/zlib1.dll" "$<TARGET_FILE_DIR:editor>/zlib1.dll"
            )

endif()

#configure_file("demo-proj/project.json" "demo-proj/project.json" COPYONLY)

add_custom_command(TARGET editor POST_BUILD
        COMMENT "Copying Demo Project"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/demo-proj" "${CMAKE_BINARY_DIR}/demo-proj"
)
