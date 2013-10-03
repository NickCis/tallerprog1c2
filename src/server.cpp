#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>

// Para select
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_SIZE 255

int PORTS[2] = {
	56000,
	56001
};

int main(int argc, char* argv[]){
	unsigned int sockfd[2], newsockfd, clilen, largest_fd=0;
	struct sockaddr_in cli_addr, serv_addr;
	char buff[BUFF_SIZE] = {0};
	size_t read_size =0;

	//Para select
	fd_set rfds;
	struct timeval tv;
	int s_out;

	FD_ZERO(&rfds);

	FD_SET(fileno(stdin), &rfds);

	if(buff[0] && read_size);

	printf("Creo socket\n");
	for(int i=0; i<2;i++){
		if((sockfd[i] = socket(AF_INET, SOCK_STREAM, 0)) < 0){
			perror("creando socket");
			printf("%s\n", strerror(errno));
			exit(1);
		}

		FD_SET(sockfd[i], &rfds);

		if(sockfd[i] >= largest_fd)
			largest_fd = sockfd[i];

		// Seteo puerto
		memset((char*) &serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET; // ipv4
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(PORTS[i]);

		// Bind port
		if ( bind( sockfd[i], (struct sockaddr *) &serv_addr, (socklen_t) sizeof(struct sockaddr)) > 0){
			perror("Bind");
			printf("%s\n", strerror(errno));
			exit(1);
		}

		listen(sockfd[i], 5);
		printf("Escuchando %u...\n", i);
	}


	tv.tv_sec = 400;
	tv.tv_usec = 0;

	while( (s_out = select(largest_fd+1, &rfds, NULL, NULL, &tv)) >0 ){
		tv.tv_sec = 400;
		tv.tv_usec = 0;

		printf("Salio de select %d\n", s_out);
		if(FD_ISSET(fileno(stdin), &rfds)){
			char c = getchar();
			if(c == 'q')
				break;
		}

		clilen = (socklen_t) sizeof(cli_addr);
		for(int i=0; i<2; i++){
			if(FD_ISSET(sockfd[i], &rfds)){
				newsockfd = accept(sockfd[i], (struct sockaddr *) &cli_addr, &clilen);

				printf("newsockfd %d\n", newsockfd);

				//if(newsockfd < 0){
				//	perror("accept");
				//	printf("%s\n", strerror(errno));
				//	exit(1);
				//}

				//read_size = recv(newsockfd, buff, BUFF_SIZE-1, 0);
				//buff[read_size] = 0;
				//printf("Lei %d: '%s'", i, buff);
				//read_size = recv(newsockfd, buff, BUFF_SIZE-1, 0);
				//buff[read_size] = 0;
				//printf("Lei %d: '%s'", i, buff);
				//shutdown(newsockfd, SHUT_RDWR);
				//close(newsockfd);
			}
		}
		printf("vuelvo a esperar\n");
	}

	for(int i=0; i<2; i++){
		shutdown(sockfd[i], SHUT_RDWR);
		close(sockfd[i]);
	}

	return 0;
}
