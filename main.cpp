#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Axis.h"

int main() {
    Pt mouse_pos (-1, -1);
    Pt curr_del (gv::wid()/2, gv::hei()/2);

    sf::RenderWindow window(sf::VideoMode(gv::wid() + gv::swid(), gv::hei()), "SFML works!");
    Axis a {Pt(gv::wid()/2, gv::hei()/2)};

    a.add_shape(new AxisRectangle{Pt(2,2), gPt(-3,-3), sf::Color::Green});

    std::vector<AxisRectangleDynamic*> rects;
    for (float i=.5; i<5.5; i++) {
        for (float j=.5; j<5.5; j++) {
            AxisRectangleDynamic* dyn = 
                new AxisRectangleDynamic(Pt(1,1), gPt(i,j), sf::Color(255,255,255,100), 3);
            rects.push_back(dyn);
        }
    }
    int rectInd = 0;

    SlideBar sizeBar {gv::swid()-50, 100, 50, Pt{gv::wid()+25, 20}, "Size", SlideBar::Orient::x};
    SlideBar bar {300, 10, 1, Pt(gv::wid()+100, 450), "Hello", SlideBar::Orient::y};

    Button but_make {Pt(200,150), Pt(gv::wid()+30,100), "Make shape", sf::Color::Green};
    Button but_del {Pt{200,150}, Pt(gv::wid()+30,250), "Delete!", sf::Color::Red};
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
        but_make.update();
        but_del.update();
        if (rectInd < 25 && but_make.is_clicked()) {
            a.add_shape(rects[rectInd]);
            rectInd++;
        }
        if (rectInd <= 25 && but_del.is_clicked()) {
            a.remove_latest_shape();
            rectInd--;
        }
    

        window.clear();
        a.draw(window);
        but_make.draw_button(window);
        but_del.draw_button(window);
        bar.draw_shape(window);
        sizeBar.draw_shape(window);
        window.display();

        gv::lines_gap = sizeBar.getValue();
    }
    return 0;
}