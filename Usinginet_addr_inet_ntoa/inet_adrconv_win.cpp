#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	WSAData wsaData;


	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	/* inet_adddr �Լ��� ȣ�� ��*/
	{
		const char *addr = "127.212.124.78";
		unsigned long conv_addr;
		inet_pton(AF_INET, addr, &conv_addr);
		if (conv_addr == INADDR_NONE)
		{
			printf("Error occured \n");
		}
		else
			printf("Network ordered integer addr : %#lx \n",conv_addr);
	}
	/* inet_ntoa �Լ��� ȣ�� ��*/
	{
		struct sockaddr_in addr;
		//char* strPtr;
		char strArr[20];
		int size = 
		addr.sin_addr.s_addr = htonl(0x1020304);
		//strPtr = inet_ntoa(addr.sin_addr);
		inet_ntop(AF_INET, &addr.sin_addr, strArr,sizeof(strArr));
		//strcpy(strArr, strPtr);

		printf("Dotted-Decimal notation3 %s \n", strArr);
	}
	// �� inet_ntoa�� ���ڿ��� �ּҰ��� ��ȯ��(char*), �̴� �Լ��� ����Ǹ鼭 �޸𸮰����� ������ ���ڹ迭�� ������� �� �ּҸ� strPtr�� �־��ִ� ���̴�.
	// �̴� �߰��� inet_ntoa() ����� strPtr�� �����(��ǻ� ����Ű��) ���� ���� ������� ���ο� ���� ���� �ȴ�.
	// ���� inet_ntoa�� ����� �ڿ��� ���ο� ���ڿ��迭�� ������ش��� ���� �ѹ� �� �Ű��ش�.
	// �׸��� ������� �ѹ��� ���ڿ� �迭�� �־��ִ� inet_ntop() �Լ��� ����Ͽ���.

	WSACleanup();
	return 0;

}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
