#include "Input.hpp"

Input::Input(int x, int y, std::string asset, ObjectType type,
int size, std::string font_src, sf::Color color) {
  if (!_input.loadFromFile(asset)) {
    std::cout << "Can't find the logo !" << std::endl;
  }
  _inputImage.setTexture(_input);
  _inputImage.setPosition(x, y);

  // Text of Input
  _font.loadFromFile(font_src);
  _playerText.setFont(_font);
  _playerText.setCharacterSize(size);
  _playerText.setString("|");
  _playerText.setPosition(x + 100, y + 10);
  _playerText.setFillColor(color);

  _type = type;
}
