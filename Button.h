#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Pt.h"

class Button {
public:
    Button(Pt dim, Pt corner, std::string str, sf::Color col) :
        dim{dim},
        fr_corner{corner},
        label{str, Pt{corner.x+20,corner.y+20}},
        color{col} {
        rect.setSize(sf::Vector2f(dim.x, dim.y));
        rect.setPosition(sf::Vector2f(fr_corner.x, fr_corner.y));
        rect.setFillColor(color);
        reg_color = color;
        hover_color = color - sf::Color(30,30,30,0);
        press_color = color - sf::Color(80,80,80,0);
        label.set_size(60);
        clicked = false;
    }
    void update(sf::RenderWindow& win) {
        if (gv::mouseX > fr_corner.x && gv::mouseX < fr_corner.x+dim.x &&
            gv::mouseY > fr_corner.y && gv::mouseY < fr_corner.y+dim.y) {
            color = hover_color;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                color = press_color;
                clicked = true;
            }
            else {
                clicked = false;
            }
        }
        else color = reg_color;
        rect.setFillColor(color);
        win.draw(rect);
        label.draw_shape(win);
    }
private:
    Pt dim;
    Pt fr_corner;
    sf::Color color;
    sf::Color reg_color;
    sf::Color hover_color;
    sf::Color press_color;
    sf::RectangleShape rect;
    Word label;
    bool clicked;
};