#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

#include "common.socket.h"
#include "server.socket_listener.h"

#define BUFF_SIZE 255

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]){
	TCPSocketListener sock;
	SocketIO* fd;

	if(sock.listen(40000)){
		cout << "Error en listen" << endl;
		return 1;
	}

	fd = sock.accept();
	if(!fd){
		cout << "Error accept" << endl;
		return 1;
	}
	string msg;
	if(fd->read(msg)){
		cout << "Error read" << endl;
		delete fd;
		return 1;
	}

	cout << msg << endl;
	delete fd;
	return 0;
}
