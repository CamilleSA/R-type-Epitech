#include "Server.hpp"

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "Please enter a port number" << std::endl;
    return 84;
  }
  try {
    std::string _port(argv[1]);
    Server _serv(std::stoi(_port));

    while (1) {
      _serv.runConnection();
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
	return 0;
}
