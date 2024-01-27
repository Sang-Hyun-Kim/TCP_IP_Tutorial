// uecho_server.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <string>

#define BUF_SIZE 1024

#pragma warning(disable:4996)
// connected UDP 방식
void ErrorHandling(const char* message);
int main(int argc, char* argv[])
{

	WSADATA wsaData;
	SOCKET sock;
	char message[BUF_SIZE];
	int strLen;
	SOCKADDR_IN servAdr, from_adr;
	//if (argc != 3) {
	//	printf("Usage : %s <IP> <port>\n", argv[0]);
	//	exit(1);
	//}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	//servAdr.sin_addr.s_addr = inet_addr(argv[1]);
	servAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//servAdr.sin_port = htons(atoi(argv[2]));
	servAdr.sin_port = htons(atoi("9190"));
	connect(sock, (SOCKADDR*)&servAdr, sizeof(servAdr));

	while (1)
	{
		fputs("Insert message(q to quit): ", stdout);
		fgets(message, sizeof(message), stdin);
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;
		 //sendto(sock, message, sizeof(message), 0, (SOCKADDR*)&servAdr, sizeof(servAdr)); // unconnectedUDP;

		send(sock, message, strlen(message), 0);
		strLen = recv(sock, message, sizeof(message) - 1, 0);
		//int adr_sz = sizeof(from_adr);
		//strLen = recvfrom(sock, message, BUF_SIZE, 0, (SOCKADDR*)&from_adr, &adr_sz); // unconnectedUDP;
		message[strLen] = 0;
		printf("Message from server: %s", message);
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}
void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}