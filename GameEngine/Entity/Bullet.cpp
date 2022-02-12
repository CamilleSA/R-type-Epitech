#include "Bullet.hpp"

Bullet::Bullet(int x, int y, std::string asset) {
    if (!_bulletText.loadFromFile(asset)) {
      std::cout << "Error: Could not display Bullet !" << std::endl;
    }

    _bulletSprite.setTexture(_bulletText);
    _bulletSprite.setPosition(x, y);
}
