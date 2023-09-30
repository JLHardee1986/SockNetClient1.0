#include <iostream>
#include <winsock.h>

#define PORT 12345

int nClientSocket;

struct sockaddr_in srv;

int main(int argc, char* argv[])
{
	int nRet = 0;
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws) < 0)
	{
		std::cout << std::endl << "Failed to initialize WSA";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << std::endl << "WSA initialized";
	}

	nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (nClientSocket < 0)
	{
		std::cout << std::endl << "Failure to make socket";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << std::endl << "Waiting for connection confirmation from server..\n";
	}

	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(srv.sin_zero), 0, 8);
	nRet = connect(nClientSocket, (struct sockaddr*)&srv, sizeof(srv));

	if (nRet < 0)
	{
		std::cout << std::endl << "Failed to connect";
		WSACleanup();
		return (EXIT_FAILURE);
	}
	else
	{
		// connected to the server
		// talk
		while (true)
		{

			char buff[256+1] = { 0, }; 
			recv(nClientSocket, buff, 257, 0);
			std::cout << std::endl << buff;
			std::cout << std::endl;
			fgets(buff, 257, stdin);
			send(nClientSocket, buff, sizeof(buff)-1, 0);
			std::cout << std::endl << "\nYou: ";
			getchar();
			
		}
			
	}

	return EXIT_SUCCESS;
}