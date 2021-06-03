#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "DoubleIntegral.h"
#include "Axis.h"

class IntegralDrawer {
public:
    enum class State { // what is integral drawer doing?    
        Drawing, Stopped, EraseAll
    };  
    IntegralDrawer(Bound a, Bound b, Bound c, Bound d, float dx, float dy, Two_var_fn fnc) :
        integral(a, b, c, d, dx, dy, fnc),
        dx{dx}, dy{dy},
        start_region {Pt(a.value()+0.5*dx, c.value(a.value())+0.5*dy)},
        curr_region {start_region},
        regions {0},
        total_value {0},
        value_label {"", Pt(0,0), "resource/mathfont.ttf"},
        next_square {Pt(200,70), Pt(gv::wid()+30,100), "Start", sf::Color(0,180,0)},
        del_square {Pt{200,70}, Pt(gv::wid()+30,190), "Pause", sf::Color::Red},
        restart_square {Pt(200,70), Pt(gv::wid()+30,280), "Restart", sf::Color(100,100,100)},
        state {State::Drawing},
        change_dx {int(0.2*gv::hei()), 3.0, 1.0, Pt(gv::wid()+0.1*gv::swid(), 0.75*gv::hei()), "DX", SlideBar::Orient::y},
        change_dy {int(0.2*gv::hei()), 3.0, 1.0, Pt(gv::wid()+0.6*gv::swid(), 0.75*gv::hei()), "DY", SlideBar::Orient::y},
        time_elapsed{0}
    {
        value_label.set_size(40);
    }
    void draw(sf::RenderWindow& win, Axis& a) {
        next_square.update();
        del_square.update();
        restart_square.update();

        change_dx.draw_shape(win);
        change_dy.draw_shape(win);
        dx = change_dx.getValue();
        dy = change_dy.getValue();
        integral.set_dxdy(dx, dy);
        
        if (next_square.is_clicked()) state = State::Drawing;
        if (del_square.is_clicked()) state = State::Stopped;
        if (restart_square.is_clicked()) state = State::EraseAll;

        if (state == State::Drawing) {
            time_elapsed += clock.getElapsedTime().asSeconds();
            clock.restart();
            const float add_delay = gv::timeToRender()/(integral.tot_regions());
            if (time_elapsed > add_delay) {
                int toAdd = int(time_elapsed/add_delay);
                time_elapsed -= add_delay*toAdd;
                while (toAdd-- && curr_region.x != 999) {
                    update_value_label(win, a, true);
                    a.add_shape(new 
                        AxisRectangleDynamic{Pt(dx,dy), gPt(curr_region.x, curr_region.y), sf::Color(255,0,0,100), 2});
                    curr_region = integral.next_pt(curr_region);
                    regions++;
                }
            }
        }
        if (state == State::Stopped) {
            time_elapsed = 0;
            clock.restart();
        }
        if (state == State::EraseAll) {
            time_elapsed = 0;
            clock.restart();
            for (; regions>0; regions--) {
                a.remove_latest_shape();
            }
            curr_region = start_region;
            total_value = 0;
        }
        next_square.draw_button(win);
        del_square.draw_button(win);
        restart_square.draw_button(win);
        update_value_label(win, a, false);
    }

    void update_value_label(sf::RenderWindow& win, Axis& a, bool from_dyn) {
        lb_fmt << std::fixed << std::setprecision(4);
        if (curr_region.x != 999) {
            if (from_dyn) total_value += dx * dy * integral.fnc_value(curr_region.x, curr_region.y);
            lb_fmt << "f(" << curr_region.x << ", " << curr_region.y << ")(" << dx*dy << ")";
            value_label.set_size(30);
            value_label.set_pos_str(lb_fmt.str(), Pt(gv::wid()-400,gv::hei()-150));
            value_label.draw_shape(win);
            lb_fmt.str("");
            if (regions > 0) {
                sf::Vertex line[2];
                line[0].position = sf::Vector2f(gv::wid()-400, gv::hei()-150);
                line[0].color = sf::Color::Black;
                line[1].position = a.get_exact_position();
                line[1].color = sf::Color::White;
                // std::cout << line[1].position.x << " ";
                win.draw(&line[0], 2, sf::Lines);
            }
        }
        lb_fmt << "Integral value: " << total_value;
        value_label.set_size(40);
        value_label.set_pos_str(lb_fmt.str(), Pt(gv::wid()-400,gv::hei()-90));
        value_label.draw_shape(win);
        lb_fmt.str("");
    }
private:
    DoubleIntegral integral;
    float dx, dy;
    Pt start_region;
    Pt curr_region;
    int regions;
    double total_value;
    Word value_label;
    std::stringstream lb_fmt;

    Button next_square;
    Button del_square;
    Button restart_square;
    State state;

    SlideBar change_dx;
    SlideBar change_dy;

    sf::Clock clock;
    double time_elapsed;
};