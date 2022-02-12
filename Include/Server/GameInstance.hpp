#ifndef GAMEINSTANCE_HPP_
#define GAMEINSTANCE_HPP_

// Standard libs
#include <iostream>
#include <boost/asio.hpp>

// Local libs
#include "PlayerManager.hpp"
#include "ObstaclesManager.hpp"
#include "BulletsManager.hpp"

using boost::asio::ip::udp;

class GameInstance {
  public:
    GameInstance();

    // Getters Player
    std::vector<PlayerManager> getPlayerList() {
      return _list_player;
    }
    PlayerManager &getPlayerById(int id) {
      return _list_player[id];
    }
    int getPlayerId(udp::endpoint endpoint) {
      int id = 0;
      for (auto &client : _list_player) {
        if (client.getEndpoint() == endpoint)
          return id;
        id += 1;
      }
      return -1;
    }
    bool allPlayerAreReady() {
      if (_nb_player_ready == _nb_player)
        return true;
      return false;
    }

    // Setters Player
    void addPlayer(udp::endpoint endpoint) {
      if (_nb_player <= 4) {
        _nb_player += 1;
        PlayerManager _new_player(endpoint, _player_id);
        _list_player.push_back(_new_player);
        _player_id += 1;
      }
    }
    void addPlayerReady() {
      if (_nb_player_ready <= 4)
        _nb_player_ready += 1;
    }

    // Getters Obstacles
    std::vector<ObstaclesManager> getObstacleList() {
      return _list_obstacles;
    }
    ObstaclesManager &getObstacleById(int id) {
      return _list_obstacles[id];
    }

    // Setters Obstacles
    void addObstacle(int pos) {
      ObstaclesManager new_obstacle(pos, _obstacle_id);
      _list_obstacles.push_back(new_obstacle);
      _obstacle_id += 1;
    }

    // Getters Bullets
    std::vector<BulletsManager> getBulletList() {
      return _list_bullets;
    }
    BulletsManager &getBulletById(int id) {
      return _list_bullets[id];
    }
    bool getAllBulletDeleted() {
      int nb_reseted = 0;
      for (auto &bullet : _list_bullets) {
        if (bullet.isReseted())
          nb_reseted += 1;
      }
      if (nb_reseted == _list_bullets.size())
        return true;
      return false;
    }

    // Setters Bullets
    void addBullet(int pos_x, int pos_y) {
      BulletsManager new_bullet(pos_x, pos_y, _bullets_id);
      _list_bullets.push_back(new_bullet);
      _bullets_id += 1;
    }

    ~GameInstance();
  private:
    // Player
    int _player_id = 1;
    std::vector<PlayerManager> _list_player;

    // Obstacles
    int _obstacle_id = 1;
    std::vector<ObstaclesManager> _list_obstacles;

    // Bullets
    int _bullets_id = 1;
    std::vector<BulletsManager> _list_bullets;

    int _id = 0;
    int _nb_player = 0;
    int _nb_player_ready = 0;
};

#endif /* GAMEINSTANCE_HPP_ */
