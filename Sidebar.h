#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>

class SlideBar {
public:
    SlideBar(const Pt& p, int height, const Word& lab) : 
        pos{p}, 
        height{height}, 
        label{lab},
        bs{sf::Vector2f(5, height)},
        but{20.f} 
    {
        bs.setPosition(pos.x, pos.y);
        but.setOrigin(but.getRadius(), but.getRadius());
        but.setPosition(pos.x, pos.y);   

        clr_shp.setPosition(gv::wid(), 0);
        clr_shp.setFillColor(sf::Color::Black);

        label.set_size(40);
    }
    void update(sf::RenderWindow& win) {
        win.draw(clr_shp);
        win.draw(bs);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (on_circle(win)) {
                mouse_on = true;
            }
        }
        else if (mouse_on) mouse_on = false; // mouse is not pressed anymore

        if (mouse_on) {
            int new_pos = sf::Mouse::getPosition(win).y;
            if (new_pos < pos.y) new_pos = pos.y;
            if (new_pos > pos.y+height) new_pos = pos.y+height;
            but.setPosition(pos.x, new_pos);

            label.set_str("dx=dy=" + 
                (std::to_string(2*
                ((new_pos-pos.y)/float(height))
            ).substr(0,4)));
        }
        win.draw(but);
        label.draw_shape(win);
    }

    //DELETE FOR LATER
    void hh(sf::RenderWindow& win) {
        label.test(win);
    }
private:
    int height;
    Pt pos;
    Word label;
    bool mouse_on;
    sf::RectangleShape bs;
    sf::CircleShape but;
    sf::RectangleShape clr_shp {sf::Vector2f(gv::swid(), gv::hei())};
    
    bool on_circle(sf::RenderWindow& win) const {
        sf::Vector2i curr_mouse = sf::Mouse::getPosition(win);
        const double dist = sqrt(
                                pow(curr_mouse.x - but.getPosition().x, 2) +
                                pow(curr_mouse.y - but.getPosition().y, 2)
                            );
        return (dist-20 < but.getRadius());
    }
};

void sidebar(sf::RenderWindow& win, SlideBar& bar) {
    bar.update(win);
}