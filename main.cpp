#include <SFML/Graphics.hpp>
#include <iostream>
#include "Axis.h"

extern const int wid;
extern const int hei;
extern const int sidebar_wid;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Pt mouse_pos {-1,-1};
    Pt curr_del {wid/2,hei/2};

    sf::RenderWindow window(sf::VideoMode(wid+sidebar_wid, hei), "SFML works!");
    Axis a {Pt{wid/2, hei/2}};
    AxisShape* hi = new AxisRectangle{Pt{100,100}, sf::RectangleShape{sf::Vector2f{100,30}}, sf::Color::Cyan};
    AxisShape* bye = new AxisCircle({Pt{0,0}, sf::CircleShape{100,100}, sf::Color(255,255,255,50)});
    a.add_shape(hi);
    a.add_shape(bye);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                curr_del = a.get_del();
                mouse_pos.x = event.mouseButton.x;
                mouse_pos.y = event.mouseButton.y;                
            }
        }
        window.clear();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i curr_mouse = sf::Mouse::getPosition(window);
            if (curr_mouse.x < wid) 
                a.set_del(Pt{curr_del.x+curr_mouse.x-mouse_pos.x, curr_del.y+curr_mouse.y-mouse_pos.y});
        }
        a.draw(window);
        sidebar(window);
        window.display();
    }
    return 0;
}