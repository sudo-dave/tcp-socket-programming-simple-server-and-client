#include<stdio.h>

#include<winsock2.h>
#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib") 




int main(int argc, char* argv[])
{
	int i;
	


	WSADATA wsData;
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	struct sockaddr_in hint;

	hint.sin_family = AF_INET;
	hint.sin_port = htons(8888);
	hint.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	

	int connREsult = connect(sock, (struct sockaddr*)&hint,sizeof(hint));

	if (connREsult == SOCKET_ERROR) {
		printf("Cant connect to server ERR%d", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	puts("Connected");
	char buff[4096];
	char input[1000];

	do {
		printf(">\n");
		fgets(input, 20, stdin);

		for (i = 0; input[i] != '\0'; ++i);

		if (i > 0) {
			
			int sendResult = send(sock, input, i + 1, 0);
			
			if (sendResult != SOCKET_ERROR) {
				int byteREcvied = recv(sock, buff, 4096, 0);

				if (byteREcvied > 0) {
					printf("SERVER -> ");
					buff[byteREcvied] = '\0';
					puts(buff);
				}
			}
		}
		memset(input, 0, sizeof input);
		
	} while (i > 0);

	puts("Shuttind down");
	closesocket(sock);
	WSACleanup();



	return 0;
}
