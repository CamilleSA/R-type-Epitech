#include "ManageScene.hpp"

ManageScene::ManageScene() {

}

void ManageScene::init() {

  // Add Menu to _list_scenes
  std::shared_ptr<Menu> _menu = std::make_shared<Menu>();
  _list_scenes.push_back(_menu);
  // Add lobby to _list_scenes
  std::shared_ptr<Lobby> _lobby = std::make_shared<Lobby>();
  _list_scenes.push_back(_lobby);
  // Add Game to _list_scenes
  std::shared_ptr<Game> _game = std::make_shared<Game>();
  _list_scenes.push_back(_game);
}

void ManageScene::nextScene() {
  // Delete assets
  _list_scenes[_actual_index]->deleteElements();

  // Change actual scene by next scene in array
  _actual_index += 1;

  // Init next scene
  _list_scenes[_actual_index]->initScene();
}

void ManageScene::prevScene() {
  // Delete assets
  _list_scenes[_actual_index]->deleteElements();

  // Change actual scene by prev scene in array
  _actual_index -= 1;

  // Init next scene
  _list_scenes[_actual_index]->initScene();
}


// ----------SFML---------

void ManageScene::initWindow() {
  _window.create(sf::VideoMode(1920, 1080), "Spaceship action!", sf::Style::Default);
  _width = 1920;
  _height = 1080;
  _window.setFramerateLimit(60);
  _window.setVerticalSyncEnabled(true);
}

void ManageScene::initMusic() {
    if (!_music.openFromFile("./Assets/musics/music-r-type.ogg"))
        std::cout << "Error: Could not display _music !" << std::endl;
   
    _music.play();
}

void ManageScene::renderScene() {
  _window.clear();
  _list_scenes[_actual_index]->displayScene(_window);
  _window.display();
}

void ManageScene::closeScreen() {
  _window.close();
}

ManageScene::~ManageScene() {

}
