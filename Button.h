#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Pt.h"

class Button {
public:
    Button(Pt dim, Pt pos, std::string str, sf::Color col) :
        dim{dim},
        pos{pos},
        label{str, Pt{pos.x+20,pos.y+20}},
        color{col} 
    {
        rect.setSize(sf::Vector2f(dim.x, dim.y));
        rect.setPosition(sf::Vector2f(pos.x, pos.y));
        rect.setFillColor(color);

        reg_color = color;
        hover_color = color - sf::Color(30,30,30,0);
        press_color = color - sf::Color(80,80,80,0);

        label.set_size(60);

        clicked = false;
        sent_signal = false;
    }
    void update() {
        if (gv::mouseX > pos.x && gv::mouseX < pos.x+dim.x &&
            gv::mouseY > pos.y && gv::mouseY < pos.y+dim.y) {
            color = hover_color;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                color = press_color;
                if (!sent_signal) {
                    clicked = true;
                    sent_signal = true;
                }
                else { // signal is sent already
                    clicked = false;
                }
            }
            else { // signal is restarted IF ONLY let go of mouse
                clicked = false;
                sent_signal = false;
            }
        }
        else {
            color = reg_color;
            clicked = false;
        }

        rect.setFillColor(color);
    }

    void draw_button(sf::RenderWindow& win) {
        win.draw(rect);
        label.draw_shape(win);
    }

    bool is_clicked() const {
        return clicked;
    }

private:
    Pt dim;
    Pt pos;

    sf::Color color;
    sf::Color reg_color;
    sf::Color hover_color;
    sf::Color press_color;
    sf::RectangleShape rect;

    Word label;

    bool clicked;
    bool sent_signal;
};