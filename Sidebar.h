#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>

class SlideBar {
public:
    enum class Orient {
        x, y
    };
    SlideBar(int length, float max_value, float default_value, Pt pos, std::string str, Orient orient) : 
        pos{pos}, 
        max_value{max_value},
        default_value{default_value},
        length{length}, 
        label{str, Pt{pos.x+12,pos.y+12}},
        orient{orient},
        ratio_of_length{default_value/max_value}
    {
        slide_line.setPosition(pos.x, pos.y);
        if (orient == Orient::y) slide_line.setSize(sf::Vector2f(5, length));
        if (orient == Orient::x) slide_line.setSize(sf::Vector2f(length, 5));

        if (orient == Orient::y) slide_circle.setPosition(pos.x, pos.y + length*(default_value / max_value));   
        if (orient == Orient::x) slide_circle.setPosition(pos.x + length*(default_value / max_value), pos.y);

        slide_circle.setRadius(20);
        slide_circle.setOrigin(slide_circle.getRadius(), slide_circle.getRadius());

        label.set_size(40);
    }
    void draw_shape(sf::RenderWindow& win) {
        win.draw(slide_line);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (on_circle(win)) {
                mouse_on = true;
            }
        }
        else if (mouse_on) mouse_on = false; // mouse is not pressed anymore

        if (mouse_on) {
            if (orient == Orient::y) {
                int new_pos = gv::mouseY;
                if (new_pos < pos.y) new_pos = pos.y;
                if (new_pos > pos.y+length) new_pos = pos.y + length;
                slide_circle.setPosition(pos.x, new_pos);
                ratio_of_length = (new_pos-pos.y)/float(length);

                label.set_str((std::to_string(max_value*ratio_of_length).substr(0,4)));
            }
            if (orient == Orient::x) {
                int new_pos = gv::mouseX;
                if (new_pos < pos.x) new_pos = pos.x;
                if (new_pos > pos.x+length) new_pos = pos.x + length;
                slide_circle.setPosition(new_pos, pos.y);
                ratio_of_length = (new_pos-pos.x)/float(length);

                label.set_str((std::to_string(max_value*ratio_of_length).substr(0,4)));
            }
        }

        win.draw(slide_circle);
        label.draw_shape(win);
    }
    float getValue() const {
        return max_value*ratio_of_length;
    }

private:
    int length;
    float max_value;
    float default_value;
    Pt pos;
    Word label;
    Orient orient;

    sf::RectangleShape slide_line;
    sf::CircleShape slide_circle;
    
    bool mouse_on;
    float ratio_of_length;
    
    bool on_circle(sf::RenderWindow& win) const {
        sf::Vector2i curr_mouse = sf::Mouse::getPosition(win);
        const double dist = sqrt(
                                pow(curr_mouse.x - slide_circle.getPosition().x, 2) +
                                pow(curr_mouse.y - slide_circle.getPosition().y, 2)
                            );
        return (dist < slide_circle.getRadius());
    }
};
