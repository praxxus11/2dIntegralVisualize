#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <math.h>
#include <assert.h>


#include "Settings.h"
#include "Pt.h"
#include "Words.h"
#include "Sidebar.h"
#include "Button.h"

class AxisShape {
public:
    AxisShape(gPt pos, sf::Color col) : pos{pos}, color{col} 
    {
    }
    virtual void draw_shape(const Pt& del, sf::RenderWindow& win) = 0;
    virtual sf::Vector2f get_position() const = 0;
protected:
    gPt pos;
    sf::Color color;
};

class AxisRectangle : public AxisShape {
public:
    AxisRectangle(Pt dim, gPt pos, sf::Color col) : 
        AxisShape{pos, col},
        dim{dim}
    {
        sf_rect.setOrigin(sf::Vector2f(
            0.5 * dim.x * gv::ggap(), 
            0.5 * dim.y * gv::ggap()));
        sf_rect.setSize(sf::Vector2f(
            dim.x * gv::ggap(), 
            dim.y * gv::ggap()));
        sf_rect.setFillColor(col);
    }
    void draw_shape(const Pt& del, sf::RenderWindow& win) override {
        sf_rect.setOrigin(sf::Vector2f(
            0.5 * dim.x * gv::ggap(), 
            0.5 * dim.y * gv::ggap()));
        sf_rect.setSize(sf::Vector2f(
            dim.x * gv::ggap(), 
            dim.y * gv::ggap()));
        sf_rect.setPosition(
            pos.x * gv::ggap() + del.x, 
            pos.y * gv::ggap() + del.y);
        win.draw(sf_rect);
    }
    sf::Vector2f get_position() const override {
        return sf_rect.getPosition();
    }
protected:
    Pt dim;
    sf::RectangleShape sf_rect;
};


class AxisRectangleDynamic : public AxisRectangle {
public:
    AxisRectangleDynamic(Pt dim, gPt pos, sf::Color col, int border_thickness) : 
        AxisRectangle{dim, pos, col},
        border_thickness{border_thickness},
        time_elapsed{0},
        ratio_of_size{0}
        {
            sf_rect.setSize(sf::Vector2f(dim.x * gv::ggap(), dim.y * gv::ggap()));
            sf_rect.setOutlineColor(sf::Color(255,255,255,200));
            sf_rect.setFillColor(AxisShape::color);
        }
    void draw_shape(const Pt& del, sf::RenderWindow& win) override {
        if (ratio_of_size < 1) { 
        // the rectangle is not at full size and is "loading"
            time_elapsed += clock.getElapsedTime().asSeconds();
            clock.restart();
            if (time_elapsed > gv::dynDelay()) {
                const int incrmt_steps = int(time_elapsed / gv::dynDelay());
                ratio_of_size = std::min(ratio_of_size + 0.01*incrmt_steps, 1.0);
                time_elapsed -= gv::dynDelay()*incrmt_steps;
            }
        }
        else if (border_thickness > 1) { 
        // the rectangle is at full size and the border is still present
            time_elapsed += clock.getElapsedTime().asSeconds();
            clock.restart();
            if (time_elapsed > gv::outlnDelay()) {
                time_elapsed = 0;
                border_thickness--;
            }
        }
        const float new_dim_x = ratio_of_size * (dim.x * gv::ggap());
        const float new_dim_y =  ratio_of_size * (dim.y * gv::ggap());  
        sf_rect.setOrigin(sf::Vector2f(
            ratio_of_size * 0.5 * dim.x * gv::ggap(), 
            ratio_of_size * 0.5 * dim.y * gv::ggap()));
        sf_rect.setSize(sf::Vector2f(
            new_dim_x, 
            new_dim_y));
        sf_rect.setPosition(
            pos.x * gv::ggap() + del.x, 
            pos.y * gv::ggap() + del.y);
        sf_rect.setOutlineThickness((std::min(new_dim_x, new_dim_y) <= 6) ? 0 : -border_thickness);

        win.draw(sf_rect);
    }
private:
    int border_thickness;
    float ratio_of_size;
    float time_elapsed;
    sf::Clock clock;
};

class Axis {
public:
    Axis(Pt del) : del{del} 
    {
    }
    ~Axis() 
    {
        for (AxisShape* shp : axis_shapes) {
            delete shp;
        }
    }
    void add_shape(AxisShape* shp) {
        axis_shapes.push_back(shp);
    }
    void remove_latest_shape() {
        if (axis_shapes.size()) {
            delete axis_shapes.back();
            axis_shapes.pop_back();
        }
    } 
    sf::Vector2f get_exact_position() const {
        assert(axis_shapes.size()>=1);
        return axis_shapes.back()->get_position();
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
        sf::RectangleShape ax {sf::Vector2f(gv::wid(), 2)}; // x axis
        ax.setFillColor(sf::Color::White);
        ax.setPosition(0, del.y);
        win.draw(ax);
        ax.setSize(sf::Vector2f(2, gv::hei())); // y axis
        ax.setPosition(del.x, 0);
        win.draw(ax);

        const int left = -del.x / gv::ggap() -1;
        const int right = (-del.x + gv::wid()) / gv::ggap() +1;
        const int top = -del.y / gv::ggap() -1;
        const int bot = (-del.y + gv::hei()) / gv::ggap() +1;

        static Word numbering {"", Pt{0,0}, "resource/mathfont.ttf"};    
        numbering.set_size(20);
        for (int i=left; i<right; i++) {
            sf::RectangleShape ln {sf::Vector2f(1, gv::hei())};
            ln.setFillColor(sf::Color(255, 255, 255,(i%4==0 ? 150 : 70)));
            ln.setPosition(i*gv::ggap()+del.x, 0);
            win.draw(ln);
            if (!(i%2)) {
                numbering.set_pos_str(std::to_string(i), Pt(i*gv::ggap(),0));
                numbering.draw_shape(del, win);
            }
        }
        
        for (int i=top; i<bot; i++) {
            sf::RectangleShape ln {sf::Vector2f(gv::wid(), 1)};
            ln.setFillColor(sf::Color(255, 255, 255,(i%4==0 ? 150 : 70)));
            ln.setPosition(0, i*gv::ggap()+del.y);
            win.draw(ln);
            if (!(i%2)) {
                numbering.set_pos_str(std::to_string(-i), Pt(10, i*gv::ggap()-10));
                numbering.draw_shape(del, win);
            }
        }
    }
};