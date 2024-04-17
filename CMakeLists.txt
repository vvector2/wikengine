cmake_minimum_required(VERSION 3.1)

project(WikEngine)

file(GLOB ENGINE_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/Engine/Src/Core/*.cpp ${PROJECT_SOURCE_DIR}/Engine/Src/Core/*.h
        ${PROJECT_SOURCE_DIR}/Engine/Src/Core/Helpers/*.cpp ${PROJECT_SOURCE_DIR}/Engine/Src/Core/Helpers/*.h)


add_executable(main
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/external/imgui/imconfig.h
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui_demo.cpp
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui_draw.cpp
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui_impl_glfw.cpp
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui_impl_glfw.h
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui_impl_opengl3.cpp
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui_impl_opengl3.h
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui_internal.h
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui.cpp
        ${PROJECT_SOURCE_DIR}/external/imgui/imgui.h
        ${PROJECT_SOURCE_DIR}/external/imgui/imstb_rectpack.h
        ${PROJECT_SOURCE_DIR}/external/imgui/imstb_textedit.h
        ${PROJECT_SOURCE_DIR}/external/imgui/imstb_truetype.h
        ${ENGINE_SRC}
        Engine/Src/Core/RigidbodyComponent.cpp
        Engine/Src/Core/ColliderComponent.cpp
        Engine/Src/Core/ColliderComponent.h
)


set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_compile_options(main PRIVATE -Wall)

add_subdirectory(external/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)

add_definitions(-DGLEW_STATIC)
add_subdirectory(external/glew EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE libglew_static)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)

target_include_directories(main PRIVATE
        ${PROJECT_SOURCE_DIR}/external/imgui
)

IF (WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
ENDIF ()

find_package(ReactPhysics3D REQUIRED)

if (WIN32)
    list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\ReactPhysics3D")
elseif (APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake/ReactPhysics3D")
endif ()

target_link_libraries(main PRIVATE ReactPhysics3D::ReactPhysics3D)

