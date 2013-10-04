#include "common.socket.h"
#include <errno.h>
#include <string.h>

using std::string;

TCPSocket::TCPSocket() : fd(0), backlog(5){
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in* TCPSocket::ip2struct(const int port, const string& ip){
	string service;
	return this->ip2struct(hints, service, ip);
}
struct sockaddr_in* TCPSocket::ip2struct(string& service, const string& ip){
	struct sockaddr_in* addr;
	struct addrinfo *servinfo;

	if(getaddrinfo(ip.c_str(), service.c_str(), NULL, &servinfo))
		return NULL;

	addr = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
	memcpy(addr, servinfo->ai_addr, sizeof(struct sockaddr_in));

	freeaddrinfo(servinfo);

	return addr;
}

int TCPSocket::listen(const int port){
	struct sockaddr_in serv_addr
	memset((char*) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	return this->listen(serv_addr);
}

int TCPSocket::listen(const int port, const std::string& ip){



}

int TCPSocket::listen(struct sockaddr_in & serv_addr){
	if ( bind( this->fd, (struct sockaddr *) &serv_addr, (socklen_t) sizeof(struct sockaddr)) > 0)
		return 1;

	return listen(this->fd, this->backlog);;
}

TCPSocket& TCPSocket::setBacklog(const unsigned int backlog){
	this->backlog = backlog;
	return *this;
}

TCPSocket::~TCPSocket(){
	if(this->fd){
		close(fd);
	}
}
