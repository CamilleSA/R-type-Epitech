#include "Player.hpp"

Player::Player(int x, int y, std::string asset) {
  if (!_playerText.loadFromFile(asset)) {
    std::cout << "Can't find the image" << std::endl;
  }
  _playerSprite.setPosition(x, y);
  _playerSprite.setTexture(_playerText);
  _playerSprite.setScale(1.4, 1.4);
}
