#include <iostream>

#include <SFML/Graphics.hpp>

#include "version.hpp"

int main() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "SFML Template v" << APP_VERSION << " started." << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // create the window and set up
    const sf::String title = "sfml-template version: " APP_VERSION;
    sf::RenderWindow window(sf::VideoMode({800, 600}), title);
    window.setFramerateLimit(60);

    sf::Image icon;
    if (icon.loadFromFile("assets/icon.png")) {
        window.setIcon(icon);
    }

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Black);

        // end the current frame
        window.display();
    }

    return 0;
}
