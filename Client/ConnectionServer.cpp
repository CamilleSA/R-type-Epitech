#include "ConnectionServer.hpp"

ConnectionServer::ConnectionServer()
: _socket(_ios, udp::endpoint(udp::v4(), 0))
{
}

void ConnectionServer::setPortHost(std::string host, std::string port)
{
  udp::resolver resolver(_ios);
  udp::resolver::query query(udp::v4(), host, port);
  udp::resolver::iterator itr = resolver.resolve(query);

  _sender_endpoint = *itr;
  _host = host;
  _port = port;
}

void ConnectionServer::resetReceived() {
  _receivestruct.id = "";
  _receivestruct.msgPlayer.clear();
  _receivestruct.msgObject.clear();
}

void ConnectionServer::createLobby()
{
  std::cout << "Ready connection" << std::endl;
  sender("100", "");

  _ios.poll();
  _ios.reset();
}

void ConnectionServer::joinLobby()
{
  sender("101", "");

  _ios.poll();
  _ios.reset();
}

void ConnectionServer::startGame()
{
  sender("102", "");
  _lobby_to_game = true;

  _ios.poll();
  _ios.reset();
}

void ConnectionServer::playerMoved(int _move)
{
  sender("104", std::to_string(_move));

  _ios.poll();
  _ios.reset();
}

void ConnectionServer::playerShoot()
{
  sender("106", "");

  _ios.poll();
  _ios.reset();
}

void ConnectionServer::sender(std::string id, std::string msg)
{
  _sendstruct.id = id;
  _sendstruct.msg = msg;

  std::ostringstream archive_stream;
  boost::archive::binary_oarchive archive(archive_stream);
  archive << _sendstruct;

	_socket.send_to(boost::asio::buffer(archive_stream.str()), _sender_endpoint);
}


void ConnectionServer::handleReceive()
{
  _socket.async_receive_from(boost::asio::buffer(_tmp, MAX_READ),
                             _sender_endpoint,
                             boost::bind(&ConnectionServer::handleRead,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void ConnectionServer::handleRead(const boost::system::error_code& error, size_t bytes_recvd)
{
    if (!error) {
      _received_length = bytes_recvd;
      std::string buf(_tmp, bytes_recvd);

      std::istringstream archive_stream(buf);
      boost::archive::binary_iarchive archive(archive_stream);
      archive >> _receivestruct;

      if (_receivestruct.id == "103") {
        _game_run = true;
      }
      handleReceive();
    } else {
        std::cerr << "Error in handling send :" << error << std::endl;
  	}
    return;
}

void ConnectionServer::runGame(int _move)
{
  if (_move > 0 && _move < 5) {
    playerMoved(_move);
  } else if (_move == 5) {
    playerShoot();
  } else {
    handleReceive();
    _ios.poll();
    _ios.reset();
  }

  if (!_receivestruct.msgPlayer.empty()) {
    memset(_tmp, 0, _received_length);
  }
}

ConnectionServer::~ConnectionServer()
{
  _socket.close();
}
