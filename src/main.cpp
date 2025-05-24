#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Ventana SFML");
    window.setFramerateLimit(60);

    sf::CircleShape circle(100.0f);
    sf::Vector2f origin(300.0f, 200.0f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(origin);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
