#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "interface/textArea/textArea.h"
#include "geometry/superEllipse/superEllipse.h"
#include "interface/figure/figure.h"
#include <map>
#include <string>

const int WIDTH = 800;
const int HEIGHT = 800;

int main()
{
    int i = 0;
    sf::Color color[2] = {sf::Color::Red, sf::Color::Blue};
    sf::Clock clock;
    float time = clock.getElapsedTime().asSeconds();

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "GUI");
    Figure figure;
    figure.setFillColor(sf::Color::Red);
    figure.setOutlineColor(sf::Color::Black);
    figure.setOutlineWidth(2);
    figure.setWidth(400);
    figure.setHeight(200);
    figure.setCoords(WIDTH / 2, HEIGHT / 2);
    
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


        }

        if (clock.getElapsedTime().asSeconds() - time >= 0.5)
        {
            figure.setFillColor(color[i % 2]);
            ++i;
            clock.restart();
        }

        window.clear(sf::Color(200, 200, 200));
        figure.draw(window);
        window.display();
    }

    return 0;
}