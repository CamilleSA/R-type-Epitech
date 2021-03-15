#include "Text.hpp"

Text::Text(int x, int y, int size, std::string placeholder, std::string font_src, sf::Color color, ObjectType type)
{
    _font.loadFromFile(font_src);
    _playerText.setFont(_font);
    _playerText.setCharacterSize(size);
    _playerText.setString(placeholder);
    _playerText.setPosition(x, y);
    _playerText.setFillColor(color);
    _type = type;
}
