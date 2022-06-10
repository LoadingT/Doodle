#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class TextField {
public:
    TextField();
    void handleInput(sf::Event e);
    void Draw(sf::RenderWindow* window);
    std::string m_text;
private:
    sf::Font m_font;
    sf::Text text;
};