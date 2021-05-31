#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Pt.h"

class Word {
public:
    Word(const std::string& str, Pt pos) : pos{pos} {
        if (!font.loadFromFile("resource/acid.otf")) std::cout << "Font not loaded";
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(pos.x, pos.y);
    }
    void draw_shape(sf::RenderWindow& win) {
        text.setPosition(pos.x, pos.y);
        win.draw(text);
    }
    void draw_shape(const Pt& del, sf::RenderWindow& win) {
        text.setPosition(pos.x + del.x, pos.y + del.y);
        win.draw(text);
    }
    void set_pos_str(std::string str, const Pt& new_pos) {
        text.setString(str);
        pos = new_pos;
    }
    void set_str(std::string str) {
        text.setString(str);
    }
    void set_size(const int& sz) {
        text.setCharacterSize(sz);
    }
private:
    Pt pos;
    sf::Text text;
    sf::Font font;
};