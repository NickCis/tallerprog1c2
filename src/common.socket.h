#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

#include <string>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>

class TCPSocket {
	protected:
		unsigned int fd;
		unsigned int backlog;
		struct sockaddr_in* ip2struct(const int port, const std::string& ip);
		struct sockaddr_in* ip2struct(const std::string& service, const std::string& ip);

	public:
		TCPSocket();
		~TCPSocket();

		int listen(const int port);
		int listen(const int port, const std::string& ip);
		int listen(struct sockaddr_in & serv_addr);

		TCPSocket& setBacklog(const unsigned int backlog);

};

#endif
