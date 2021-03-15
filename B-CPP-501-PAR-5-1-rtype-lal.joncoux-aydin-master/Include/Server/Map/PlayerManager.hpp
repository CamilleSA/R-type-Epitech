#ifndef PLAYERMANAGER_HPP_
#define PLAYERMANAGER_HPP_

// Standard libs
#include <iostream>
#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class PlayerManager {
  public:
    PlayerManager(udp::endpoint endpoint, int id) {
      _endpoint = endpoint;
      _id = id;

      switch (id) {
        case 1:
          _x = 30;
          _y = 50;
          break;
        case 2:
          _x = 30;
          _y = 150;
          break;
        case 3:
          _x = 30;
          _y = 250;
          break;
        case 4:
          _x = 30;
          _y = 350;
          break;
      }
    };

    // Getters
    std::string getPlayerRequest() {
      return "P" + std::to_string(_id) + ":" + std::to_string(_x) + ":" + std::to_string(_y);
    }
    udp::endpoint getEndpoint() {
      return _endpoint;
    }
    int getPlayerX() {
      return _x;
    }
    int getPlayerY() {
      return _y;
    }

    // Setters
    void addPlayerX(int to_add) {
      _x += to_add;
    }
    void delPlayerX(int to_del) {
      _x -= to_del;
    }
    void addPlayerY(int to_add) {
      _y += to_add;
    }
    void delPlayerY(int to_del) {
      _y -= to_del;
    }
    void resetPlayer() {
      _x = -100;
      _y = -100;
      _id = 0;
    }
    void disaparedObstacle() {
      _x = -100;
      _y = -100;
    }

    ~PlayerManager() {};
  private:
    int _id = 0;
    int _x = 0;
    int _y = 0;
    udp::endpoint _endpoint;
};

#endif /* PLAYERMANAGER_HPP_ */
