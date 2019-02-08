#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <ctime>
#include <stdlib.h>

// 서버 소스파일

using namespace std;

int main() {
	
		// ==============================================================================================

		WSADATA wsaData;
		WORD DllVersion = MAKEWORD(2, 1);

		if (WSAStartup(DllVersion, &wsaData) != 0) {
			// 연결 에러 발생시 메시지 박스 실행과 함께 exit(1) 함수가 프로그램을 종료시킨다.
			MessageBoxA(NULL, "Window socket start is failed.", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}

		SOCKADDR_IN addr, addr1, addr2;
		int addrlen = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 서버의 IP주소 - 127.0.0.1 의 의미는 localhost 즉 자기자신을 가리킨다.
		addr.sin_port = htons(9000); // 포트 번호 9000 ( 서버 - 클라이언트 통일 사항 )
		addr.sin_family = AF_INET; // IPv4 이건 네트워크 연결할 때 주의깊게 보면 관찰 가능. IP 주소의 버전이 4번째 버전이라는 의미.

		SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		listen(sListen, SOMAXCONN);

		// =================================================================================================
		char conn1[100] = "A";
		char conn2[100] = "B";

		// 첫번째 클라이언트와의 연결 준비 - 소켓을 생성함
		SOCKET newConnection1;
		newConnection1 = accept(sListen, (SOCKADDR*)&addr1, &addrlen);

		// 두번째 클라이언트와의 연결 준비 - 소켓 생성
		SOCKET newConnection2;
		newConnection2 = accept(sListen, (SOCKADDR*)&addr2, &addrlen);

		while (1) {
		if (newConnection1 == 0) {
			cout << "클라이언트1와의 연결 실패\n";
		}
		else send(newConnection1, conn1, sizeof(conn1), NULL);

		if (newConnection2 == 0) {
			cout << "클라이언트2와의 연결 실패\n";
		}
		else send(newConnection2, conn2, sizeof(conn2), NULL);

		cout << "클라이언트1, 2 연결\n";
		
		clock_t starttime = clock(), checkt = clock(), createtime = rand()%10+5;

			while (1) {
				char buffer_1[10000];
				char buffer_2[10000];

				while (recv(newConnection1, buffer_1, sizeof(buffer_1), NULL)) {
					send(newConnection2, buffer_1, sizeof(buffer_1), NULL);
					cout << buffer_1[0] << ' ';
					if (buffer_1[0] == '!')
					{ cout << "EOF\n"; break; }
					else if (buffer_1[0] == '`' || buffer_1[0] == '~') 
					{ cout << "-fin-\n"; break; }
				}

				if (buffer_1[0] == '`' || buffer_1[0] == '~' ||
					buffer_2[0] == '`' || buffer_2[0] == '~')
				{
					cout << "-finfin-\n"; break;
				}

				while (recv(newConnection2, buffer_2, sizeof(buffer_2), NULL)) {
					send(newConnection1, buffer_2, sizeof(buffer_2), NULL);
					cout << buffer_2[0] << ' ';
					if (buffer_2[0] == '!') 
					{ cout << "EOF\n"; break; }
					else if (buffer_2[0] == '`' || buffer_2[0] == '~') 
					{ cout << "round-fin-\n"; break; }
				}

				if (buffer_1[0] == '`' || buffer_1[0] == '~' ||
					buffer_2[0] == '`' || buffer_2[0] == '~')
				{
					cout << "-finfin-\n"; break;
				}
				if (newConnection1 == 0 || newConnection2 == 0) {
					cout << "클라이언트 1 연결 소멸\n";
					shutdown(newConnection1, SD_BOTH);
					shutdown(newConnection2, SD_BOTH);
					closesocket(newConnection1);
					closesocket(newConnection2);
					break;
				}
			}

			// 보내는 함수는 send(소켓 객체, 메시지 배열 <- 보내는 메시지가 담긴 장소, 배열 크기, NULL)
			// 받는 함수는 recv(소켓 객체, 메시지 배열 <- 저장 장소, 배열 크기, NULL)
		}
		system("pause");
		return 0;
	
}