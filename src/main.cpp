#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Axis.h"
#include "IntegralDrawer.h"

int main() {
    Pt mouse_pos (-1, -1);
    Pt curr_del (gv::wid()/2, gv::hei()/2);

    sf::RenderWindow window(sf::VideoMode(gv::wid() + gv::swid(), gv::hei()), "");
    window.setFramerateLimit(60);

    Axis a {curr_del};

    SlideBar sizeBar {gv::swid()-50, 300, float(gv::ggap()), Pt(gv::wid()+25, 20), "Zoom", SlideBar::Orient::x};

    IntegralDrawer dr {
        Bound{-5}, 
        Bound{5}, 
        Bound{[](float x) { return -abs(sin(x)); }}, 
        Bound{[](float x) { return sqrt(81-x*x); }}, 
        0.5, 0.5, 
        [](float a, float b) { return a*a+b; }};

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
            if (event.type == sf::Event::GainedFocus) 
                gv::window_focused = 1;
            if (event.type == sf::Event::LostFocus) 
                gv::window_focused = 0;
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        gv::mouseX = mousePos.x;
        gv::mouseY = mousePos.y;

        if (gv::window_focused && gv::mouseX < gv::wid() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            a.set_del(Pt(curr_del.x+gv::mouseX-mouse_pos.x, curr_del.y+gv::mouseY-mouse_pos.y));
        }

        window.clear();
        a.draw(window);
        dr.draw(window, a);
        sizeBar.draw_shape(window);
        window.display();

        gv::lines_gap = sizeBar.getValue();
    }
    return 0;
}