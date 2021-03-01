#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") 




int main(int argc, char* argv[])
{
	//INtialze winsock
	WSADATA wsData;
	SOCKET listening, ClientSocket;
	char* message = "Hello\n";

	struct sockaddr_in   server, client;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.");
	//Create socekt


	listening = socket(AF_INET, SOCK_STREAM, 0);

	if (listening == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		return 1;
	}



	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(7777);

	

	if (bind(listening, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
	}
	puts("Connected");

	listen(listening, SOMAXCONN);


	puts("Waiting for incoming connections...");

	int c_size = sizeof(struct sockaddr_in);
	ClientSocket = accept(listening, (struct sockaddr*)&client, &c_size);

	
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d", WSAGetLastError());
	}

	char host[NI_MAXHOST]; 
	char service[NI_MAXHOST]; 

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);



	puts("conected");
	closesocket(listening);
	char buff[4096];
	
	send(ClientSocket, message, strlen(message), 0);

	while (1) {
		ZeroMemory(buff, 4096);

		int bytesRecived = recv(ClientSocket, buff, 4096, 0);
		
		if (bytesRecived == SOCKET_ERROR) {
			puts("error in recv(). qutititng");
			break;
		}
		if (bytesRecived == 0) {
			puts("clinet disconexted");
			break;
		}

		send(ClientSocket, buff, bytesRecived + 1, 0);

	}
	closesocket(ClientSocket);
	WSACleanup();
	//Reply to client
	






	return 0;
}
