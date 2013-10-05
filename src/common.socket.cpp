#include "common.socket.h"
#include <sstream>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

using std::string;
using std::stringstream;
using std::size_t;

Socket::Socket() : fd(0){}
Socket::~Socket(){
	if(this->fd){
		close(fd);
	}
}

int Socket::shutdown(){
	return this->shutdown(SHUT_RDWR);
}

int Socket::shutdown(int how){
	return ::shutdown(this->fd, how);
}

struct sockaddr_in* Socket::ip2struct(const string& ipport){
	string ip, service;
	size_t found = ipport.find(':');
	if(found != std::string::npos){
		ip = ipport.substr(0, found);
		service = ipport.substr(found+1, ipport.length()-found);
		return this->ip2struct(service, ip);
	}
	return NULL;
}

struct sockaddr_in* Socket::ip2struct(const int port, const string& ip){
	string service;
	stringstream ss;
	ss << port;
	service = ss.str();
	return this->ip2struct(service, ip);
}
struct sockaddr_in* Socket::ip2struct(const string& service, const string& ip){
	struct sockaddr_in* addr;
	struct addrinfo *servinfo;

	if(getaddrinfo(ip.c_str(), service.c_str(), NULL, &servinfo))
		return NULL;

	addr = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
	memcpy(addr, servinfo->ai_addr, sizeof(struct sockaddr_in));

	freeaddrinfo(servinfo);

	return addr;
}

TCPSocket::TCPSocket(){
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
}

TCPSocket::~TCPSocket(){}
