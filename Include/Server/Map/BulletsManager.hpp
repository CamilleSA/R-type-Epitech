#ifndef BulletsSMANAGER_HPP_
#define BulletsSMANAGER_HPP_

// Standard libs
#include <iostream>
#include <vector>

class BulletsManager {
  public:
    BulletsManager(int pos_x, int pos_y, int id) {
      _x = pos_x;
      _y = pos_y;
      _id = id;
    };

    // Getters
    std::string getBulletsRequest() {
      return "B" + std::to_string(_id) + ":" + std::to_string(_x) + ":" + std::to_string(_y);
    }
    int getBulletsX() {
      return _x;
    }
    int getBulletsY() {
      return _y;
    }
    bool isReseted() {
      if (_x == 0 && _y == 0 && _id == 0)
        return true;
      return false;
    }

    // Setters
    void addBulletsX(int to_add) {
      _x += to_add;
    }
    void resetBullets() {
      _x = 0;
      _y = 0;
      _id = 0;
    }

    ~BulletsManager() {};
  private:
    int _id = 0;
    int _x = 0;
    int _y = 0;
};

#endif /* BulletsSMANAGER_HPP_ */
