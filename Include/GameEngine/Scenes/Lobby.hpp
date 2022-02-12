#ifndef LOBBY_HPP_
#define LOBBY_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "IScene.hpp"

class Lobby: public IScene {
    public:
        Lobby();

        virtual void initScene();
        virtual void displayScene(sf::RenderWindow &_window);
        virtual void deleteElements();
        virtual int manageEvent(sf::RenderWindow &_window);
        virtual void updateScene(std::vector<std::string> _mapPlayer, std::vector<std::string> _mapObject, std::vector<std::string> _mapBullet, int _id) {};

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
          if (_connect == true) {
            _connect = false;
            return true;
          }
          return false;
        }
        virtual bool joinButtonClicked() {
          if (_join == true) {
            _join = false;
            return true;
          }
          return false;
        }
        virtual bool readyButtonClicked() {
          if (_ready == true) {
            _ready = false;
            return true;
          }
          return false;
        }
        virtual std::string getHost() {
          return _host;
        }
        virtual std::string getPort() {
          return _port;
        }

        ~Lobby() = default;
    private:
      ManageElement _manage_elem;

      // Events
      sf::Event Event;

      // Scene manager
      bool _exit = false;
      bool _next = false;
      bool _prev = false;

      // Input management
      bool _host_input = false;
      bool _port_input = false;
      std::string _host;
      std::string _port;

      // Connexion management
      bool _connect = false;
      bool _join = false;
      bool _ready = false;
};

#endif /* LOBBY_HPP_ */
