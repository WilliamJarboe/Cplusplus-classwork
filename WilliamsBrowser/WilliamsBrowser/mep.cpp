#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
int main()
{
	//initializing winsock
	WSADATA wsaData;
	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	
	//	GET / HTTP / 1.1\r\nHost: XXX.com\r\n\r\n

	//creating a socket for a client
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//specifying ip address and port
	#define DEFAULT_PORT "80"
	// Resolve the server address and port
	iResult = getaddrinfo("www.epguides.com", DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	//creating a socket
	SOCKET ConnectSocket = INVALID_SOCKET;
	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;
	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n",
			WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	//connect to a socket

	// Connect to server.
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}


	//sending data
	#define DEFAULT_BUFLEN 512
	int sendbuflen = DEFAULT_BUFLEN;
	char sendbuf[DEFAULT_BUFLEN] = "GET /simpsons/  HTTP/1.1\r\nHost: epguides.com\r\n\r\n";
	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	//recieving data
	//#define DEFAULT_BUFLEN 512
	//char *sendbuf = "this is a test";
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
	string h = "";
	string temp = "";
	// Receive data until the server closes the connection

	//
	do {
		
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		//printf("recv failed: %d\n", WSAGetLastError());
		


		if (iResult > 0)
		{
			temp = recvbuf;
			h += temp.substr(0, 504);
			Sleep(7);
			if (iResult != 512)
			{
				break;
			}
		}
		else if (iResult == 0)
		{
			//...
			break;
		}
		else
		{
			printf("recv failed: %d\n", WSAGetLastError());
		}
	} while (iResult > 0);

	
		
	//
	
	std::stringstream ss;
	ss << h;
	std::string to;
	int i = 0;
	bool isIgnoringSCRIPT = false;
	

	while (std::getline(ss, to, '\n')) {
		i++;
		//printf("Line %i\n",i);
		to.erase(to.find_last_not_of(" \n\r\t") + 1);
		to.erase(0,to.find_first_not_of(" \t"));
		if (to == "<script>")
		{
			isIgnoringSCRIPT = true;
		}
		if (to == "</script>")
		{
			isIgnoringSCRIPT = false;
		}
		if (to.substr(0, 7) == "<title>")
		{
			to = to.substr(7, to.length() - 15);
			printf("%s\n", to.c_str());
		}

		//<tr><td class='epinfo right'>89.</td><td class='epinfo left pad'>5-8&nbsp;</td><td class='epinfo right pad'>18 Nov 93</td><td class='eptitle left'><a target="_blank" href="https://www.tvmaze.com/episodes/5086/the-simpsons-5x08-boy-scoutz-n-the-hood">Boy-Scoutz 'n the Hood</a></td></tr>
		if (to.length() > 16 && to.substr(to.length() - 14, to.length()) == "</a></td></tr>")
		{
			to = to.substr(0, to.length() - 14);
			int a = 0, b = 0;

			for (int a = b; a < to.length(); a++) {
				if (to[a] == '<') {
					for (int b = a; b < to.length(); b++) {
						if (to[b] == '>') {
							to.erase(a, (b - a + 1));
							break;
						}
					}
				}
			}
			a = 0;
			b = 0;

			for (int a = b; a < to.length(); a++) {
				if (to[a] == '<') {
					for (int b = a; b < to.length(); b++) {
						if (to[b] == '>') {
							to.erase(a, (b - a + 1));
							break;
						}
					}
				}
			}
			a = 0;
			b = 0;

			for (int a = b; a < to.length(); a++) {
				if (to[a] == '<') {
					for (int b = a; b < to.length(); b++) {
						if (to[b] == '>') {
							to.erase(a, (b - a + 1));
							break;
						}
					}
				}
			}
			printf("%s\n", to.c_str());
		}

		else if ((to.substr(0, 1) != "<" && to.substr(0, 1) != ">" && to.substr(0, 1) != "&" && to != "" && to != "<!--" && to != "//-->" && to != "{" && to != "}" && to.substr(to.length()-1, to.length()) !=";" && to.substr(to.length() - 1, to.length()) != "{" && to.substr(to.length() - 1, to.length()) != "}") && !isIgnoringSCRIPT)
		{
			int a = 0, b = 0;

			for (int a = b; a < to.length(); a++) {
				if (to[a] == '<') {
					for (int b = a; b < to.length(); b++) {
						if (to[b] == '>') {
							to.erase(a, (b - a + 1));
							break;
						}
					}
				}
			}

			printf("%s\n", to.c_str());
		}



		if (("<!--" && to != "//-->")&&!isIgnoringSCRIPT)
		{
			int a = 0, b = 0;

			for (int a = b; a < to.length(); a++) {
				if (to[a] == '<') {
					for (int b = a; b < to.length(); b++) {
						if (to[b] == '>') {
							to.erase(a, (b - a + 1));
							break;
						}
					}
				}
			}
			//printf("[NOT REAL]%s\n", to.c_str());
		}
		else
		{
			
		}
	}
	system("pause");

	








	
	
	

	// shutdown the connection for sending since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	//just closing

	printf("8\n");

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
	return 0;




}