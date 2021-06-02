#pragma once

#include <functional>
#include <assert.h>
#include <vector>

#include "Pt.h"

typedef std::function<float(float, float)> Two_var_fn; // R^2 => R
typedef std::function<float(float)> One_var_fn; // R => R

struct Bound {
    Bound(float val) : val{val} {}
    Bound(One_var_fn fnc) : fnc{fnc} {}
    inline float value(float input) const { return (is_dependent() ? fnc(input) : val); }
    inline float value() const { assert(!is_dependent()); return val; }
    inline bool is_dependent() const { return (fnc != nullptr); }
private:
    float val;
    One_var_fn fnc;
};

class DoubleIntegral {
public:
    DoubleIntegral(Bound a, Bound b, Bound c, Bound d, float dx, float dy, Two_var_fn fnc) :
        a{a},
        b{b},
        c{c},
        d{d},
        dx{dx},
        dy{dy},
        fnc{fnc} 
    {
    }
    std::vector<Pt>* get_pts() { // just dydx for now
        std::vector<Pt>* pts = new std::vector<Pt>;
        for (float i=a.value()+dx; i<b.value()+0.001; i+=dx) {
            for (float j=c.value(i)+dy; j<d.value(i)+0.001; j+=dy) {
                pts->push_back(Pt(i-0.5*dx,j-0.5*dy));
            }
        }
        return pts;
    }
private:
    Bound a, b, c, d;
    float dx, dy;
    Two_var_fn fnc;
};
