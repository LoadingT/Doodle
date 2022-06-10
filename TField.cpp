#include "TField.h"
#include <string>
#include <iostream>

TextField::TextField()
{
    m_font.loadFromFile("Resources\\20443.otf");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(100, 100);
    text.setFont(this->m_font);
}
void TextField::Draw(sf::RenderWindow* window)
{
    text.setString(sf::String(m_text));
    window->draw(text);
}
void TextField::handleInput(sf::Event e) {
    if (e.type == sf::Event::TextEntered)
    {
        if (e.text.unicode == 8) {   // Delete key
            m_text = m_text.substr(0, m_text.size() - 1);
        }

        else if (e.text.unicode < 128 && m_text.size() < 10)
        {
            m_text += (sf::Uint8)e.text.unicode;
        }
    }
}