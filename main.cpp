#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Axis.h"

int main() {
    Pt mouse_pos {-1, -1};
    Pt curr_del {gv::wid()/2, gv::hei()/2};

    sf::RenderWindow window(sf::VideoMode(gv::wid() + gv::swid(), gv::hei()), "SFML works!");
    Axis a {Pt{gv::wid()/2, gv::hei()/2}};


    const int xr = 10;
    const int yr = 10;
    const float dx = 5.0/xr;
    std::vector<AxisRectangleDynamic*> rects;
    for (float i=dx/2; i<xr*dx + dx/2; i += dx) {
        for (float j=dx/2; j<yr*dx + dx/2; j += dx) {
            AxisRectangleDynamic* dyn = new 
                AxisRectangleDynamic{gPt{i, j}, sf::RectangleShape{sf::Vector2f{dx, dx}}, sf::Color(255,255,255,100)};
            rects.push_back(dyn);
        }
    }
    a.add_shape(new AxisRectangle{gPt{-3, 2}, sf::RectangleShape{sf::Vector2f{5, 1}}, sf::Color::Green});


    Word www {"dx=dy=", Pt{gv::wid()+100, 330}};
    SlideBar bar {Pt{gv::wid()+100, 400}, 400, www};

    sf::Clock clock;
    float time_elapsed = 0;
    int rectNum = 0;
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
        time_elapsed += clock.getElapsedTime().asSeconds();
        clock.restart();
        if (time_elapsed > gv::addrectDelay() && rectNum < xr*yr) {
            int prevRect = rectNum;
            rectNum += int(time_elapsed / (gv::addrectDelay() + 0.0000001));
            time_elapsed = 0;
            for (int i=prevRect; i<rectNum && i<xr*yr; i++)
                a.add_shape(rects[i]);
        }
        window.clear();
        // bar.hh(window);
        a.draw(window);
        sidebar(window, bar);
        window.display();
    }
    return 0;
}