#ifndef CONNECTIONSERVER_H
#define CONNECTIONSERVER_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <deque>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

// Local libs
#include "Packet.hpp"

using boost::asio::ip::udp;
#define MAX_READ 15000

struct datasReceive
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

struct datasSend
{
    std::string id;
    std::string msg;

    template<typename archive> void serialize(archive& ar, const unsigned /*version*/) {
        ar &id;
        ar &msg;
    }
};

class ConnectionServer
{
    public :
        ConnectionServer();

        // Request management
        void createLobby();
        void joinLobby();
        void startGame();
        void runGame(int _move);

        // Getters
        bool getGameState() {
          return _game_run;
        }
        bool getNavToGame() {
          if (_lobby_to_game == true) {
            _lobby_to_game = false;
            return true;
          }
          return _lobby_to_game;
        }
        std::vector<std::string> getReceivedObject() {
          return _receivestruct.msgObject;
        }

        std::vector<std::string> getReceivedBullet() {
            return _receivestruct.msgBullet;
        }

        std::vector<std::string> getReceivedPlayer() {
            return _receivestruct.msgPlayer;
        }

        std::string getReceivedId() {
          return _receivestruct.id;
        }

        // Setters
        void resetReceived();
        void setPortHost(std::string host, std::string port);

        ~ConnectionServer();

    private :
        // Connexion
        boost::asio::io_service _ios;
        udp::socket _socket;
        udp::endpoint _sender_endpoint;
        std::string _host;
        std::string _port;
        bool _game_run = false;
        bool _lobby_to_game = false;

        // Send / Receive handler
        void handleReceive();
        void handleRead(const boost::system::error_code& error, size_t number_bytes_read);
        void sender(std::string id, std::string msg);

        // Storage Data
        int _received_length = MAX_READ;
        char _tmp[MAX_READ];
        datasSend _sendstruct;
        datasReceive _receivestruct;

        // Manage Player
        void playerMoved(int _move);
        void playerShoot();
};

#endif
