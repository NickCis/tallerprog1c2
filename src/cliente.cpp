#include <iostream>
#include "cliente.socket_connect.h"

using std::string;
using std::cout;
using std::endl;

int main(){
	TCPSocketConnect sock;
	string str;

	str = "127.0.0.1";
	if(sock.connect(40000, str)){
		cout << "Error connectandose" << endl;
		return 1;
	}


	str = "hola";
	if(sock.write(str)){
		cout << "Error escribiendo" << endl;
	}

	return 0;
}
