#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

#include <string>
#include <netdb.h>

class Socket {
	protected:
		unsigned int fd;
	public:
		Socket();
		~Socket();
};

class TCPSocket : public virtual Socket {
	protected:
		struct sockaddr_in* ip2struct(const int port, const std::string& ip);
		struct sockaddr_in* ip2struct(const std::string& service, const std::string& ip);
		//TCPSocket(int fd);

	public:
		TCPSocket();
		~TCPSocket();
};



#endif
