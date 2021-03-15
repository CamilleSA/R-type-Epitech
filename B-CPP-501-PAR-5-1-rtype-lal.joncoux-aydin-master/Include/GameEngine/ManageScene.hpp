#ifndef MANAGESCENE_HPP_
#define MANAGESCENE_HPP_

// Standard libs
#include <iostream>
#include <memory>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Local libs
#include "IScene.hpp"
#include "Menu.hpp"
#include "Lobby.hpp"
#include "Game.hpp"

class ManageScene {
  public:
    ManageScene();

    // Scenes management
    void init();
    void nextScene();
    void prevScene();

    // SFML
    void initWindow();
    void initMusic();
    void renderScene();
    void closeScreen();

    // Getters
    std::vector<std::shared_ptr<IScene>> getListScene() {
      return _list_scenes;
    }
    std::shared_ptr<IScene> getActualScene() {
      return _list_scenes[_actual_index];
    }
    bool windowsIsOpen() {
      return _window.isOpen();
    }
    sf::RenderWindow &getDisplayWindow() {
      return _window;
    }
    int getWidthSize() {
      return _width;
    }
    int getHeightSize() {
      return _height;
    }
    std::string getAssetsSize() {
      return _assets_size;
    }

    ~ManageScene();
  private:
    int _actual_index = 0;
    std::vector<std::shared_ptr<IScene>> _list_scenes;

    // Window
    sf::RenderWindow _window;
    int _width = 0;
    int _height = 0;
    std::string _assets_size;

    // Audio
    sf::Music _music;
};

#endif /* MANAGESCENE_HPP_ */
