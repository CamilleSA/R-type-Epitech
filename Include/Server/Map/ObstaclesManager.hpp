#ifndef OBSTACLESMANAGER_HPP_
#define OBSTACLESMANAGER_HPP_

// Standard libs
#include <iostream>
#include <vector>

class ObstaclesManager {
  public:
    ObstaclesManager(int pos, int id) {
      _y = pos;
      _id = id;
    };

    // Getters
    std::string getObjetRequest() {
      return "O" + std::to_string(_id) + ":" + std::to_string(_x) + ":" + std::to_string(_y);
    }
    int getObstacleX() {
      return _x;
    }
    int getObstacleY() {
      return _y;
    }
    bool isReseted() {
      if (_x == -100 && _y == 0 && _id == 0)
        return true;
      return false;
    }

    // Setters
    void delObstacleX(int to_add) {
      _x -= to_add;
    }
    void resetObstacle() {
      _x = -100;
      _y = 0;
      _id = 0;
    }
    void disaparedObstacle() {
      _x = -100;
      _y = 0;
    }

    ~ObstaclesManager() {};
  private:
    int _id = 0;
    int _x = 1700;
    int _y = 0;
};

#endif /* OBSTACLESMANAGER_HPP_ */
