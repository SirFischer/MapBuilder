cmake_minimum_required(VERSION 3.10)
project(MapBuilder CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Add compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
else()
    add_compile_options(-g)
endif()

# Find SFML
find_package(SFML COMPONENTS system window graphics REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}/includes/Editor
    ${CMAKE_SOURCE_DIR}/includes/EditorSettings
    ${CMAKE_SOURCE_DIR}/includes/Element
    ${CMAKE_SOURCE_DIR}/includes/Map
    ${CMAKE_SOURCE_DIR}/includes/Menu
    ${CMAKE_SOURCE_DIR}/includes/Profile
    ${CMAKE_SOURCE_DIR}/includes/ResourceManager
    ${CMAKE_SOURCE_DIR}/includes/Settings
    ${CMAKE_SOURCE_DIR}/includes/StateManager
    ${CMAKE_SOURCE_DIR}/includes/System
	${CMAKE_SOURCE_DIR}/includes/Components
    ${CMAKE_SOURCE_DIR}/mfGUI/include
)

# Add mfGUI subdirectory
add_subdirectory(mfGUI)

# Explicitly list all source files
set(SOURCES
    srcs/main.cpp
    srcs/Editor/EditorState.cpp
    srcs/Editor/EditorWidget.cpp
    srcs/Editor/GUI.cpp
    srcs/EditorSettings/EditorSettings.cpp
    srcs/EditorSettings/GUI.cpp
    srcs/Element/Element.cpp
    srcs/Map/AdvancedExport.cpp
    srcs/Map/BasicExport.cpp
    srcs/Map/Map.cpp
    srcs/Menu/GUI.cpp
    srcs/Menu/MenuState.cpp
    srcs/Profile/GUI.cpp
    srcs/Profile/Profile.cpp
    srcs/Profile/ProfileState.cpp
    srcs/ResourceManager/ResourceManager.cpp
    srcs/Settings/SettingsState.cpp
    srcs/StateManager/State.cpp
    srcs/StateManager/StateManager.cpp
    srcs/System/InputManager.cpp
    srcs/System/Window.cpp
	srcs/Components/Button.cpp
)


set(HEADERS
	includes/Core.hpp
	includes/Editor/EditorState.hpp
	includes/Editor/EditorWidget.hpp
	includes/EditorSettings/EditorSettingsState.hpp
	includes/Element/Element.hpp
	includes/Map/ExportFormat.hpp
	includes/Map/Map.hpp
	includes/Menu/MenuState.hpp
	includes/Profile/Profile.hpp
	includes/Profile/ProfileState.hpp
	includes/ResourceManager/ResourceManager.hpp
	includes/Settings/SettingsState.hpp
	includes/StateManager/Data.hpp
	includes/StateManager/StateAction.hpp
	includes/StateManager/State.hpp
	includes/StateManager/StateManager.hpp
	includes/StateManager/States.hpp
	includes/System/InputAction.hpp
	includes/System/InputManager.hpp
	includes/System/Window.hpp
	includes/Components/Components.hpp
)

set(ALL_SOURCES
	${SOURCES}
	${HEADERS}
)

# Create executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
	sfml-audio
    ${CMAKE_CURRENT_SOURCE_DIR}/mfGUI/lib/libMFGUId.a
)

# Install targets
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Copy assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Enable testing
enable_testing()

# Add test target that runs the executable
add_test(
    NAME RunMapBuilder
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
