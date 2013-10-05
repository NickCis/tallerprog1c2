#ifndef __SERVER_THREAD_LISTEN_H__
#define __SERVER_THREAD_LISTEN_H__

#include "common.thread.h"
#include "server.socket_listener.h"

class ThreadListen : public Thread {
	protected:
		TCPSocketListener sock;
		int port;
		virtual void* run();

	public:
		ThreadListen(int port);
		~ThreadListen();
};
#endif
