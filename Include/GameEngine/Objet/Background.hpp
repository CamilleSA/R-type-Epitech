#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "IObjet.hpp"

class Background: public IObjet {
    public:
        Background(std::string asset, ObjectType type);
        Background(std::string asset, sf::Color _color, sf::Shader &parallaxShader);

        virtual ObjectType getType() {
          return _type;
        };
        virtual sf::Sprite getSprite() {
          return _backgroundImage;
        };
        virtual sf::Text getText() {
          return _playerText;
        };
        virtual void setText(char new_char) {
        };

        ~Background() = default;
    private:
      ObjectType _type;
      // SFML
      sf::Texture _background;
      sf::Sprite _backgroundImage;
      sf::Text _playerText;
};

#endif
