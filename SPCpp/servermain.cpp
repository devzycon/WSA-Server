#include "stdafx.h"
#include<iostream>
#include<tchar.h>
#include<WinSock2.h>
#include<WS2tcpip.h>


int main(int numargs, char* args[]) {
	int wsaerr;
	const int port = 55555;

	SOCKET serverSocket/*server's socket */, acceptSocket;/*connection socket*/

	WSADATA wsaData; /*passed in WSAStartup()*/
	WORD wVersionRequested = MAKEWORD(2, 2); // winsock 2.2


	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		std::cout << "Failure to init WinSock" << std::endl;
		return 0;
	}
	else {
		std::cout << "Successfully init'd WinSock" << std::endl;
		std::cout << "Status: " << wsaData.szSystemStatus << std::endl;
	}


	 // creating socket

	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Failure to create SOCKET instance, terminating WSAPI subsystems. ";
		std::cout << WSAGetLastError << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "Successfully created SOCKET instance" << std::endl;
	}

	// Binding socket to server IP & Port

	sockaddr_in service;

	// address details
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);


	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {

		std::cout << "Failure to bind SOCKADDR type to SOCKET instance: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();

		return 0;
	}
	else { std::cout << "Successfully bound IP + port " << port << " to SOCKET instance" << std::endl; }


	// listening via socket

	if (listen(serverSocket, 1) == SOCKET_ERROR)
		std::cout << "Server: Failure to listen via SOCKET instance " << WSAGetLastError() << std::endl;
	else
		std::cout << "Server: Successfully listening via SOCKET instance from port: " << port << ", and awaiting client requests" << std::endl;
		

	// accepting requests from client
	acceptSocket = INVALID_SOCKET;
	acceptSocket = accept(serverSocket, NULL, NULL);

	if (acceptSocket == INVALID_SOCKET) { 
		std::cout << "Server: Failure to accept Client requests, " << WSAGetLastError() << std::endl; 
		
		WSACleanup();
		return -1; 
	
	}
	else
		std::cout << "Server: Successfully established Server-Client Connection from port " << port << std::endl;
	
	// receive msg from client
	std::cout << "Ready to receive messages from client" << std::endl;
	char msgBuffer[200];

	int byteCount = recv(acceptSocket, msgBuffer, 200, 0);

	if (byteCount > 0)
		std::cout << "Message received: " << msgBuffer << std::endl;
	else
		WSACleanup();
	
	// sent msg to client
	
	char recvConfirmation[200] = "Message Received"; // to be sent to client
	byteCount = send(acceptSocket, recvConfirmation, 200, 0);

	if (byteCount > 0)
		std::cout << "Message sent to client";
	else
		WSACleanup();

	return 0;


	
	
}


