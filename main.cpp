#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Axis.h"
#include "IntegralDrawer.h"

int main() {
    Pt mouse_pos (-1, -1);
    Pt curr_del (gv::wid()/2, gv::hei()/2);

    sf::RenderWindow window(sf::VideoMode(gv::wid() + gv::swid(), gv::hei()), "SFML works!");
    Axis a {Pt(gv::wid()/2, gv::hei()/2)};

    SlideBar sizeBar {gv::swid()-50, 100, 50, Pt(gv::wid()+25, 20), "Size", SlideBar::Orient::x};
    SlideBar bar {300, 10, 1, Pt(gv::wid()+100, 450), "Hello", SlideBar::Orient::y};

    IntegralDrawer dr {
        Bound{0}, 
        Bound{5}, 
        Bound{0}, 
        Bound{5}, 
        1, 0.5, nullptr};
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
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        gv::mouseX = mousePos.x;
        gv::mouseY = mousePos.y;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i curr_mouse = sf::Mouse::getPosition(window);
            if (curr_mouse.x < gv::wid()) 
                a.set_del(Pt(curr_del.x+curr_mouse.x-mouse_pos.x, curr_del.y+curr_mouse.y-mouse_pos.y));
        }

    

        window.clear();
        a.draw(window);;
        bar.draw_shape(window);
        sizeBar.draw_shape(window);
        dr.draw(window, a);
        window.display();

        gv::lines_gap = sizeBar.getValue();
    }
    return 0;
}