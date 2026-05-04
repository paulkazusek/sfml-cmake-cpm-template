# SFML Template with CMake & CPM

A minimal starter project for SFML 3.0 using CMake and CPM (CMake Package Manager) for zero-hassle dependency management.

## Features

- Uses **SFML 3.0** via CPM for easy dependency management
- Minimal setup with `sf::Window` and direct OpenGL rendering
- C++20 standard compliance
- Automatic versioning via generated `version.h`
- MSVC support with `/MP` multicore compilation
- CMake Presets (Version 3) for streamlined configuration
- Windows Console Visibility toggle (hidden by default, debug-console preset for output)

## Prerequisites

- CMake 3.22 or higher (required for CMake Presets support)
- A C++20 compatible compiler (MSVC, GCC, Clang)
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

Modify `src/main.cpp` to add your own logic. The default example creates a window with a color-changing background using direct OpenGL.

### Configure SFML Components (Optional)

This template uses `sf::Window` with direct OpenGL by default.
If you want to use the SFML 2D graphics API (`sf::RenderWindow`, `sf::Sprite`, `sf::Text`, etc.), follow these steps:

**Adjust `dependencies.cmake`** – enable only needed modules:

*Enable only the modules you need (e.g., set `SFML_BUILD_GRAPHICS ON` if you only want 2D rendering)*

```cmake
CPMAddPackage(
    NAME SFML
    GITHUB_REPOSITORY SFML/SFML
    GIT_TAG 3.0.0
    VERSION 3.0.0
    OPTIONS
        "SFML_BUILD_AUDIO OFF"      # Enable with ON + link SFML::Audio in CMakeLists.txt
        "SFML_BUILD_GRAPHICS OFF"   # Enable with ON + link SFML::Graphics in CMakeLists.txt
        "SFML_BUILD_NETWORK OFF"    # Enable with ON + link SFML::Network in CMakeLists.txt
        "SFML_BUILD_WINDOW ON"      # Required for current minimal window setup
        "SFML_BUILD_DOC OFF"
        "SFML_BUILD_EXAMPLES OFF"
)
```

**Adjust `CMakeLists.txt`** – link matching modules:

Link the required SFML modules (must match the enabled modules in `dependencies.cmake`):
```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Window SFML::Main)
```

Delete the `build` folder and reconfigure CMake to apply changes.

**Common Examples:**

- **Switch to SFML 2D Graphics**: Enable `SFML_BUILD_GRAPHICS ON` in `dependencies.cmake`, link `SFML::Graphics` and replace `sf::Window` with `sf::RenderWindow` in `src/main.cpp`:

```cpp
#include <SFML/Graphics.hpp>  // instead of <SFML/Window.hpp> and <SFML/OpenGL.hpp>

int main()
{
    const sf::String title = "sfml-template version: " APP_VERSION;
    sf::RenderWindow window(sf::VideoMode({800, 600}), title);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
        }

        window.clear(sf::Color::Black);
        // window.draw(...);  // Draw 2D objects here
        window.display();
    }
}
```

- **Enable Audio/Network**: Enable the respective modules in `dependencies.cmake` and link `SFML::Audio`/`SFML::Network` in `CMakeLists.txt`. Refer to the [SFML docs](https://www.sfml-dev.org/documentation/3.0.0/) for usage examples.

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

## Project Structure

```
sfml-template/
├── src/
│   ├── main.cpp
│   └── version.h.in
├── .clang-format
├── .gitignore
├── CMakeLists.txt
├── CMakePresets.json
├── dependencies.cmake
├── LICENSE
└── README.md
```

## License

