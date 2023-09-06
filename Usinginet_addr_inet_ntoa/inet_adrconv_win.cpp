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

	/* inet_adddr 함수의 호출 예*/
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
	/* inet_ntoa 함수의 호출 예*/
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
	// 자 inet_ntoa는 문자열의 주소값을 반환함(char*), 이는 함수가 실행되면서 메모리공간에 임의의 문자배열을 만든다음 그 주소를 strPtr에 넣어주는 것이다.
	// 이는 추가로 inet_ntoa() 실행시 strPtr에 저장된(사실상 가리키던) 기존 값은 사라지고 새로운 값이 들어가게 된다.
	// 따라서 inet_ntoa를 사용한 뒤에는 새로운 문자열배열을 만들어준다음 값을 한번 더 옮겨준다.
	// 그리고 경고때문에 한번에 문자열 배열에 넣어주는 inet_ntop() 함수를 사용하였다.

	WSACleanup();
	return 0;

}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
