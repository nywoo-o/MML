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
		//ntw.networkConnect();//네트워크 연결
		DllVersion = MAKEWORD(2, 1);

		if (WSAStartup(DllVersion, &wsaData) != 0) {
			// 연결 에러 발생시 메시지 박스 실행과 함께 exit(1) 함수가 프로그램을 종료시킨다.
			MessageBoxA(NULL, "Window socket start is failed.", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}


		int addrlen = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //서버의 IP주소 - 127.0.0.1 의 의미는 localhost 즉 자기자신을 가리킨다.
		addr.sin_port = htons(9000); //포트 번호 9000 ( 서버 - 클라이언트 통일 사항 )
		addr.sin_family = AF_INET; //IPv4 이건 네트워크 연결할 때 주의깊게 보면 관찰 가능. IP 주소의 버전이 4번째 버전이라는 의미.

		Connection1 = socket(AF_INET, SOCK_STREAM, NULL);// 소켓 객체 생성
		if (connect(Connection1, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
			// connect 함수는 생성된 소켓 객체에 주소 정보 (addr)를 등록하고 연결을 시도하는 함수이다.
			// connect 함수는 연결을 생성하고 유지하는 함수이며 이 과정이 성공하면 1을 리턴하고, 실패하면 0을 리턴한다.
			// 그러므로 0을 리턴하면 에러메시지를 띄우고 프로그램이 종료됨
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
			buf.sound(); //sound 시작
			system("mode con:cols=160 lines=40"); //콘솔 크기 조절

			buf.readymonitor(); //시작인터페이스 출력
			buf.Rulemonitor(); Sleep(150);
			buf.main_menu();
			int sy, sx, scolor;
			char smych;

			//map을 콘솔에 출력
			for (int i = 0; i < 35; i++) {
				cout << map[i] << endl;
			}
			recv(Connection1, buffer, sizeof(buffer), NULL);//클라이언트 몇인지 확인

			if (buffer[0] == 'A') {
				//기본 세팅
				mych = turn_interface = 'A';
				start.first = 1; start.second = 1; y = 1; x = 1;
				sy = 1; sx = 1; smych = 'A'; scolor = buf.getcolor();
				//버그난 거 야매로 때우기

				statrtime = checktime = clock(); //starttime과 checktime은 5초이상 움직이는지 확인하는 변수
				while (1) { //본격적인 시작
					if (allfin == true) break;
					y = sy; x = sx;
					mych = smych;
					buf.setcolor(scolor);

					while (gamerunning) {
						buf.infomonitor(); //목숨과 캐릭터 등 출력 모니터
						
						//서버에 맵보내기
						if (buffer[0] != '!') {
							//newmap을 일자로 이어붙여서 보낸다.
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

						//NEW랑 PREV의 화면 비교 후 변경
						buf.comparAndChange('+');
						//만약 자기차례 끝나면 ! 보내고 게임대기
						if (ending[0] == '!') {
							send(Connection1, ending, sizeof(ending), NULL);
							ending[0] = ' ';
							turn_interface = 'B';
							gamerunning = false;
							break;
						}

						CC.failOrWin();//fail또는win 컨디션체크
						if (allfin == true) break;

						system("pause > nul");
						post.first = y; post.second = x;

						checktime = clock();
						
						Console.GetTheKEY(); //키입력
						if (GetAsyncKeyState(VK_TAB)) buf.QuitOrContinue('+'); //메뉴창

						//꺾이는 부분 벡터에 저장(최대 최소값을 찾기 위해)
						CC.saveVec();
						//stack에 모든 루트 저장(루트 초기화하기 위해)
						s.push(make_pair(post.first, post.second));
						//벽에 도달한 경우 벡터 및 다른 값들 초기화
						CC.IFArriveFinish();

						checktime = clock();
						//4번이상 꺾으면 OR TIMEOVER 초기화
						CC.TimeoverAndEdgeover();
					
						
					}

					sy = y; sx = x;
					smych = mych;
					scolor = buf.getcolor();

					if (allfin == true) break;
					buf.infomonitor();
					//받자받자 애가 움직이는 걸 받자
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
							Console.gotoxy(15, 50); cout << "상대방이 게임을 끝냈습니다." << endl;
							Console.gotoxy(16, 50); cout << "게임을 끝냅니다." << endl; exit(1);
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
					//자기 캐릭터 확인창 출력
					//x랑 y랑 mych가 초기화되길래 임시 저장
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
							Console.gotoxy(15, 50); cout << "상대방이 게임을 끝냈습니다." << endl;
							Console.gotoxy(16, 50); cout << "게임을 끝냅니다." << endl; exit(1);
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
					//임시확인을 위해
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
						//NEW랑 PRV의 화면 비교 후 변경
						buf.comparAndChange('#');
						CC.failOrWin();
						if (allfin == true) break;

						//만약 자기차례 끝나면 ! 보내고 게임대기
						if (ending[0] == '!') {
							send(Connection1, ending, sizeof(ending), NULL);
							ending[0] = ' ';
							gamerunning = true;
							turn_interface = 'A'; break;
						}
						system("pause > nul");
						post.first = y; post.second = x;

						checktime = clock();
						
						Console.GetTheKEY(); //키입력
						if (GetAsyncKeyState(VK_TAB)) buf.QuitOrContinue('#');

						//꺾이는 부분 벡터에 저장(for 최대 최소값)
						CC.saveVec();
						//stack에 모든 루트 저장(for 루트 초기화)
						s.push(make_pair(post.first, post.second));
						//벽에 도달한 경우 벡터 및 다른 값들 초기화
						CC.IFArriveFinish();
						//타임 체크
						checktime = clock();
						//4번이상 꺾으면 OR TIMEOVER 초기화
						CC.TimeoverAndEdgeover();
						
					}
				}
			}
		}
		system("pause");
		return 0;
	
}