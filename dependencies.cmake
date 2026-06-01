file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.1/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    EXPECTED_HASH SHA256=f3a6dcc6a04ce9e7f51a127307fa4f699fb2bade357a8eb4c5b45df76e1dc6a5
    TLS_VERIFY ON
)

include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage(
    NAME SFML
    GITHUB_REPOSITORY SFML/SFML
    GIT_TAG 3.0.0
    VERSION 3.0.0
    OPTIONS 
        # Disable unused components to speed up build
        "SFML_BUILD_AUDIO OFF"      # Enable with ON + link SFML::Audio in CMakeLists.txt
        "SFML_BUILD_GRAPHICS ON"    # Enable with ON + link SFML::Graphics in CMakeLists.txt
        "SFML_BUILD_NETWORK OFF"    # Enable with ON + link SFML::Network in CMakeLists.txt
        "SFML_BUILD_WINDOW ON"      # ON by default; link via $<$<PLATFORM_ID:Windows>:SFML::Main> (Windows only)
        "SFML_BUILD_DOC OFF"
        "SFML_BUILD_EXAMPLES OFF"
)
