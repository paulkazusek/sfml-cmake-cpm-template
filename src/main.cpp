#include <iostream>

#include <SFML/OpenGL.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include "version.h"

int main() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "SFML Template v" << APP_VERSION << " started." << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // create the window and set up
    const sf::String title = "sfml-template version: " APP_VERSION;
    sf::Window window(sf::VideoMode({800, 600}), title);
    window.setFramerateLimit(60);

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
        }

        // OpenGL:
        const auto time = clock.getElapsedTime().asSeconds();
        glClearColor(0.5f + 0.5f * sin(time), 0.3f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // end the current frame
        window.display();
    }

    return 0;
}
