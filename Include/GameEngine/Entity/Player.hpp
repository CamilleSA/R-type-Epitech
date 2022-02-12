#ifndef PLAYER_HPP_
#define PLAYER_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "IEntity.hpp"

class Player: public IEntity {
    public:
        Player(int x, int y, std::string asset);

        virtual bool isPlayer() {
          return true;
        }
        virtual sf::Sprite getSprite() {
          return _playerSprite;
        }

        virtual void setSpritePosition(int x, int y) {
          _playerSprite.setPosition(x, y);
        }

        virtual int getSourceRect() {
            return _sourceSprite.left;
        }

        virtual void setSourceRect(int rect) {
            _sourceSprite.left = rect;
        }

        virtual void updateTextureRect() {
            _playerSprite.setTextureRect(_sourceSprite);
        }

        ~Player() = default;
    private:
      sf::IntRect _sourceSprite;
      sf::Texture _playerText;
      sf::Sprite _playerSprite;
};

#endif
