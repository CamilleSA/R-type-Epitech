#include "Game.hpp"

Game::Game()
{
}

void Game::initScene()
{
  sf::Color _color(255, 255, 255, 200);
  _manage_elem.createObjet<Background>("./Assets/parallax.jpg", _color, _parallaxShader);
}

void Game::updateScene(std::vector<std::string> _mapPlayer, std::vector<std::string> _mapObject, std::vector<std::string> _mapBullet, int _id) {

  for (int i = 0; i < _mapPlayer.size(); i++) {
     // Player id
    std::size_t pos_elem = _mapPlayer[i].find(":");
    std::string player_id = _mapPlayer[i].substr(0, pos_elem);
    _mapPlayer[i].erase(0, pos_elem + 1);

    // Player X
    pos_elem = _mapPlayer[i].find(":");
    std::string player_x = _mapPlayer[i].substr(0, pos_elem);
    _mapPlayer[i].erase(0, pos_elem + 1);

    // Player Y
    std::string player_y = _mapPlayer[i];

    if (_created_player != _mapPlayer.size()) {
      _player = true;
      _created_player += 1;
      int asset_id = (player_id[1] - 48) - 1;
      _manage_elem.createEntity<Player>(std::stoi(player_x), std::stoi(player_y), _assets_player[asset_id]);
    } else {
      if (_player == true)
        _manage_elem.getIdEntity(i)->setSpritePosition(std::stoi(player_x), std::stoi(player_y));
    }
  }

  for (int i = 0; i < _mapObject.size(); i++) {
    //Object id
    std::size_t pos_elem = _mapObject[i].find(":");
    std::string player_id = _mapObject[i].substr(0, pos_elem);
    if (player_id[1] == '0')
      continue;
    _mapObject[i].erase(0, pos_elem + 1);

      // Object X
    pos_elem = _mapObject[i].find(":");
    std::string object_x = _mapObject[i].substr(0, pos_elem);
    _mapObject[i].erase(0, pos_elem + 1);

    // Object Y
    std::string object_y = _mapObject[i];

    if ( _id == 105) {
      _object = true;
      int random_obstacles = (rand() % (3 + 1));
      _manage_elem.createObstacles<Obstacles>(std::stoi(object_x), std::stoi(object_y), _assets_obstacles[random_obstacles]);
    } else {
      if (_object == true)
        _manage_elem.getIdObstacles(i)->setSpritePosition(std::stoi(object_x), std::stoi(object_y));
    }
  }

  for (int i = 0; i < _mapBullet.size(); i++) {
    //Object id
    std::size_t pos_elem = _mapBullet[i].find(":");
    std::string player_id = _mapBullet[i].substr(0, pos_elem);
    if (player_id[1] == '0')
      continue;
    _mapBullet[i].erase(0, pos_elem + 1);

      // Object X
    pos_elem = _mapBullet[i].find(":");
    std::string object_x = _mapBullet[i].substr(0, pos_elem);
    _mapBullet[i].erase(0, pos_elem + 1);

    // Object Y
    std::string object_y = _mapBullet[i];

    if ( _id == 107 && i == _mapBullet.size() - 1) {
      _manage_elem.createBullets<Bullet>(std::stoi(object_x), std::stoi(object_y), "./Assets/r-typesheet2.gif");
      _bullet = true;
    } else {
      if (_bullet == true)
        _manage_elem.getIdBullets(i)->setSpritePosition(std::stoi(object_x), std::stoi(object_y));
    }
  }
}

void Game::displayScene(sf::RenderWindow &_window) {
  _manage_elem.displayObjets(_window, _parallaxShader, _offset, _clockParrallax);
  _manage_elem.displayEntities(_window);
  _manage_elem.displayObstacles(_window);
}



void Game::deleteElements()
{
  _manage_elem.deleteObjets();
}

int Game::manageEvent(sf::RenderWindow &_window) {

    if (!_music.openFromFile("./Assets/musics/shoot.ogg"))
        std::cout << "Error: Could not display _music !" << std::endl;
    while (_window.pollEvent(_event))
    {
        switch (_event.type) {
        case sf::Event::Closed:
            _exit = true;
            break;
        }
    }

    if(_clockObstacles.getElapsedTime().asSeconds() > 1.0f) {
        for (size_t i = 0; i < _manage_elem.getListObstacles().size(); i++) {
          if (_manage_elem.getIdObstacles(i)->getSourceRect() >= 128) {
              _manage_elem.getIdObstacles(i)->setSourceRect(0);
          }
          else {
                _manage_elem.getIdObstacles(i)->setSourceRect(_manage_elem.getIdObstacles(i)->getSourceRect() + 65);
          }
           _manage_elem.getIdObstacles(i)->updateTextureRect();
        }
        _clockObstacles.restart();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      return TOP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      return LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      return BOT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      return RIGHT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      _music.play();
      return ATTACK;
    }
  return 0;
}
