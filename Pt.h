#pragma once

struct Pt {
    int x, y;
    Pt(int x, int y) : x{x}, y{y} {}
    Pt() : x{0}, y{0} {}
};

struct gPt : public Pt {
    gPt(int x, int y) : Pt(x, -y) {}
};