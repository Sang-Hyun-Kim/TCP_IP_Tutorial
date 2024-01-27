// Op_Server.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <string>
#define BUF_SIZE 1024
#define OPSZ 4
#pragma warning(disable:4996)
// 클라이언트는 서버에 접속하자마자 피연산자의 개수정보를 1바이트 정수형태로 전달
// 클라이언트가 서버에 전달하는 정수하나는 4바이트로 표현한다.
// 정수를 전달한다음에는 연산의 종류를 전달한다.
// 문자 +,-,*,중 하나를선택해서 전달
// 서버는 연산결과를 4바이트 정수의 형태로 클라이언트에게 전달
// 연산결과를 얻은 클라이언트는 서버와의 연결을 종료한다.

void ErrorHandling(const char* message);
int calculate(int opnum, int opnds[], char op);
int main(int argc,char *argv[])
{
	WSAData wsaData;
	SOCKET hServSock, hClntSock;
	char opinfo[BUF_SIZE];
	int result, opndCnt, i;
	int recvCnt, recvLen;

	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;
	
	if (argc != 2)
	{
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if(bind(hServSock,(SOCKADDR*)&servAdr,sizeof(servAdr))==SOCKET_ERROR)
		ErrorHandling("bind() error");

	if(listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	clntAdrSize = sizeof(clntAdr);

	for (i = 0; i < 5; ++i)
	{
		opndCnt = 0;
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);
		printf("Client Connected");
		recv(hClntSock, (char *)&opndCnt, 1, 0);
		recvLen = 0;
		printf("opndCnt = %d", opndCnt);
		while ((opndCnt*OPSZ+1)>recvLen)
		{
			recvCnt = recv(hClntSock, &opinfo[recvLen], BUF_SIZE - 1, 0);
			recvLen += recvCnt;
		}
		result = calculate(opndCnt, (int*)opinfo, opinfo[recvLen - 1]);
		
		send(hClntSock, (char*)&result, sizeof(result), 0);
		closesocket(hClntSock);
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;
}
int calculate(int opnum, int opnds[], char op)
{
	int result = opnds[0], i;
	switch (op)
	{
		case '+':
			for (i = 1; i < opnum; ++i) result += opnds[i];
			break;
		case '-':
			for (i = 1; i < opnum; ++i) result -= opnds[i];
			break;
		case '*':
			for (i = 1; i < opnum; ++i) result *= opnds[i];
			break;
	}
	return result;
}
void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}