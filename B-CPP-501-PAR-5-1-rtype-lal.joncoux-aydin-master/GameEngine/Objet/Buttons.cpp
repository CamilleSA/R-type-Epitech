#include "Buttons.hpp"

Buttons::Buttons(int x, int y, std::string asset, ObjectType type) {
  //GESTION D'ERREURS POUR VOIR SI LE BOUTON EXISTE
  if (!_buttontexture.loadFromFile(asset)) {
    std::cout << "Can't find the image" << std::endl;
  }

  //POSITION DU BOUTON EXIT
  _buttonImage.setPosition(x, y);

  //POUR CHOPER LA POSITION DE LA SOURIS PAR RAPPORT AU BOUTON
  _buttonWidth = _buttonImage.getLocalBounds().width;
  _buttonHeight = _buttonImage.getLocalBounds().height;

  //INITIALISATION DE LA TEXTURE SUR LE BOUTON
  _buttonImage.setTexture(_buttontexture);
  _type = type;
}
