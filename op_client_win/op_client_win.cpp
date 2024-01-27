
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>


#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4
#pragma warning(disable:4996)

// 클라이언트는 서버에 접속하자마자 피연산자의 개수정보를 1바이트 정수형태로 전달
// 클라이언트가 서버에 전달하는 정수하나는 4바이트로 표현한다.
// 정수를 전달한다음에는 연산의 종류를 전달한다.
// 문자 +,-,*,중 하나를선택해서 전달
// 서버는 연산결과를 4바이트 정수의 형태로 클라이언트에게 전달
// 연산결과를 얻은 클라이언트는 서버와의 연결을 종료한다.
void ErrorHandling(const char* message);



int main(int argc, char* argv[])
{
	WSAData wsaData;
	SOCKET hSocket;
	char opmsg[BUF_SIZE];
	int result, opndCnt, i;
	SOCKADDR_IN servAdr;
	//if (argc != 3)
	//{
	//	printf("Usage : %s <IP> <port>\n", argv[0]);
	//	exit(1);
	//}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	//servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	inet_pton(AF_INET, "127.0.0.1", &(servAdr.sin_addr.s_addr));
	/*servAdr.sin_port = htons(atoi(argv[2]));*/
	servAdr.sin_port = htons(atoi("9190"));

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
	recv(hSocket,  (char *)&result, RLT_SIZE, 0);

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