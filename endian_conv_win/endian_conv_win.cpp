
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	WSAData wsaData;
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr = 0x12345678;
	unsigned long net_addr;


	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	printf("Host ordered port: %#x \n",host_port);
	printf("Network ordered port: %#x \n", net_port);
	printf("Host ordered address: %#x \n", host_addr);
	printf("Network ordered address: %#x \n", net_addr);

	WSACleanup();
	return 0;

}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

// 바이트 순서는 CPU의 저장하는 방식에 따라 리틀 엔디안과 빅 엔디안 시스템으로 나뉜다.
// 이때 네트워크 바이트 순서의 약손은 빅 엔디안 시스템으로 통일하자 였고
// Intel과 AMD CPU는 리틀 엔디안 방식으로 저장하기 때문에
// 변환해주는 과정이 필수다.
// 이때 사용되는 함수가 short 사이즈와 long 사이즈에 따라 htons 과 htonl 로 나뉜다.
// 리틀 엔디안: 상위 바이트의 값을 큰 번지수에 저장하는 방식
// 빅 엔디안: 상위 바이트의 값을 작은 번지수에 저장하는 방식