namespace gv {

int mouseX = 0;
int mouseY = 0;
int lines_gap = 50;

const int wid() { // the width of the entire window in pixels
    static const int wid = 1200; return wid;
}
const int hei() { // the height of the entire window in pixels
    static const int hei = 900; return hei; 
}
const int swid() { // the width of the sidebar in pixels
    static const int swid = 300; return swid;
}
const int ggap() { // the gap between grid lines in pixels
    return lines_gap;
}
const float dynDelay() { // return the delay required for block to load in
    static const float delay = 0.005; return delay;
}
const float outlnDelay() { // return the delay required for the block's outlien to fade out
    static const float delay = 0.1; return delay;
}
const float timeToRender() { // return the delay between each addition of a new dynamic rectangle
    static const float render_time = 2; return render_time;
}
const int outlnWid() { // return the width of the outline in dyanmic squares in pixels
    static const int wid = 1; return wid;
}

}
