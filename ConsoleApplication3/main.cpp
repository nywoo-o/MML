//____define the entry point____//
#include "network.h"
#include "console.h"
#include <thread>

class console Console;
class BUFFERING buf;
class CheckCondition CC;
class item Item;
class network ntw;
bool gamerunning = true;
int soundchoice = 1;

int main() {
		////////////////////////////////////////////////////////////
		//ntw.networkConnect();//��Ʈ��ũ ����
		DllVersion = MAKEWORD(2, 1);

		if (WSAStartup(DllVersion, &wsaData) != 0) {
			// ���� ���� �߻��� �޽��� �ڽ� ����� �Բ� exit(1) �Լ��� ���α׷��� �����Ų��.
			MessageBoxA(NULL, "Window socket start is failed.", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}


		int addrlen = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //������ IP�ּ� - 127.0.0.1 �� �ǹ̴� localhost �� �ڱ��ڽ��� ����Ų��.
		addr.sin_port = htons(9000); //��Ʈ ��ȣ 9000 ( ���� - Ŭ���̾�Ʈ ���� ���� )
		addr.sin_family = AF_INET; //IPv4 �̰� ��Ʈ��ũ ������ �� ���Ǳ�� ���� ���� ����. IP �ּ��� ������ 4��° �����̶�� �ǹ�.

		Connection1 = socket(AF_INET, SOCK_STREAM, NULL);// ���� ��ü ����
		if (connect(Connection1, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
			// connect �Լ��� ������ ���� ��ü�� �ּ� ���� (addr)�� ����ϰ� ������ �õ��ϴ� �Լ��̴�.
			// connect �Լ��� ������ �����ϰ� �����ϴ� �Լ��̸� �� ������ �����ϸ� 1�� �����ϰ�, �����ϸ� 0�� �����Ѵ�.
			// �׷��Ƿ� 0�� �����ϸ� �����޽����� ���� ���α׷��� �����
			MessageBoxA(NULL, "Connect is failed.", "Error", MB_OK | MB_ICONERROR);
			return 0;
		}

		while (1) {
			allfin = 0; life = 15;
			ending[0] = ' ';
			for (int i = 0; i < 35; i++) {
				for (int j = 0; j < 119; j++) {
					map[i][j] = newmap[i][j] = defaultmap[i][j];
				}
			}
			buf.sound(); //sound ����
			system("mode con:cols=160 lines=40"); //�ܼ� ũ�� ����

			buf.readymonitor(); //�����������̽� ���
			buf.Rulemonitor(); Sleep(150);
			buf.main_menu();
			int sy, sx, scolor;
			char smych;

			//map�� �ֿܼ� ���
			for (int i = 0; i < 35; i++) {
				cout << map[i] << endl;
			}
			recv(Connection1, buffer, sizeof(buffer), NULL);//Ŭ���̾�Ʈ ������ Ȯ��

			if (buffer[0] == 'A') {
				//�⺻ ����
				mych = turn_interface = 'A';
				start.first = 1; start.second = 1; y = 1; x = 1;
				sy = 1; sx = 1; smych = 'A'; scolor = buf.getcolor();
				//���׳� �� �߸ŷ� �����

				statrtime = checktime = clock(); //starttime�� checktime�� 5���̻� �����̴��� Ȯ���ϴ� ����
				while (1) { //�������� ����
					if (allfin == true) break;
					y = sy; x = sx;
					mych = smych;
					buf.setcolor(scolor);

					while (gamerunning) {
						buf.infomonitor(); //����� ĳ���� �� ��� �����
						
						//������ �ʺ�����
						if (buffer[0] != '!') {
							//newmap�� ���ڷ� �̾�ٿ��� ������.
							int idx = 0; mapcounting = 0;
							for (int i = 0; idx < 35; i++) {
								if (i != 0 && i % 119 == 0) {
									idx++;
									if (idx > 34) break;
								}
								buffer[i] = newmap[idx][i % 119];
								if (newmap[idx][i % 119] == '+') mapcounting++;
							}
							send(Connection1, buffer, sizeof(buffer), NULL);
						} 

						//NEW�� PREV�� ȭ�� �� �� ����
						buf.comparAndChange('+');
						//���� �ڱ����� ������ ! ������ ���Ӵ��
						if (ending[0] == '!') {
							send(Connection1, ending, sizeof(ending), NULL);
							ending[0] = ' ';
							turn_interface = 'B';
							gamerunning = false;
							break;
						}

						CC.failOrWin();//fail�Ǵ�win �����üũ
						if (allfin == true) break;

						system("pause > nul");
						post.first = y; post.second = x;

						checktime = clock();
						
						Console.GetTheKEY(); //Ű�Է�
						if (GetAsyncKeyState(VK_TAB)) buf.QuitOrContinue('+'); //�޴�â

						//���̴� �κ� ���Ϳ� ����(�ִ� �ּҰ��� ã�� ����)
						CC.saveVec();
						//stack�� ��� ��Ʈ ����(��Ʈ �ʱ�ȭ�ϱ� ����)
						s.push(make_pair(post.first, post.second));
						//���� ������ ��� ���� �� �ٸ� ���� �ʱ�ȭ
						CC.IFArriveFinish();

						checktime = clock();
						//4���̻� ������ OR TIMEOVER �ʱ�ȭ
						CC.TimeoverAndEdgeover();
					
						
					}

					sy = y; sx = x;
					smych = mych;
					scolor = buf.getcolor();

					if (allfin == true) break;
					buf.infomonitor();
					//���ڹ��� �ְ� �����̴� �� ����
					while (!gamerunning) {
						int idx = 0;

						recv(Connection1, buffer, sizeof(buffer), NULL);
						if (buffer[0] == '!') {
							gamerunning = true;
							buffer[0] = '*';
							turn_interface = 'A'; break;
						}
						else if (buffer[0] == '?') {
							buf.clear();
							Console.gotoxy(15, 50); cout << "������ ������ ���½��ϴ�." << endl;
							Console.gotoxy(16, 50); cout << "������ �����ϴ�." << endl; exit(1);
						}
						else if (buffer[0] == '~' || buffer[0] == '`') {
							CC.failOrWin();
							if (allfin == true) break;
						}
				
						for (int i = 0; i < sizeof(buffer); i++) {
							if (i != 0 && i % 119 == 0) idx++;
							newmap[idx][i % 119] = buffer[i];
						}
						buf.comparAndChange('+');
					}

				}

			}

			else if (buffer[0] == 'B') {

				turn_interface = 'A';
				mych = 'B';
				start.first = 1; start.second = 117;
				y = 1; x = 117;

				
				statrtime = clock(); checktime = clock();
				while (1) {
					if (allfin == true) break;
					//�ڱ� ĳ���� Ȯ��â ���
					//x�� y�� mych�� �ʱ�ȭ�Ǳ淡 �ӽ� ����
					sy = y; sx = x;
					smych = mych;
					scolor = buf.getcolor();
					buf.infomonitor();

					Console.gotoxy(38, 0); cout << scolor << ' ' << buf.getcolor();
					while (gamerunning) {
						int idx = 0;

						recv(Connection1, buffer, sizeof(buffer), NULL);

						if (buffer[0] == '`' || buffer[0] == '~' || buffer[0] == '!' || buffer[0] == '?')
						{
							Console.gotoxy(37, 0); 
							cout << buffer[0];
						
						}
						if (buffer[0] == '!') {
							gamerunning = false;
							buffer[0] = '*';
							turn_interface = 'B'; break;
						}
						else if (buffer[0] == '?') {
							buf.clear();
							Console.gotoxy(15, 50); cout << "������ ������ ���½��ϴ�." << endl;
							Console.gotoxy(16, 50); cout << "������ �����ϴ�." << endl; exit(1);
						}
						else if (buffer[0] == '~' || buffer[0] == '`') {
							CC.failOrWin();
							if (allfin == true) break;
						}
					
						for (int i = 0; i < sizeof(buffer); i++) {
							if (i != 0 && i % 119 == 0) idx++;
							newmap[idx][i % 119] = buffer[i];
						}

						buf.comparAndChange('#');
					}
					//�ӽ�Ȯ���� ����
					y = sy; x = sx;
					mych = smych;
					buf.setcolor(scolor);
					if (allfin == true) break;

					while (!gamerunning) {
						Console.gotoxy(38, 0); cout << scolor << ' ' << buf.getcolor();
						buf.infomonitor();
						
						if (buffer[0] != '!') {
							int idx = 0; mapcounting = 0;
							for (int i = 0; idx < 35; i++) {
								if (i != 0 && i % 119 == 0) {
									idx++;
									if (idx > 34) break;
								}
								buffer[i] = newmap[idx][i % 119];
								if (newmap[idx][i % 119] == '#') mapcounting++;
							}
							send(Connection1, buffer, sizeof(buffer), NULL);
						}
						//NEW�� PRV�� ȭ�� �� �� ����
						buf.comparAndChange('#');
						CC.failOrWin();
						if (allfin == true) break;

						//���� �ڱ����� ������ ! ������ ���Ӵ��
						if (ending[0] == '!') {
							send(Connection1, ending, sizeof(ending), NULL);
							ending[0] = ' ';
							gamerunning = true;
							turn_interface = 'A'; break;
						}
						system("pause > nul");
						post.first = y; post.second = x;

						checktime = clock();
						
						Console.GetTheKEY(); //Ű�Է�
						if (GetAsyncKeyState(VK_TAB)) buf.QuitOrContinue('#');

						//���̴� �κ� ���Ϳ� ����(for �ִ� �ּҰ�)
						CC.saveVec();
						//stack�� ��� ��Ʈ ����(for ��Ʈ �ʱ�ȭ)
						s.push(make_pair(post.first, post.second));
						//���� ������ ��� ���� �� �ٸ� ���� �ʱ�ȭ
						CC.IFArriveFinish();
						//Ÿ�� üũ
						checktime = clock();
						//4���̻� ������ OR TIMEOVER �ʱ�ȭ
						CC.TimeoverAndEdgeover();
						
					}
				}
			}
		}
		system("pause");
		return 0;
	
}