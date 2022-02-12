#ifndef TEXT_HPP_
#define TEXT_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "IObjet.hpp"

class Text: public IObjet {
    public:
        Text(int x, int y, int size, std::string placeholder, std::string font_src, sf::Color color, ObjectType type);

        virtual ObjectType getType() {
          return _type;
        };
        virtual sf::Sprite getSprite() {
          return _unused_sprite;
        };
        virtual sf::Text getText() {
          return _playerText;
        };
        virtual void setText(char new_char) {
        };

        ~Text() = default;
    private:
      sf::String playerInput;
      sf::Text _playerText;
      sf::Font _font;

      //Unused
      sf::Sprite _unused_sprite;

      ObjectType _type;
};

#endif
