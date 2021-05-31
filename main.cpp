#include <SFML/Graphics.hpp>
#include <iostream>
#include "Axis.h"


int main() {
    Pt mouse_pos {-1, -1};
    Pt curr_del {gv::wid()/2, gv::hei()/2};

    sf::RenderWindow window(sf::VideoMode(gv::wid() + gv::swid(), gv::hei()), "SFML works!");
    Axis a {Pt{gv::wid()/2, gv::hei()/2}};
    a.add_shape(new AxisRectangle{Pt{100, 100}, sf::RectangleShape{sf::Vector2f{100, 30}}, sf::Color::Cyan});
    a.add_shape(new AxisCircle({Pt{0, 0}, sf::CircleShape{100, 100}, sf::Color(255, 255, 255, 50)}));
    a.add_shape(new AxisRectangle{Pt{600, 100}, sf::RectangleShape{sf::Vector2f{100, 30}}, sf::Color::Green});
    Word www {"dx=dy=", Pt{gv::wid()+100, 330}};
    SlideBar bar {Pt{gv::wid()+100, 400}, 400, www};
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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i curr_mouse = sf::Mouse::getPosition(window);
            if (curr_mouse.x < gv::wid()) 
                a.set_del(Pt{curr_del.x+curr_mouse.x-mouse_pos.x, curr_del.y+curr_mouse.y-mouse_pos.y});
        }
        window.clear();
        // bar.hh(window);
        a.draw(window);
        sidebar(window, bar);
        window.display();
    }
    return 0;
}