#include "Background.hpp"

Background::Background(std::string asset, ObjectType type) {
    //GESTION D'ERREURS POUR VOIR SI LE BACKGROUND EXISTE BIEN
    if (!_background.loadFromFile(asset)) {
      std::cout << "Error: Could not display Background Space !" << std::endl;
    }

    //INITIALISATION DE LA TEXTURE AU BACKGROUND
    _backgroundImage.setTexture(_background);
    _type = type;
}

Background::Background(std::string asset, sf::Color _color, sf::Shader &parallaxShader) {
    if (!_background.loadFromFile(asset)) {
      std::cout << "Error: Could not display Parallax !" << std::endl;
    }

   _background.setRepeated(true);
   _backgroundImage.setTexture(_background);

   _backgroundImage.setPosition(0, 0);
   _backgroundImage.setColor(_color);

   parallaxShader.loadFromMemory(
       "uniform float offset;"

       "void main() {"
       "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
       "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
       "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" // magic
       "    gl_FrontColor = gl_Color;"
       "}"
       , sf::Shader::Vertex);
}
