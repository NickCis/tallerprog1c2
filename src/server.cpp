#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

#include "server.thread_listen.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]){
	ThreadListen thread(40000);

	thread.start();

	thread.join();

	return 0;
}
