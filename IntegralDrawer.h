#include <SFML/Graphics.hpp>
#include <vector>

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
        start_region {Pt(a.value()+0.5*dx, c.value(a.value()))},
        curr_region {start_region},
        regions {0},
        next_square {Pt(200,70), Pt(gv::wid()+30,100), "Start", sf::Color(0,180,0)},
        del_square {Pt{200,70}, Pt(gv::wid()+30,190), "Pause", sf::Color::Red},
        restart_square {Pt(200,70), Pt(gv::wid()+30,280), "Restart", sf::Color(100,100,100)},
        state {State::Drawing},
        change_dx {int(0.2*gv::hei()), 3.0, 1.0, Pt(gv::wid()+0.1*gv::swid(), 0.75*gv::hei()), "DX", SlideBar::Orient::y},
        change_dy {int(0.2*gv::hei()), 3.0, 1.0, Pt(gv::wid()+0.6*gv::swid(), 0.75*gv::hei()), "DY", SlideBar::Orient::y},
        time_elapsed{0}
    {
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
        }

        next_square.draw_button(win);
        del_square.draw_button(win);
        restart_square.draw_button(win);
    }
private:
    DoubleIntegral integral;
    float dx, dy;
    Pt start_region;
    Pt curr_region;
    int regions;

    Button next_square;
    Button del_square;
    Button restart_square;
    State state;

    SlideBar change_dx;
    SlideBar change_dy;

    sf::Clock clock;
    double time_elapsed;
};