#ifndef ICONS_HPP_
#define ICONS_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "IObjet.hpp"

class Icons: public IObjet {
    public:
        Icons(int x, int y, std::string asset, ObjectType type);

        virtual ObjectType getType() {
          return _type;
        };
        virtual sf::Sprite getSprite() {
          return logoImage;
        };
        virtual sf::Text getText() {
          return _playerText;
        };
        virtual void setText(char new_char) {
        };

        ~Icons() = default;
    private:
      // SFML
      sf::Texture logo;
      sf::Sprite logoImage;
      // Unused
      sf::Text _playerText;

      ObjectType _type;
};

#endif
