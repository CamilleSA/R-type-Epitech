#ifndef CLIENT_HPP_
#define CLIENT_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "ConnectionServer.hpp"
#include "ManageScene.hpp"
#include "ManageElement.hpp"

class Client {
  public:
    Client();

    void startGame();

    ~Client();
  private:
    // Network
    ConnectionServer _network;
    void manageConnexion();

    // Navigation
    void manageNavigation();
    int _move_state;

    // Graphical
    ManageScene _scenes;
    ManageElement _objets;
    bool _device_run = false;
};

#endif /* CLIENT_HPP_ */
