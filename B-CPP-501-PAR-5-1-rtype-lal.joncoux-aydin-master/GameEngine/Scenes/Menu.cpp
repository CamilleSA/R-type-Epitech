#include "Menu.hpp"

Menu::Menu() {
}

void Menu::initScene() {
  std::cout << "INIT MENU" << std::endl;

  _manage_elem.createObjet<Background>("./Assets/background.jpg", BACKGROUND);
  _manage_elem.createObjet<Icons>(330, -50, "./Assets/logo_r-type.png", ICONS);
  _manage_elem.createObjet<Buttons>(750, 700, "./Assets/exit_button.png", BUTTONS);
  _manage_elem.createObjet<Buttons>(750, 400, "./Assets/lobby_button.png", BUTTONS);
}

void Menu::displayScene(sf::RenderWindow &_window) {
  _manage_elem.displayObjets(_window);
}

void Menu::deleteElements() {
  _manage_elem.deleteObjets();
}

int Menu::manageEvent(sf::RenderWindow &_window) {
    while (_window.pollEvent(Event)) {
        switch (Event.type) {
            case sf::Event::Closed: {
              _exit = true;
              break;
            }

            case sf::Event::MouseMoved: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                //PETITE CONDITION POUR CHANGER LA COULEUR DES BOUTONS QUAND ON PASSE DESSUS
                if (_manage_elem.getIdObjet(2)->getSprite().getGlobalBounds().contains(mousePosF)) {
                  //SOUND MOUSE OVER
                  //music_button.play();
                  _manage_elem.getIdObjet(2)->getSprite().setColor(sf::Color(250, 20, 20));
                } else {
                  _manage_elem.getIdObjet(2)->getSprite().setColor(sf::Color(255, 255, 255));
                }

                if (_manage_elem.getIdObjet(3)->getSprite().getGlobalBounds().contains(mousePosF)) {
                  //SOUND MOUSE OVER
                  //music_button.play();
                  _manage_elem.getIdObjet(3)->getSprite().setColor(sf::Color(250, 20, 20));
                } else {
                  _manage_elem.getIdObjet(3)->getSprite().setColor(sf::Color(255, 255, 255));
                }
                break;
            }

            case sf::Event::MouseButtonPressed: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (_manage_elem.getIdObjet(2)->getSprite().getGlobalBounds().contains(mousePosF)) {
                    _exit = true;
                }
                if (_manage_elem.getIdObjet(3)->getSprite().getGlobalBounds().contains(mousePosF)) {
                    _next = true;
                }
                break;
            }
        }
    }
    return 0;
}
