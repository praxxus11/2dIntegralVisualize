namespace gv {


const int wid() { // the width of the entire window in pixels
    static const int wid = 900; return wid;
}
const int hei() { // the height of the entire window in pixels
    static const int hei = 900; return hei; 
}
const int swid() { // the width of the sidebar in pixels
    static const int swid = 300; return swid;
}
const int ggap() { // the gap between grid lines in pixels
    static const int ggap = 50; return ggap;
}
const float dynDelay() { // return the delay required for block to load in
    static const float delay = 0.0; return delay;
}
const float outlnDelay() { // return the delay required for the block's outlien to fade out
    static const float delay = 0.0; return delay;
}
const float addrectDelay() { // return the delay between each addition of a new dynamic rectangle
    static const float delay = 0.01; return delay;
}
const int outlnWid() {
    static const int wid = 2; return wid;
}

}
