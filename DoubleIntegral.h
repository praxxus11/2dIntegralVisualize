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
    Pt next_pt(Pt curr) {
        // these constants are to offset potential erros with bad precision
        if (curr.y + dy - 0.0000001 > d.value(curr.x)) {
            if (curr.x + dx - 0.0000001 > b.value()) {
                return Pt(999,999); // no more points left
            }
            return Pt(curr.x + dx, c.value(curr.x + dx) + 0.5*dy); 
            // no more points in inner integral
            // add term 0.5*dy to adjust for midpoint issues 
            // (since the pos of rectanlge represents midpoint)
        }
        return Pt(curr.x, curr.y + dy); // exist point to add
    }
    int tot_regions() { // returns total regions possible with current dx, dy configuration
        int ct = 0;
        for (float i=a.value()+dx; i<b.value()+0.001; i+=dx) {
            for (float j=c.value(i)+dy; j<d.value(i)+0.001; j+=dy) {
                ct++;
            }
        }
        return ct;
    }
    inline void set_dxdy(float DX, float DY) {
        dx = DX;
        dy = DY;
    }
    inline float fnc_value(float a, float b) {
        return fnc(a, b);
    }
    inline float get_a() const {
        return a.value();
    }
    inline float get_b() const {
        return b.value();
    }
    inline float get_c(float x) const {
        return c.value(x);
    }
    inline float get_d(float x) const {
        return d.value(x);
    }
private:
    Bound a, b, c, d;
    float dx, dy;
    Two_var_fn fnc;
};
