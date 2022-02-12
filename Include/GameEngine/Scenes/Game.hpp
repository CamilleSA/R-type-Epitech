#ifndef GAME_HPP_
#define GAME_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "IScene.hpp"

class Game: public IScene {
    public:
        Game();

        virtual void initScene();
        virtual void displayScene(sf::RenderWindow &_window);
        virtual void deleteElements();
        virtual int manageEvent(sf::RenderWindow &_window);
        virtual void updateScene(std::vector<std::string> _mapPlayer, std::vector<std::string> _mapObject, std::vector<std::string> _mapBullet, int _id);

        // Getters
        virtual bool exitButtonClicked() {
          return _exit;
        }
        virtual bool navNextButtonClicked() {
          return _next;
        }
        virtual bool navPrevButtonClicked() {
          return _prev;
        }
        virtual bool connectButtonClicked() {
          return false;
        }
        virtual bool joinButtonClicked() {
          return false;
        }
        virtual bool readyButtonClicked() {
          return false;
        }
        virtual std::string getHost() {
          return "";
        }
        virtual std::string getPort() {
          return "";
        }

        ~Game() = default;
    private:
      ManageElement _manage_elem;

      // SFML
      float _offset = 0.f;
      sf::Clock _clockParrallax;
      sf::Clock _clockObstacles;
      sf::Event _event;
      sf::Shader _parallaxShader;
      sf::Music _music;
      bool _object = false;
      bool _bullet = false;
      bool _player = false;

      // Scene manager
      bool _exit = false;
      bool _next = false;
      bool _prev = false;

      // Player management
      int _created_player = 0;
      std::vector<std::string> _assets_player = {"./Assets/player1.gif", "./Assets/player2.gif", "./Assets/player3.gif", "./Assets/player4.gif"};

      // Obstacle management
      std::vector<std::string> _assets_obstacles = {"./Assets/mechant1.gif", "./Assets/mechant2.gif", "./Assets/mechant3.gif", "./Assets/mechant4.gif"};
};

#endif /* GAME_HPP_ */
