#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <vector>
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TypeEnum.hpp"

class IEntity {
    public:
        virtual bool isPlayer() = 0;
        virtual sf::Sprite getSprite() = 0;
        virtual void setSpritePosition(int x, int y) = 0;
        virtual int getSourceRect() = 0;
        virtual void setSourceRect(int rect) = 0;
        virtual void updateTextureRect() = 0;
        virtual ~IEntity() = default;
};

#endif
