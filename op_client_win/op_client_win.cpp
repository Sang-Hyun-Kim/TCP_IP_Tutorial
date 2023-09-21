
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>


#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4
#pragma warning(disable:4996)


void ErrorHandling(const char* message);



int main(int argc, char* argv[])
{
	WSAData wsaData;
	SOCKET hSocket;
	char opmsg[BUF_SIZE];
	int result, opndCnt, i;
	char resultmsg[4];
	SOCKADDR_IN servAdr;

	if (argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	//servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	inet_pton(AF_INET, argv[1], &(servAdr.sin_addr.s_addr));
	servAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");
	else
		puts("Connected..........");

	fputs("Operand count: ", stdout);
	scanf("%d", &opndCnt);
	opmsg[0] = (char)opndCnt;

	for (i = 0; i < opndCnt; i++)
	{
		printf("Operand %d: ", i + 1);
		scanf("%d", (int*)&opmsg[i * OPSZ + 1]);
	}

	fgetc(stdin);
	fputs("Operator: ", stdout);
	scanf("%c", &opmsg[opndCnt * OPSZ + 1]);
	send(hSocket, opmsg, opndCnt * OPSZ + 2, 0);
	recv(hSocket,  resultmsg, RLT_SIZE, 0);
	
	result = atoi(resultmsg);

	// 변환 실패 처리
	//recv(hSocket, resultmsg, RLT_SIZE, 0);
	//char* endptr;
	//result = strtol(resultmsg, &endptr, 10);

	//if (*endptr != '\0') {
	//	// 변환 실패 처리
	//	ErrorHandling("Conversion error");
	//}

	printf("Operation Result: %d\n", result);


	printf("Operation Result: %d\n", result);
	closesocket(hSocket);

	WSACleanup();
	return 0;
}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}