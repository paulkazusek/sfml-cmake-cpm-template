# SFML Template with CMake & CPM

A minimal starter project for SFML 3.0 using CMake and CPM (CMake Package Manager) for zero-hassle dependency management.

## Features

- Uses **SFML 3.0** via CPM for easy dependency management
- Minimal setup with `sf::RenderWindow` and SFML Graphics API
- C++20 standard compliance
- Automatic versioning via generated `version.hpp`
- MSVC support with `/MP` multicore compilation
- CMake Presets (Version 3) for streamlined configuration
- Asset management — \assets/` directory automatically copied to builds and releases`
- Windows Console Visibility toggle (hidden by default, debug-console preset for output)

## Prerequisites

- CMake 3.22 or higher (required for CMake Presets support)
- A C++20 compatible compiler (MSVC, GCC or Clang)
- Git

## Getting Started

Follow this workflow to set up, customize, build, and run your project:

### Load the Template

Choose one of two methods to get the project files:

- Clone this repository:

    ```bash
    git clone https://github.com/paulkazusek/sfml-cmake-cpm-template.git my-sfml-project
    cd my-sfml-project
    ```
- Or use it as a GitHub template by clicking "Use this template" on the repository page.

### Customize Project Metadata

Open `CMakeLists.txt` and update the `project()` command with your project name and initial version:

```cmake
project(
    my-sfml-project  # Change to your project name
    VERSION 0.1.0    # Set your initial version
    LANGUAGES CXX
)
```

If you need to see debug output (e.g., std::cout) on Windows, you can either:

- Use the debug-console CMake preset (see Build section below) 
- Manually set the `SHOW_CONSOLE` option in `CMakeLists.txt` (default is `OFF`)

```cmake
option(SHOW_CONSOLE "Show console window (useful for debugging)" ON)
```

### Implement Your Application

Modify `src/main.cpp` to add your own logic.

### Add Assets

Place assets such as icons, textures, or fonts in the `assets/` directory.
They are automatically copied next to the executable at build time and
included in release packages.

```cpp
sf::Image icon;
if (icon.loadFromFile("assets/icon.png")) {
    window.setIcon(icon);
}
```

### Configure Additional SFML Components (Optional)

The template enables only the modules you need. By default, `SFML_BUILD_GRAPHICS`
and `SFML_BUILD_WINDOW` are ON, with `SFML::Graphics` linked.

To add **Audio** or **Network**, enable them in `dependencies.cmake`:

```cmake
"SFML_BUILD_AUDIO ON"
"SFML_BUILD_NETWORK ON"
```

and link the corresponding target in `CMakeLists.txt`:

Link the required SFML modules (must match the enabled modules in `dependencies.cmake`):
```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics
    SFML::Audio       # add if needed
    SFML::Network     # add if needed
    $<$<PLATFORM_ID:Windows>:SFML::Main>
)
```

Delete the `build` folder and reconfigure CMake to apply changes.

## Build the Project

We recommend using CMake Presets for streamlined configuration, but a classic manual method is also available.

### Using CMake Presets (Recommended)

Presets auto-detect your system's default generator (e.g., Visual Studio on Windows, Unix Makefiles/Ninja on Linux/macOS):

```bash
# Debug build (hidden console, default)
cmake --preset debug
cmake --build --preset debug

# Release build (optimized, hidden console)
cmake --preset release
cmake --build --preset release

# Debug build with visible console (Windows only)
cmake --preset debug-console
cmake --build --preset debug-console
```

### Classic Method (Optional)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Run the Application

After building, run the executable from the build directory:

- **Debug builds**: `./build/Debug/my-sfml-project.exe` (Windows) or `./build/Debug/my-sfml-project` (Linux/macOS)
- **Release builds**: `./build/Release/my-sfml-project.exe` (Windows) or `./build/Release/my-sfml-project` (Linux/macOS)

## CI/CD & Releases

This project uses GitHub Actions for continuous integration.
When a tag matching `v*` is pushed (e.g. `v0.3.0`), the CI pipeline
automatically builds the project on Linux, Windows, and macOS,
and uploads the platform-specific binaries as assets to the
corresponding GitHub Release.

## Project Structure

```
sfml-template/
├── assets/
│   └── icon.png
├── src/
│   ├── main.cpp
│   └── version.hpp.in
├── .clang-format
├── .gitignore
├── CMakeLists.txt
├── CMakePresets.json
├── dependencies.cmake
├── LICENSE
└── README.md
```

## License

This Template is licensed under the terms of the [MIT License](LICENSE).