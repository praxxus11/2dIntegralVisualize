#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>

extern const int wid;
extern const int hei;
extern const int sidebar_wid;

class SlideBar {
public:
    SlideBar(Pt p, int height, Word lab) : pos{p}, 
        height{height}, 
        label{lab},
        bs{sf::Vector2f(5, height)},
        but{40.f} 
    {
        bs.setPosition(pos.x, pos.y);
        but.setOrigin(but.getRadius(), but.getRadius());
        but.setPosition(pos.x, pos.y);   
    }
    void update(sf::RenderWindow& win) {
        win.draw(bs);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (on_circle(win)) {
                int new_pos = sf::Mouse::getPosition(win).y;
                if (new_pos < pos.y) new_pos = pos.y;
                if (new_pos > pos.y+height) new_pos = pos.y+height;
                but.setPosition(pos.x, new_pos);

                label.set_str("dx=" + 
                    (std::to_string(2*
                    ((new_pos-pos.y)/float(height))
                ).substr(0,4)));
            }
        }
        win.draw(but);
        label.draw_shape(win);
    }
private:
    int height;
    Pt pos;
    sf::RectangleShape bs;
    sf::CircleShape but;
    Word label;

    bool on_circle(sf::RenderWindow& win) const {
        sf::Vector2i curr_mouse = sf::Mouse::getPosition(win);
        const double dist = sqrt(
                                pow(curr_mouse.x - but.getPosition().x, 2) +
                                pow(curr_mouse.y - but.getPosition().y, 2)
                            );
        return (dist-20 < but.getRadius());
    }
};

Word w {"dx", Pt{100,100}};
SlideBar bar {Pt{wid+100, 400}, 400, w};
void sidebar(sf::RenderWindow& win) {
    bar.update(win);
}