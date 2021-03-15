#ifndef SERVER_HPP_
#define SERVER_HPP_

// Standard libs
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <thread>
#include <string>
#include <cstdio>
#include <ctime>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

// Local libs
#include "GameInstance.hpp"

using boost::asio::ip::udp;
#define MAXLENGTH 1500000

struct datasSend
{
    std::string id;
    std::vector<std::string> msgObject;
    std::vector<std::string> msgBullet;
    std::vector<std::string> msgPlayer;

    template<typename archive> void serialize(archive& ar, const unsigned /*version*/) {
        ar &id;
        ar &msgObject;
        ar &msgBullet;
        ar &msgPlayer;
    }
};

struct datasReceive
{
    std::string id;
    std::string msg;

    template<typename archive> void serialize(archive& ar, const unsigned /*version*/) {
        ar &id;
        ar &msg;
    }
};


class Server {
  public:
    Server(int _port);

    // Network
    void runConnection();

    // Request to send
    void handleSend();

    void createObject();
    void moveObstacles();
    void moveBullets();
    void checkCollisionObstacles();
    void checkCollisionPlayer();

    // Request to read
    void handleReceive();
    void handleRead(const boost::system::error_code& error, size_t bytes_recvd);

    void newClient();
    void joinClient();
    void startGame();
    void movePlayer();
    void createBullets();

    void sendMap(std::string id);

    ~Server();
  private:
    // Network Management
    boost::asio::io_service _io_service;
    udp::endpoint _endpoint;
    udp::socket _socket;
    bool _gameRun = false;
    bool _createObstacle = false;
    bool _createPlayer = false;
    bool _createBullet = false;

    // Clock management
    std::clock_t _start;
    double _duration = 0.000000;

    // Network Data
    char _recv_buf[MAXLENGTH] = "";
    datasSend _sendstruct;
    datasReceive _receivestruct;

    // Game Instance
    std::vector<GameInstance> _lobby;
    std::vector<std::thread> myThreads;
};

#endif /* SERVER_HPP_ */
