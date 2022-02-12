#include "Obstacles.hpp"

Obstacles::Obstacles(int x, int y, std::string asset)
: _sourceSprite(0, 0, 63, 50)
{
    if (!_music.openFromFile("./Assets/musics/monster.ogg"))
        std::cout << "Error: Could not display _music !" << std::endl;
   
    if (!_obstaclesText.loadFromFile(asset)) {
        std::cout << "Can't find the image" << std::endl;
    }
    _obstaclesSprite.setPosition(x, y);
    _obstaclesSprite.setTexture(_obstaclesText);
    _obstaclesSprite.setScale(1.4, 1.4);
    _obstaclesSprite.setTextureRect(_sourceSprite);
    _music.play();

}
