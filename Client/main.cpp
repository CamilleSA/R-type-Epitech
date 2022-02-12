#include "Client.hpp"

int main(int argc, char** argv)
{
	try	{
		Client _cli;

		_cli.startGame();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
