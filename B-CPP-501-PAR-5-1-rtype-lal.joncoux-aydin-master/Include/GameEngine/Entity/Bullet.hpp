#ifndef BULLET_HPP_
#define BULLET_HPP_


#include <vector>
#include <iostream>

// Local libs
#include "IEntity.hpp"

class Bullet: public IEntity {
    public:
        Bullet(int x, int y, std::string asset);

        virtual bool isPlayer() {
          return false;
        }
        
        virtual sf::Sprite getSprite() {
          return _bulletSprite;
        }

        virtual void setSpritePosition(int x, int y) {
          _bulletSprite.setPosition(x, y);
        }

        virtual int getSourceRect() {
            return _sourceSprite.left;
        }

        virtual void setSourceRect(int rect) {
            _sourceSprite.left = rect;
        }

        virtual void updateTextureRect() {
            _bulletSprite.setTextureRect(_sourceSprite);
        }

        ~Bullet() = default;
    private:
      sf::IntRect _sourceSprite;
      sf::Texture _bulletText;
      sf::Sprite _bulletSprite;
};


#endif
