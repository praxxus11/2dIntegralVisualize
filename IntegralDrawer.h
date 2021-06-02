#include <SFML/Graphics.hpp>
#include <vector>

#include "DoubleIntegral.h"
#include "Axis.h"

class IntegralDrawer {
public:
    IntegralDrawer(Bound a, Bound b, Bound c, Bound d, float dx, float dy, Two_var_fn fnc) :
        integral(a, b, c, d, dx, dy, fnc),
        dx{dx}, dy{dy},
        next_square {Pt(200,150), Pt(gv::wid()+30,100), "Make shape", sf::Color::Green},
        del_square {Pt{200,150}, Pt(gv::wid()+30,250), "Delete!", sf::Color::Red},
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
    // void draw(sf::RenderWindow& win, Axis& a) {
    //     next_square.update();
    //     del_square.update();
    //     if (pts_ind < pts->size() && next_square.is_clicked()) {
    //         a.add_shape(new 
    //             AxisRectangleDynamic{Pt(dx,dy), gPt((*pts)[pts_ind].x, (*pts)[pts_ind].y), sf::Color(255,0,0,150), 3});
    //         pts_ind++;
    //     }
    //     if (pts_ind > 0 && del_square.is_clicked()) {
    //         a.remove_latest_shape();
    //         pts_ind--;
    //     }

    //     next_square.draw_button(win);
    //     del_square.draw_button(win);
    // }
    void draw(sf::RenderWindow& win, Axis& a) {
        time_elapsed += clock.getElapsedTime().asSeconds();
        clock.restart();
        const float add_delay = gv::timeToRender()/(pts->size());
        if (time_elapsed > add_delay) {
            const int toAdd = int(time_elapsed/add_delay);
            for (int i=0; i<toAdd && pts_ind<pts->size(); i++, pts_ind++) {
                a.add_shape(new 
                    AxisRectangleDynamic{Pt(dx,dy), gPt((*pts)[pts_ind].x, (*pts)[pts_ind].y), sf::Color(255,0,0,100), 3});
                    // AxisRectangle{Pt(dx,dy), gPt((*pts)[pts_ind].x, (*pts)[pts_ind].y), sf::Color(255,0,0,100)});
            }
            time_elapsed -= add_delay*toAdd;
        }
    }
private:
    DoubleIntegral integral;
    float dx, dy;
    Button next_square;
    Button del_square;
    std::vector<Pt>* pts;
    int pts_ind;

    sf::Clock clock;
    double time_elapsed;
};