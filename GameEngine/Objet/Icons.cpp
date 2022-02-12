#include "Icons.hpp"

Icons::Icons(int x, int y, std::string asset, ObjectType type) {
  //GESTION D'ERREURS POUR VOIR SI LE LOGO EXISTE BIEN
  if (!logo.loadFromFile(asset)) {
    std::cout << "Can't find the logo !" << std::endl;
  }

  //INITIALISATION DE LA TEXTURE AU LOGO
  logoImage.setTexture(logo);
  //POSITION DU LOGO
  logoImage.setPosition(x, y);
  _type = type;
}
