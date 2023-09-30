#ifndef __NETWORKCLIENT__
#define __NETWORKCLIENT__

#include <iostream>
#include <string>
#include <winsock.h>

#include "CONSTANTS.hpp"

class NetworkClient {
public:
	NetworkClient() : nClientSocket(0), playerID(0), name("Bart") {
		// Initialize Winsock
		if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
			std::cout << std::endl << "Failed to initialize WSA";
			WSACleanup();
			exit(EXIT_FAILURE);
		}
		else {
			std::cout << std::endl << "WSA initialized";
		}

		nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (nClientSocket < 0) {
			std::cout << std::endl << "Failure to create socket";
			WSACleanup();
			exit(EXIT_FAILURE);
		}
		else {
			std::cout << std::endl << "Waiting for connection confirmation from server..\n";
		}

		srv.sin_family = AF_INET;
		srv.sin_port = htons(PORT);
		srv.sin_addr.s_addr = inet_addr(IP_ADDRESS);
		memset(&(srv.sin_zero), 0, 8);
	}

	void Connect() {
		int nRet = connect(nClientSocket, (struct sockaddr*)&srv, sizeof(srv));
		if (nRet < 0) {
			std::cout << std::endl << "Failed to connect";
			WSACleanup();
			exit(EXIT_FAILURE);
		}
		else {
			// We are connected on a fresh connection
			// send name of this player to server
			std::cout << std::endl << "Sending name: " << name;
			send(nClientSocket, name.c_str(), sizeof(name.c_str()), 0);

			// wait for a reply that tells me my playerID
			char buff[7 + 1] = { 0, };
			recv(nClientSocket, buff, MAX_BUFFER_SIZE, 0);
	
			// convert return into an int
			const char tmpID[1]{ buff[0] };
			playerID = atoi(tmpID);
			std::cout << std::endl << "This client's Player ID is:" << playerID;
			
			for (int i = 0; i < 8; i++)
			{
				prevBuff[i] = buff[i];
			}
			// Connected to the server
			// Start communication
			StartCommunication();

		}
	}

	~NetworkClient() {
		closesocket(nClientSocket);
		WSACleanup();
	}

private:
	int playerID{ 0 };
	std::string name{ "Bart" };
	WSADATA ws;
	int nClientSocket;
	struct sockaddr_in srv;
	char prevBuff[MAX_BUFFER_SIZE + 1]{ 0, };

	void StartCommunication() {
		char buff[MAX_BUFFER_SIZE + 1] = { 0, };
		while (true) {
			
			send(nClientSocket, prevBuff, sizeof(prevBuff), 0);
			recv(nClientSocket, buff, MAX_BUFFER_SIZE, 0);
			for (int i = 0; i < 8; i++)
			{
				prevBuff[i] = buff[i];
			}
			playerID = buff[0] - '0';
			std::cout << "I am player " << playerID << ", " << name;
			std::string tmpStr = prevBuff;
			std::cout << "The other player's data is: " << tmpStr;
			
		}
	}

	std::string GetOtherPlayerData(bool isAfterASend = true)
	{
		if (isAfterASend)
		{
			char buff[MAX_BUFFER_SIZE + 1] = { 0, };
			recv(nClientSocket, buff, MAX_BUFFER_SIZE, 0);
			std::string tmp;
			tmp = buff;
			return tmp;
		}
		else
		{
			return "NOTSENT";
		}
	}

	void SendData()
	{
		char* buff;
		std::string tmpStr = "";
		switch (playerID)
		{
		case 0:
			tmpStr = "PLAYER0";
			break;
		case 1:
			tmpStr = "PLAYER1";
			break;
		case 2:
			tmpStr = "PLAYER2";
			break;
		default:
			tmpStr = "INVALID";
			break;
		}
		
		buff = new char(strlen(tmpStr.c_str()) + 1);
		send(nClientSocket, buff, sizeof(buff), 0);

		delete[] buff;
	}
};

#endif