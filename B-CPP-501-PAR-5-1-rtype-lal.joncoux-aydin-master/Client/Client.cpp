#include "Client.hpp"

Client::Client()
: _network() {
    _scenes.init();
}

void Client::manageConnexion() {
  if (_scenes.getActualScene()->connectButtonClicked() && !_scenes.getActualScene()->getHost().empty() && !_scenes.getActualScene()->getPort().empty()) {
      _network.setPortHost(_scenes.getActualScene()->getHost(), _scenes.getActualScene()->getPort());
      _network.createLobby();
  }
  else if (_scenes.getActualScene()->joinButtonClicked() && !_scenes.getActualScene()->getHost().empty() && !_scenes.getActualScene()->getPort().empty()) {
      _network.setPortHost(_scenes.getActualScene()->getHost(), _scenes.getActualScene()->getPort());
      _network.joinLobby();
  }
  else if (_scenes.getActualScene()->readyButtonClicked()) {
      _network.startGame();
  }
  else {
    if (_network.getNavToGame()) {
      _scenes.nextScene();
    }
    _network.runGame(_move_state);
    _move_state = 0;
    if (_network.getGameState()) {
      if (!_network.getReceivedId().empty())
        _scenes.getActualScene()->updateScene(_network.getReceivedPlayer(), _network.getReceivedObject(), _network.getReceivedBullet(), std::stoi(_network.getReceivedId()));
      _network.resetReceived();
    }
  }
}

void Client::manageNavigation() {
  _move_state = _scenes.getActualScene()->manageEvent(_scenes.getDisplayWindow());
  if (_scenes.getActualScene()->navNextButtonClicked()) {
    _scenes.nextScene();
  }
  if (_scenes.getActualScene()->navPrevButtonClicked()) {
    _scenes.prevScene();
  }
  if (_scenes.getActualScene()->exitButtonClicked()) {
    _scenes.closeScreen();
  }
}

void Client::startGame() {

  _scenes.getActualScene()->initScene();

  // Init music
   _scenes.initMusic();

  // Init la windows
  _scenes.initWindow();

  while (_scenes.windowsIsOpen()) {
    // Connexion button clicked
    manageConnexion();

    // Navigation button clicked
    manageNavigation();

    _scenes.renderScene();
  }
}

Client::~Client() {

}
