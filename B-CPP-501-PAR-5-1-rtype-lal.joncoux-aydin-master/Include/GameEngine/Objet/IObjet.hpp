#ifndef IOBJET_HPP_
#define IOBJET_HPP_

#include <vector>
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>

#include "TypeEnum.hpp"

class IObjet {
    public:
        virtual ObjectType getType() = 0;
        virtual sf::Sprite getSprite() = 0;
        virtual sf::Text getText() = 0;
        virtual void setText(char new_char) = 0;
        virtual ~IObjet() = default;
};

#endif
