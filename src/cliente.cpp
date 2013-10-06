#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "cliente.socket_connect.h"

using std::string;
using std::stringstream;
using std::istream;
using std::ifstream;
using std::cout;
using std::cin;
using std::getline;
using std::endl;

int read_file(const char* path, string &str);
void read_cin(string &str);
int get_port(const string &ipport, string &port);

int main(int argc, char*argv[]){
	if(argc < 2)
		return 1;

	TCPSocketConnect sock;
	string ip_port = argv[1];
	string port;
	string data_length;
	if(get_port(ip_port, port))
		return 1;

	if(sock.connect(ip_port))
		return 1;

	string msj;
	if(sock.read(msj))
		return 2;

	if(msj.compare("PUERTO "+port+" Aceptado. Recibiendo datos..."))
		return 2;

	cout << "[SERVIDOR] " << msj << endl;

	if(argc == 3){
		if(read_file(argv[2], msj)){
			return 3;
		}
	}else{
		read_cin(msj);
	}

	{
		stringstream ss;
		ss << msj.length();
		data_length = ss.str();
	}

	cout << "[CLIENTE] Enviando datos..." << endl;

	if(sock.write(msj))
		return 3;

	if(sock.read(msj))
		return 3;

	if(msj.compare(
			"Datos recibidos exitosamente. Cantidad de bytes recibidos: "+
			data_length+"."))
		return 2;

	cout << "[SERVIDOR] " << msj << endl;

	return 0;
}

void read_all(istream& in, string &str){
	stringstream ss;

	char c = in.get();
	while(in.good()){
		ss << c;
		c = in.get();
	}

	str = ss.str();
}

int read_file(const char* path, string &str){
	ifstream ifs(path);
	if(!ifs.is_open())
		return -1;

	read_all(ifs, str);

	ifs.close();

	return 0;
}

void read_cin(string &str){
	read_all(cin, str);
}

int get_port(const string &ipport, string &port){
	size_t found = ipport.find(':');
	if(found != std::string::npos){
		port = ipport.substr(found+1, ipport.length()-found);
		return 0;
	}

	return -1;
}
