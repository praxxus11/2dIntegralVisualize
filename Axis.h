#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Pt.h"
#include "Words.h"
#include "Sidebar.h"
#include "Settings.h"
#pragma once

extern const int wid;
extern const int hei;

class AxisShape {
public:
    AxisShape(Pt pos, sf::Color col = sf::Color::White) : pos{pos}, color{col} {
    }
    virtual void draw_shape(const Pt& del, sf::RenderWindow& win) = 0;
protected:
    Pt pos;
    sf::Color color;
};

class AxisRectangle : public AxisShape {
public:
    AxisRectangle(Pt pos, 
    sf::RectangleShape rect, 
    sf::Color col = sf::Color::White) : 
    AxisShape{pos, col}, 
    sf_rect{rect} {
    }
    void draw_shape(const Pt& del, sf::RenderWindow& win) override {
        sf_rect.setPosition(pos.x + del.x, pos.y + del.y);
        sf_rect.setFillColor(AxisShape::color);
        win.draw(sf_rect);
    }
private:
    sf::RectangleShape sf_rect;
};

class AxisCircle : public AxisShape {
public:
    AxisCircle(Pt pos, 
    sf::CircleShape circ, 
    sf::Color col = sf::Color::White) : 
        AxisShape{pos, col}, 
        sf_circ{circ} {
    }
    void draw_shape(const Pt& del, sf::RenderWindow& win) override {
        sf_circ.setOrigin(sf_circ.getRadius(), sf_circ.getRadius());
        sf_circ.setPosition(pos.x + del.x, pos.y + del.y);
        sf_circ.setFillColor(AxisShape::color);
        win.draw(sf_circ);
    }
private:
    sf::CircleShape sf_circ;
};

class Axis {
public:
    Axis(Pt del) : del{del} {
    }
    ~Axis() {
        for (AxisShape* shp : axis_shapes) {
            delete shp;
        }
    }
    void add_shape(AxisShape* shp) {
        axis_shapes.push_back(shp);
    }

    void draw(sf::RenderWindow& win) {
        draw_axis(win);
        for (AxisShape* shp : axis_shapes) {
            shp->draw_shape(del, win);
        }
    }
    void set_del(const Pt& new_del) {
        del = new_del;
    }
    Pt get_del() const { return del; }
private:
    Pt del;
    std::vector<AxisShape*> axis_shapes;

    void draw_axis(sf::RenderWindow& win) {
        sf::RectangleShape ax {sf::Vector2f(wid, 2)}; // x axis
        ax.setFillColor(sf::Color::White);
        ax.setPosition(0, del.y);
        win.draw(ax);
        ax.setSize(sf::Vector2f(2, hei)); // y axis
        ax.setPosition(del.x, 0);
        win.draw(ax);

        const int thickness = 50;
        const int left = -del.x / thickness -1;
        const int right = (-del.x + wid) / thickness +1;
        const int top = -del.y / thickness -1;
        const int bot = (-del.y + hei) / thickness +1;

        Word numbering {"", Pt{0,0}};    
        for (int i=left; i<right; i++) {
            sf::RectangleShape ln {sf::Vector2f(1, hei)};
            ln.setFillColor(sf::Color(255,255,255,(i%5==0 ? 200 : 100)));
            ln.setPosition(i*thickness+del.x, 0);
            win.draw(ln);
            if (!(i%5)) {
                numbering.set_pos_str(std::to_string(i), Pt{i*thickness,0});
                numbering.draw_shape(del, win);
            }
        }
        
        for (int i=top; i<bot; i++) {
            sf::RectangleShape ln {sf::Vector2f(wid, 1)};
            ln.setFillColor(sf::Color(255,255,255,(i%5==0 ? 200 : 100)));
            ln.setPosition(0, i*thickness+del.y);
            win.draw(ln);
            if (!(i%5)) {
                numbering.set_pos_str(std::to_string(i), Pt{10,i*thickness-10});
                numbering.draw_shape(del, win);
            }
        }
    }
};