#include "Server.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

Server::Server(int _port)
: _socket(_io_service, udp::endpoint(udp::v4(), _port))
{
}

// Network
void Server::runConnection()
{
  handleReceive();
  _io_service.poll();
  _io_service.reset();

  handleSend();
  _io_service.poll();
  _io_service.reset();
}



//////////////////////////////// HANDLE RECEIVE
void Server::handleReceive()
{
  _socket.async_receive_from(boost::asio::buffer(_recv_buf, MAXLENGTH),
                             _endpoint,
                             boost::bind(&Server::handleRead,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void Server::handleRead(const boost::system::error_code& error, size_t bytes_recvd)
{
    if (!error) {
      std::string buf(_recv_buf, bytes_recvd);
      std::istringstream archive_stream(buf);
      boost::archive::binary_iarchive archive(archive_stream);
      archive >> _receivestruct;

      int id_request = std::stoi(_receivestruct.id);
      switch (id_request) {
        case 100:
          newClient();
          break;
        case 101:
          joinClient();
          break;
        case 102:
          startGame();
          break;
        case 104:
          movePlayer();
          break;
        case 106:
          createBullets();
          break;
      }
      handleReceive();
  } else {
      std::cerr << "Error in handling send :" << error << std::endl;
	}
}

// Handle request
void Server::newClient()
{
  GameInstance newlobby;
  newlobby.addPlayer(_endpoint);
  _lobby.push_back(newlobby);
}

void Server::joinClient()
{
  _lobby[_lobby.size() - 1].addPlayer(_endpoint);
}

void Server::startGame()
{
  _lobby[_lobby.size() - 1].addPlayerReady();
  if (_lobby[_lobby.size() - 1].allPlayerAreReady() == true) {
    _createPlayer = true;
    for (int i = 0; i < _lobby[_lobby.size() - 1].getPlayerList().size(); i++) {
      _sendstruct.msgPlayer.push_back(_lobby[_lobby.size() - 1].getPlayerById(i).getPlayerRequest());
    }
    sendMap("103");
    sleep(1);
    _gameRun = true;
  }
}

void Server::movePlayer()
{
  int player_id = _lobby[_lobby.size() - 1].getPlayerId(_endpoint);
  int direction = std::stoi(_receivestruct.msg);
  switch (direction) {
    case 1:
      _lobby[_lobby.size() - 1].getPlayerById(player_id).delPlayerY(10);
      break;
    case 2:
      _lobby[_lobby.size() - 1].getPlayerById(player_id).addPlayerY(10);
      break;
    case 3:
      _lobby[_lobby.size() - 1].getPlayerById(player_id).addPlayerX(10);
      break;
    case 4:
      _lobby[_lobby.size() - 1].getPlayerById(player_id).delPlayerX(10);
      break;
  }
}

void Server::createBullets()
{
  // Clock
  if (_duration == 0)
    _start = std::clock();

  _duration = ( std::clock() - _start ) / (double) CLOCKS_PER_SEC;

  if (_duration > 0.000800) {
    _createBullet= false;
    _start = std::clock();
    _duration = ( std::clock() - _start ) / (double) CLOCKS_PER_SEC;
  }
  if (_createBullet== true)
    return;

  int player_id = _lobby[_lobby.size() - 1].getPlayerId(_endpoint);
  int x = _lobby[_lobby.size() - 1].getPlayerById(player_id).getPlayerX() + 50;
  int y = _lobby[_lobby.size() - 1].getPlayerById(player_id).getPlayerY() + 2;

  _lobby[_lobby.size() - 1].addBullet(x, y);
  _sendstruct.msgBullet.push_back(_lobby[_lobby.size() - 1].getBulletById(_lobby[_lobby.size() - 1].getBulletList().size() - 1).getBulletsRequest());

  for (int i = 0; i < _sendstruct.msgBullet.size(); i++) {
    _sendstruct.msgBullet[i] = _lobby[_lobby.size() - 1].getBulletById(i).getBulletsRequest();
    std::cout << "msg bullet : " << _sendstruct.msgBullet[i] << std::endl;
  }

  _createBullet= true;
  sendMap("107");
}



//////////////////////////////// HANDLE SEND
void Server::handleSend()
{

  if (_gameRun == true) {
      if (_createObstacle == false) {
        createObject();
        _createObstacle = true;
        sendMap("105");
        return;
      } else if (_createObstacle == true) {
        moveObstacles();
      }

      if (_createBullet== true) {
        moveBullets();
      }

      checkCollisionObstacles();
      checkCollisionPlayer();

      sendMap("103");
  }
}

void Server::createObject()
{
    srand (time(NULL));
    int pos = 50 + rand() % (700 - 50);
    _lobby[_lobby.size() - 1].addObstacle(pos);
    _sendstruct.msgObject.push_back(_lobby[_lobby.size() - 1].getObstacleById(_lobby[_lobby.size() - 1].getObstacleList().size() - 1).getObjetRequest());
}

void Server::moveObstacles()
{
    for (size_t i = 0; i < _lobby[_lobby.size() - 1].getObstacleList().size(); i++) {
        if (_lobby[_lobby.size() - 1].getObstacleById(i).isReseted() == true) {
          continue;
        } else if (_lobby[_lobby.size() - 1].getObstacleById(i).getObstacleX() <= -100) {
          _lobby[_lobby.size() - 1].getObstacleById(i).resetObstacle();
          _createObstacle = false;
          _sendstruct.msgObject[i] = _lobby[_lobby.size() - 1].getObstacleById(i).getObjetRequest();
          break;
        } else {
          _lobby[_lobby.size() - 1].getObstacleById(i).delObstacleX(20);
        }
    }
}

void Server::moveBullets()
{
    for (size_t i = 0; i < _lobby[_lobby.size() - 1].getBulletList().size(); i++) {
        if (_lobby[_lobby.size() - 1].getBulletById(i).isReseted() == true) {
          continue;
        } else if (_lobby[_lobby.size() - 1].getBulletById(i).getBulletsX() >= 1950) {
          _lobby[_lobby.size() - 1].getBulletById(i).resetBullets();
          _sendstruct.msgBullet[i] = _lobby[_lobby.size() - 1].getBulletById(i).getBulletsRequest();
          break;
        } else {
          _lobby[_lobby.size() - 1].getBulletById(i).addBulletsX(20);
        }
    }
    if (_lobby[_lobby.size() - 1].getAllBulletDeleted()) {
      _createBullet= false;
    }
}

void Server::checkCollisionPlayer() {
  // for (auto &obj : _lobby[_lobby.size() - 1].getObstacleList()) {
  //   int object_x = obj.getObstacleX();
  //   int object_y = obj.getObstacleY();
  //
  //   if (obj.isReseted())
  //     continue;
  //
  //   int index = 0;
  //   for (auto &player : _lobby[_lobby.size() - 1].getPlayerList()) {
  //     int player_x = player.getPlayerX();
  //     int player_y = player.getPlayerY();
  //
  //     if (object_x - player_x <= 30 && object_y - player_x <= 30 &&
  //         object_x - player_y >= -50 && object_y - player_y >= -50) {
  //        _lobby[_lobby.size() - 1].getPlayerById(index).disaparedObstacle();
  //        _sendstruct.msgPlayer[index] = _lobby[_lobby.size() - 1].getPlayerById(index).getPlayerRequest();
  //     }
  //     index += 1;
  //   }
  // }
}

void Server::checkCollisionObstacles() {
  for (auto &bullet : _lobby[_lobby.size() - 1].getBulletList()) {
    int bullet_x = bullet.getBulletsX();
    int bullet_y = bullet.getBulletsY();

    int index = 0;
    for (auto &obj : _lobby[_lobby.size() - 1].getObstacleList()) {
      int object_x = obj.getObstacleX();
      int object_y = obj.getObstacleY();

      if (obj.isReseted()) {
        index = index + 1;
        continue;
      } else if (object_x - bullet_x <= 30 && object_y - bullet_y <= 30 &&
                 object_x - bullet_x >= -50 && object_y - bullet_y >= -50) {
        _lobby[_lobby.size() - 1].getObstacleById(index).disaparedObstacle();
        _sendstruct.msgObject[index] = _lobby[_lobby.size() - 1].getObstacleById(index).getObjetRequest();
      }
      index = index + 1;
    }
  }
}



//////////////////////////////// SEND MAP
void Server::sendMap(std::string id)
{
    _sendstruct.id = id;
    if (_createObstacle == true) {
      for (int i = 0; i < _sendstruct.msgObject.size(); i++) {
        _sendstruct.msgObject[i] = _lobby[_lobby.size() - 1].getObstacleById(i).getObjetRequest();
      }
    }

    if (_createPlayer == true) {
      for (int i = 0; i < _sendstruct.msgPlayer.size(); i++) {
        _sendstruct.msgPlayer[i] = _lobby[_lobby.size() - 1].getPlayerById(i).getPlayerRequest();
      }
    }

    if (_createBullet == true) {
      for (int i = 0; i < _sendstruct.msgBullet.size(); i++) {
        _sendstruct.msgBullet[i] = _lobby[_lobby.size() - 1].getBulletById(i).getBulletsRequest();
      }
    }

    std::ostringstream archive_stream;
    boost::archive::binary_oarchive archive(archive_stream);
    archive << _sendstruct;

    usleep(70000);
    for (auto client : _lobby[_lobby.size() - 1].getPlayerList()) {
      _socket.send_to(boost::asio::buffer(archive_stream.str()), client.getEndpoint());
    }
}

Server::~Server() {
    _socket.close();
    _io_service.stop();
}
