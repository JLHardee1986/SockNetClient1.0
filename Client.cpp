#include <iostream>
#include <winsock.h>

#include "NetworkClient.hpp"

int main(int argc, char* argv[]) {
	std::string tmpStr;

	std::cout << "Type Your name: ";
	std::cin >> tmpStr;

	int tmpID = 0;
	NetworkClient netWorker;
	netWorker.Connect(tmpStr);

	return EXIT_SUCCESS;
}