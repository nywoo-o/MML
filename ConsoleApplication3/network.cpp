#include "network.h"
#include "console.h"

char ending[1] = {};
char buffer[10000] = {};
WSADATA wsaData;
WORD DllVersion;
SOCKADDR_IN addr;
SOCKET Connection1;

network::network()
{
}

network::~network()
{
}

void network::networkConnect() {

}