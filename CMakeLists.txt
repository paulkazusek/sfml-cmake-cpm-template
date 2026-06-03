cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

# Fix for older dependencies (e.g. freetype) with CMake < 3.5
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(
    sfml-template
    VERSION 0.0.0
    LANGUAGES CXX 
)

# By default, hide the console window on Windows for a clean graphical experience.
# Set SHOW_CONSOLE to ON in your CMake settings if you need debug output.
option(SHOW_CONSOLE "Show console window (useful for debugging)" OFF)

# Load dependencies using CPM
include(${PROJECT_SOURCE_DIR}/dependencies.cmake)

# Source files
set(SOURCES
    src/main.cpp
)

# MSVC-specific settings
if(WIN32 AND NOT SHOW_CONSOLE)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()

# MSVC
if(MSVC)
    # Set as startup project in Visual Studio .sln
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    # Enable multicore compilation
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()

# C++20 standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics 
    $<$<PLATFORM_ID:Windows>:SFML::Main>
)

# Generate version header from template
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.hpp
    @ONLY
)

# Add generated header directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)

# Install executable
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin COMPONENT Runtime)

# CPack packaging settings
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP")

# Set the installation path to a directory without spaces
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})

# Enable CPack packaging
include(CPack)

# Override CPack components at cpack runtime via a project config file
set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/CPackOverride.cmake")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CPackOverride.cmake"
  "set(CPACK_COMPONENTS_ALL Runtime)\n")
