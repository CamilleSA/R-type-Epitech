#ifndef BUTTONS_HPP_
#define BUTTONS_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "IObjet.hpp"

class Buttons: public IObjet {
    public:
        Buttons(int x, int y, std::string asset, ObjectType type);

        virtual ObjectType getType() {
          return _type;
        };
        virtual sf::Sprite getSprite() {
          return _buttonImage;
        };
        virtual sf::Text getText() {
          return _playerText;
        };
        virtual void setText(char new_char) {
        };

        ~Buttons() = default;
    private:
      ObjectType _type;

      sf::Texture _buttontexture;
      sf::Sprite _buttonImage;
      float _buttonWidth;
      float _buttonHeight;
      sf::Text _playerText;
};

#endif
