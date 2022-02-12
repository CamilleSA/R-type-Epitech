#ifndef INPUT_HPP_
#define INPUT_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "IObjet.hpp"

class Input: public IObjet {
    public:
        Input(int x, int y, std::string asset, ObjectType type, int size, std::string font_src, sf::Color color);

        virtual ObjectType getType() {
          return _type;
        };
        virtual sf::Sprite getSprite() {
          return _inputImage;
        };
        virtual sf::Text getText() {
          return _playerText;
        };
        virtual void setText(char new_char) {
          _playerInput += new_char;
          _playerText.setString(_playerInput);
        };

        ~Input() = default;
    private:
      sf::Texture _input;
      sf::Sprite _inputImage;
      std::string _playerInput;

      sf::Font _font;
      sf::Text _playerText;

      ObjectType _type;
};

#endif
