#ifndef OBSTACLES_HPP_
#define OBSTACLES_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "IEntity.hpp"

class Obstacles: public IEntity {
    public:
        Obstacles(int x, int y, std::string asset);

        virtual bool isPlayer() {
          return false;
        }
        
        virtual sf::Sprite getSprite() {
          return _obstaclesSprite;
        }

        virtual void setSpritePosition(int x, int y) {
          _obstaclesSprite.setPosition(x, y);
        }

        virtual int getSourceRect() {
            return _sourceSprite.left;
        }

        virtual void setSourceRect(int rect) {
            _sourceSprite.left = rect;
        }

        virtual void updateTextureRect() {
            _obstaclesSprite.setTextureRect(_sourceSprite);
        }

        ~Obstacles() = default;
    private:
      sf::IntRect _sourceSprite;
      sf::Texture _obstaclesText;
      sf::Sprite _obstaclesSprite;
      sf::Music _music;
};

#endif
