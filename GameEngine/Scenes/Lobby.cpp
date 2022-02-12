#include "Lobby.hpp"

Lobby::Lobby() {
}

void Lobby::initScene() {
  std::cout << "INIT LOBBY" << std::endl;

  _manage_elem.createObjet<Background>("./Assets/lobby.jpg", BACKGROUND);
  _manage_elem.createObjet<Input>(650, 280, "./Assets/input.png", INPUT_HOST, 30, "./Assets/dodger3_1.ttf", sf::Color::Green);
  _manage_elem.createObjet<Input>(650, 380, "./Assets/input.png", INPUT_PORT, 30, "./Assets/dodger3_1.ttf", sf::Color::Green);
  _manage_elem.createObjet<Icons>(330, -50, "./Assets/LogoLobby.png", ICONS);
  _manage_elem.createObjet<Buttons>(500, 450, "./Assets/create_button.png", BUTTONS_CONNECT);
  _manage_elem.createObjet<Buttons>(900, 450, "./Assets/join_button.png", BUTTONS_JOIN);
  _manage_elem.createObjet<Buttons>(750, 600, "./Assets/ready_button.png", BUTTONS_READY);
}

void Lobby::displayScene(sf::RenderWindow &_window) {
  _manage_elem.displayObjets(_window);
}

void Lobby::deleteElements() {
  _manage_elem.deleteObjets();
}

int Lobby::manageEvent(sf::RenderWindow &_window) {
  while (_window.pollEvent(Event)) {
    switch (Event.type) {
      case sf::Event::Closed: {
        _exit = true;
        break;
      }
      // case sf::Event::MouseMoved: {
      //   sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
      //   sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
      //
      //   if (_manage_elem.getIdObjet(6)->getSprite().getGlobalBounds().contains(mousePosF)) {
      //     //SOUND MOUSE OVER
      //     //music_button.play();
      //     _manage_elem.getIdObjet(6)->getSprite().setColor(sf::Color(250, 20, 20));
      //   } else {
      //     _manage_elem.getIdObjet(6)->getSprite().setColor(sf::Color(255, 255, 255));
      //   }
      //
      //   if (_manage_elem.getIdObjet(7)->getSprite().getGlobalBounds().contains(mousePosF)) {
      //     //SOUND MOUSE OVER
      //     //music_button.play();
      //     _manage_elem.getIdObjet(7)->getSprite().setColor(sf::Color(250, 20, 20));
      //   } else {
      //     _manage_elem.getIdObjet(7)->getSprite().setColor(sf::Color(255, 255, 255));
      //   }
      //   break;
      // }
      case sf::Event::MouseButtonPressed: {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        for (auto &obj : _manage_elem.getListObjet()) {
          if (obj->getSprite().getGlobalBounds().contains(mousePosF)) {
            if (obj->getType() == BUTTONS_CONNECT) {
              _connect = true;
            } else if (obj->getType() == BUTTONS_JOIN) {
              _join = true;
            } else if (obj->getType() == BUTTONS_READY) {
              _ready = true;
            } else if (obj->getType() == INPUT_HOST) {
              _host_input = true;
              _port_input = false;
            } else if (obj->getType() == INPUT_PORT) {
              _host_input = false;
              _port_input = true;
            }
          }
        }
        break;
      }
      case sf::Event::TextEntered: {
        if (Event.text.unicode < 128) {
          for (auto &obj : _manage_elem.getListObjet()) {
            if (obj->getType() == INPUT_HOST && _host_input == true) {
              char _to_send = static_cast<char>(Event.text.unicode);
              obj->setText(_to_send);
              _host = obj->getText().getString().toAnsiString();
            } else if (obj->getType() == INPUT_PORT && _port_input == true) {
              char _to_send = static_cast<char>(Event.text.unicode);
              obj->setText(_to_send);
              _port = obj->getText().getString().toAnsiString();
            }
          }
        }
        break;
      }
    }
  }
  return 0;
}
