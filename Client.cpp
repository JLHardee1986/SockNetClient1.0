////#include <iostream>
////#include <winsock.h>
////
////#define PORT 12345
////
////int nClientSocket;
////
////struct sockaddr_in srv;
////
////int main(int argc, char* argv[])
////{
////	int nRet = 0;
////	WSADATA ws;
////	if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
////	{
////		std::cout << std::endl << "Failed to initialize WSA";
////		WSACleanup();
////		exit(EXIT_FAILURE);
////	}
////	else
////	{
////		std::cout << std::endl << "WSA initialized";
////	}
////
////	nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
////	if (nClientSocket < 0)
////	{
////		std::cout << std::endl << "Failure to make socket";
////		WSACleanup();
////		exit(EXIT_FAILURE);
////	}
////	else
////	{
////		std::cout << std::endl << "Waiting for connection confirmation from server..\n";
////	}
////
////	srv.sin_family = AF_INET;
////	srv.sin_port = htons(PORT);
////	srv.sin_addr.s_addr = inet_addr("10.0.0.49");
////	memset(&(srv.sin_zero), 0, 8);
////	nRet = connect(nClientSocket, (struct sockaddr*)&srv, sizeof(srv));
////
////	if (nRet < 0)
////	{
////		std::cout << std::endl << "Failed to connect";
////		WSACleanup();
////		return (EXIT_FAILURE);
////	}
////	else
////	{
////		// connected to the server
////		// talk
////		while (true)
////		{
////
////			char buff[256+1] = { 0, }; 
////			recv(nClientSocket, buff, 256, 0);
////			std::cout << std::endl << buff;
////			std::cout << std::endl << "\nYou: ";
////			
////			std::cin >> buff;
////			//fgets(&buff[1], 256, stdin);
////			std::cout << std::endl << "Server:  I have received your message young pattawan.\nMessage: " << buff;
////			send(nClientSocket, buff, sizeof(buff), 0);
////			std::cout << std::endl;
////			getchar();
////		}
////			
////	}
////
////	return EXIT_SUCCESS;
////}




// ********************************************************************************
// ********************************************************************************
// ********************************************************************************
// ********************************************************************************

////#include <iostream>
////#include <winsock.h>
////
////#define PORT 12345
////#define MAX_BUFFER_SIZE 256 // Define the maximum buffer size
////#define IP_ADDRESS "10.0.0.49"
////
////class NetworkClient {
////public:
////	NetworkClient() : nClientSocket(0) {
////		// Initialize Winsock
////		if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
////			std::cout << std::endl << "Failed to initialize WSA";
////			WSACleanup();
////			exit(EXIT_FAILURE);
////		}
////		else {
////			std::cout << std::endl << "WSA initialized";
////		}
////
////		nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
////		if (nClientSocket < 0) {
////			std::cout << std::endl << "Failure to create socket";
////			WSACleanup();
////			exit(EXIT_FAILURE);
////		}
////		else {
////			std::cout << std::endl << "Waiting for connection confirmation from server..\n";
////		}
////
////		srv.sin_family = AF_INET;
////		srv.sin_port = htons(PORT);
////		srv.sin_addr.s_addr = inet_addr(IP_ADDRESS);
////		memset(&(srv.sin_zero), 0, 8);
////	}
////
////	void Connect() {
////		int nRet = connect(nClientSocket, (struct sockaddr*)&srv, sizeof(srv));
////		if (nRet < 0) {
////			std::cout << std::endl << "Failed to connect";
////			WSACleanup();
////			exit(EXIT_FAILURE);
////		}
////		else {
////			// Connected to the server
////			// Start communication
////			StartCommunication();
////		}
////	}
////
////	~NetworkClient() {
////		closesocket(nClientSocket);
////		WSACleanup();
////	}
////
////private:
////	WSADATA ws;
////	int nClientSocket;
////	struct sockaddr_in srv;
////
////	void StartCommunication() {
////		char buff[MAX_BUFFER_SIZE + 1] = { 0, };
////		while (true) {
////			recv(nClientSocket, buff, MAX_BUFFER_SIZE, 0);
////			std::cout << std::endl << buff;
////			std::cout << std::endl << "\nYou: ";
////
////			std::cin >> buff;
////			std::cout << std::endl << "Server:  I have received your message young padawan.\nMessage: " << buff;
////			send(nClientSocket, buff, sizeof(buff), 0);
////			std::cout << std::endl;
////			getchar();
////		}
////	}
////};

#include <iostream>
#include <winsock.h>

#include "NetworkClient.hpp"

int main(int argc, char* argv[]) {
	int tmpID = 0;
	NetworkClient netWorker;
	netWorker.Connect();


	return EXIT_SUCCESS;
}