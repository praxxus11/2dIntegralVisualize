#pragma once

struct Pt {
    float x, y;
    Pt(float x, float y) : x{x}, y{y} {}
    Pt() : x{0}, y{0} {}
};

struct gPt : public Pt {
    gPt(float x, float y) : Pt(x, -y) {}
};