#include "common.socket_io.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>
#include <unistd.h>
#include <arpa/inet.h>

using std::string;

SocketIO::SocketIO() {}
SocketIO::SocketIO(unsigned int fd) {
	this->fd = fd;
}
SocketIO::~SocketIO(){}

int SocketIO::read(string &msg){
	uint32_t len;

	if(recv(this->fd, (void*) &len, 4, 0) != 4)
		return -1;

	len = ntohl(len);

	char *str = new char[len+1];

	if(((uint32_t) recv(this->fd, (void*) str, len, 0)) != len){
		delete str;
		return -1;
	}

	str[len] = 0;

	msg = str;
	delete str;
	return 0;
}

int SocketIO::write(const string &msg){
	uint32_t len = htonl(msg.length());
	if(send(this->fd, (void*) &len, 4, 0) != 4)
		return -1;

	if((uint32_t) send(this->fd, (void*) msg.c_str(), msg.length(), 0) != msg.length())
		return -1;

	return 0;
}
