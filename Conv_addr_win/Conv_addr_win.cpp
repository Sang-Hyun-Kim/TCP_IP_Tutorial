// WinSock2의 WSAStringTOAddress 와 WSAAddressTOString  사용해보기

#undef UNICODE
#undef _UNICODE
#include <stdio.h>
#include <WinSock2.h>


void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	//
	//const char* strAddr = "203.211.218.102:9190";
	//
	//char strAddrBuf[50];
	//SOCKADDR_IN servAddr;
	//int size;

	//WSAData wsaData;
	//
	//if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	//	ErrorHandling("WSAStartup() error!");

	//size = sizeof(servAddr);
	//WSAStringToAddress(
	//	strAddr, AF_INET, NULL, (SOCKADDR*)&servAddr, &size
	//);
	//
	//size = sizeof(strAddrBuf);
	//
	//WSAAddressToString(
	//	(SOCKADDR*)&servAddr, sizeof(servAddr), NULL, strAddrBuf, &size
	//);

	//printf("Second conv result: %s \n", strAddrBuf);
	//WSACleanup();
	//return 0;

}
	//WSAStringToAddress()
	//LPWSTR             AddressString,					IP와 PORT 번호를 담고있ㄱ는 문자열 주소 값 전달
	//INT                AddressFamily,					첫 번째 인자를 전달된 주소정보가 속하는 주소체계 정보 전달.
	//LPWSAPROTOCOL_INFOW lpProtocolInfo,				프로토콜 프로바이더 설정, 일반적으로 NULL 전달
	//LPSOCKADDR lpAddress,								주소정보를 담을 구조체 변수의 주소값 전달
	//LPINT lpAddressLength								네 번째 인자로 전달된 주소 값의 변수 크기를 담고 있는 변수의 주소값 전달
	//WSAAddressToString()
	//	LPSOCKADDR lpsaAddress,							문자열로 변환할 주소 정보를 지니는 구조체 변수의 주소 값 전달
	//	DWORD               dwAddressLength,			첫 번째 인자로 전달된 구조체 변수의 크기 전달
	//	LPWSAPROTOCOL_INFOW lpProtocolInfo,				프로토콜 프로바이더 설정, 일반적으로 NULL 전달
	//	LPWSTR lpszAddressString,						문자열로 변환된 결과를 저장할 배열의 주소 값 전달
	//	LPDWORD             lpdwAddressStringLength		네 번째 인자로 전달된 주소 값의 배열 크기를 담고 있는 변수의 주소 값 전달
	//	)
void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}