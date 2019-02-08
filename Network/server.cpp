#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <ctime>
#include <stdlib.h>

// ���� �ҽ�����

using namespace std;

int main() {
	
		// ==============================================================================================

		WSADATA wsaData;
		WORD DllVersion = MAKEWORD(2, 1);

		if (WSAStartup(DllVersion, &wsaData) != 0) {
			// ���� ���� �߻��� �޽��� �ڽ� ����� �Բ� exit(1) �Լ��� ���α׷��� �����Ų��.
			MessageBoxA(NULL, "Window socket start is failed.", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}

		SOCKADDR_IN addr, addr1, addr2;
		int addrlen = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ������ IP�ּ� - 127.0.0.1 �� �ǹ̴� localhost �� �ڱ��ڽ��� ����Ų��.
		addr.sin_port = htons(9000); // ��Ʈ ��ȣ 9000 ( ���� - Ŭ���̾�Ʈ ���� ���� )
		addr.sin_family = AF_INET; // IPv4 �̰� ��Ʈ��ũ ������ �� ���Ǳ�� ���� ���� ����. IP �ּ��� ������ 4��° �����̶�� �ǹ�.

		SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		listen(sListen, SOMAXCONN);

		// =================================================================================================
		char conn1[100] = "A";
		char conn2[100] = "B";

		// ù��° Ŭ���̾�Ʈ���� ���� �غ� - ������ ������
		SOCKET newConnection1;
		newConnection1 = accept(sListen, (SOCKADDR*)&addr1, &addrlen);

		// �ι�° Ŭ���̾�Ʈ���� ���� �غ� - ���� ����
		SOCKET newConnection2;
		newConnection2 = accept(sListen, (SOCKADDR*)&addr2, &addrlen);

		while (1) {
		if (newConnection1 == 0) {
			cout << "Ŭ���̾�Ʈ1���� ���� ����\n";
		}
		else send(newConnection1, conn1, sizeof(conn1), NULL);

		if (newConnection2 == 0) {
			cout << "Ŭ���̾�Ʈ2���� ���� ����\n";
		}
		else send(newConnection2, conn2, sizeof(conn2), NULL);

		cout << "Ŭ���̾�Ʈ1, 2 ����\n";
		
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
					cout << "Ŭ���̾�Ʈ 1 ���� �Ҹ�\n";
					shutdown(newConnection1, SD_BOTH);
					shutdown(newConnection2, SD_BOTH);
					closesocket(newConnection1);
					closesocket(newConnection2);
					break;
				}
			}

			// ������ �Լ��� send(���� ��ü, �޽��� �迭 <- ������ �޽����� ��� ���, �迭 ũ��, NULL)
			// �޴� �Լ��� recv(���� ��ü, �޽��� �迭 <- ���� ���, �迭 ũ��, NULL)
		}
		system("pause");
		return 0;
	
}