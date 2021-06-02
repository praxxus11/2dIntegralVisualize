#include <SFML/Graphics.hpp>
#include <vector>

#include "DoubleIntegral.h"
#include "Axis.h"

class IntegralDrawer {
public:
    enum class State { // what is integral drawer doing?    
        Drawing, Stopped, Erasing, EraseAll
    };  
    IntegralDrawer(Bound a, Bound b, Bound c, Bound d, float dx, float dy, Two_var_fn fnc) :
        integral(a, b, c, d, dx, dy, fnc),
        dx{dx}, dy{dy},
        next_square {Pt(200,70), Pt(gv::wid()+30,100), "Start", sf::Color(0,180,0)},
        del_square {Pt{200,70}, Pt(gv::wid()+30,190), "Pause", sf::Color::Red},
        restart_square {Pt(200,70), Pt(gv::wid()+30,280), "Restart", sf::Color(100,100,100)},
        back_square {Pt(200,70), Pt(gv::wid()+30,370), "Back", sf::Color(100,100,100)},
        state {State::Drawing},
        pts{integral.get_pts()},
        pts_ind{0},
        time_elapsed{0}
    {
        std::cout << pts->size();
    }
    ~IntegralDrawer() 
    {
        delete pts;
    }

    void draw(sf::RenderWindow& win, Axis& a) {
        next_square.update();
        del_square.update();
        restart_square.update();
        back_square.update();
        
        if (next_square.is_clicked()) state = State::Drawing;
        if (del_square.is_clicked()) state = State::Stopped;
        if (back_square.is_clicked()) state = State::Erasing;
        if (restart_square.is_clicked()) state = State::EraseAll;

        if (state == State::Drawing) {
            time_elapsed += clock.getElapsedTime().asSeconds();
            clock.restart();
            const float add_delay = gv::timeToRender()/(pts->size());
            if (time_elapsed > add_delay) {
                const int toAdd = int(time_elapsed/add_delay);
                for (int i=0; i<toAdd && pts_ind<pts->size(); i++, pts_ind++) {
                    a.add_shape(new 
                        AxisRectangleDynamic{Pt(dx,dy), 
                                            gPt((*pts)[pts_ind].x, (*pts)[pts_ind].y), 
                                            sf::Color(255,0,0,100), 
                                            2});
                }
                time_elapsed -= add_delay*toAdd;
            }
        }
        if (state == State::Stopped) {
            time_elapsed = 0;
            clock.restart();
        }
        if (state == State::Erasing) {
            time_elapsed += clock.getElapsedTime().asSeconds();
            clock.restart();
            const float add_delay = gv::timeToRender()/(pts->size());
            if (time_elapsed > add_delay) {
                const int toRemove = int(time_elapsed/add_delay);
                for (int i=0; i<toRemove && pts_ind>0; i++, pts_ind--) {
                    a.remove_latest_shape();
                }
                time_elapsed -= add_delay*toRemove;
            }
        }
        if (state == State::EraseAll) {
            time_elapsed = 0;
            clock.restart();
            for (; pts_ind>0; pts_ind--) {
                a.remove_latest_shape();
            }
        }

        next_square.draw_button(win);
        del_square.draw_button(win);
        restart_square.draw_button(win);
        back_square.draw_button(win);
    }
private:
    DoubleIntegral integral;
    float dx, dy;

    Button next_square;
    Button del_square;
    Button restart_square;
    Button back_square;
    State state;

    std::vector<Pt>* pts;
    int pts_ind;

    sf::Clock clock;
    double time_elapsed;
};