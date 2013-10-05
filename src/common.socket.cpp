#include "common.socket.h"
#include <sstream>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>

using std::string;
using std::stringstream;

Socket::Socket() : fd(0){}
Socket::~Socket(){
	if(this->fd){
		close(fd);
	}
}

TCPSocket::TCPSocket(){
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
}

//TCPSocket::TCPSocket(int fd) : fd(fd){}
TCPSocket::~TCPSocket(){}

struct sockaddr_in* TCPSocket::ip2struct(const int port, const string& ip){
	string service;
	stringstream ss;
	ss << port;
	service = ss.str();
	return this->ip2struct(service, ip);
}
struct sockaddr_in* TCPSocket::ip2struct(const string& service, const string& ip){
	struct sockaddr_in* addr;
	struct addrinfo *servinfo;

	if(getaddrinfo(ip.c_str(), service.c_str(), NULL, &servinfo))
		return NULL;

	addr = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
	memcpy(addr, servinfo->ai_addr, sizeof(struct sockaddr_in));

	freeaddrinfo(servinfo);

	return addr;
}
