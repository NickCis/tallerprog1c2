#include "server.thread_listen.h"

#include <iostream>

using std::string;
using std::cout;
using std::endl;

ThreadListen::ThreadListen(int port) : port(port){}
ThreadListen::~ThreadListen(){}

void* ThreadListen::run(){
	SocketIO* fd;

	if(this->sock.listen(this->port)){
		cout << "Error en listen" << endl;
		return NULL;
	}

	while( (fd = this->sock.accept())){
		string msg;
		if(!fd->read(msg)){
			cout << "Nuevo msje '" << msg << "'" << endl;
		}

		delete fd;
	}

	return NULL;
}

