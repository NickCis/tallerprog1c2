#include <iostream>
#include <fstream>
#include <sstream>
#include "cliente.socket_connect.h"

using std::string;
using std::stringstream;
using std::ifstream;
using std::cout;
using std::endl;

int read_file(const char* path, string &str);

int main(int argc, char*argv[]){
	if(argc < 2)
		return 1;

	TCPSocketConnect sock;
	string ip_port = argv[1];

	if(sock.connect(ip_port)){
		cout << "Error connectandose" << endl;
		return 1;
	}

	string msj;
	if(sock.read(msj)){
		cout << "Error leyendo " << endl;
		return 2;
	}

	cout << msj << endl;

	if(argc == 3){
		if(read_file(argv[2], msj)){
			cout << "Error abriendo archivo" << endl;
			return 1;
		}
	}else{
		msj = "pepe";
	}

	if(sock.write(msj)){
		cout << "Error escribiendo" << endl;
	}

	if(sock.read(msj)){
		cout << "Error leyendo " << endl;
		return 2;
	}

	cout << msj << endl;

	return 0;
}

int read_file(const char* path, string &str){
	ifstream ifs(path);
	if(!ifs.is_open())
		return -1;

	stringstream ss;

	char c;
	do {
		c = ifs.get();
		ss << c;
	} while(ifs.good());

	str = ss.str();

	ifs.close();

	return 0;
}

