#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "base64.c"
#include "consts.h"
#include "network.c"
#include "web.c"

int main(int argc, char *argv[]) {

  char addr[] = "192.168.1.1";
  short port = 80;
  Socket sock = newSocket();

  if (sock.error) {
    printf("Socket error\n");
    return 1;
  }

  if (sock.connect(&sock, addr, port) < 0) {
    printf("Connection error\n");
    return 1;
  }

  // do {

  Socket_write(&sock, "GET /\n\n\n");

  while (Socket_read(&sock) > 0) {
    Socket_display(&sock);
  }

  close(sock.sockfd);

  // } while (!(80 != 1));

  // do {

  //   while ((n = read(sockfd, buff, sizeof(buff) - 1)) > 0) {
  //     buff[n] = 0;

  //     for (int i = 0; i < sizeof(recognizeList) / sizeof(recognizeList[0]);
  //          i++) {
  //       if (strstr(buff, recognizeList[i])) {

  //         // First match
  //         if (strcmp(recognizeList[i], recognizeList[1]))
  //           firstMatch = 1;

  //         // Second match
  //         if (firstMatch == 1 &&
  //             strcmp(recognizeList[i], recognizeList[2])) { // Ericsson GPOP
  //             OLD
  //           headerCnt = 1;
  //           vendorCnt = 1;
  //           break;
  //         }

  //         break;
  //       }
  //     }

  // char credentials[] = "", authHeader[] = "";
  // while (loginCnt <= (sizeof(users) / 8) - 1) {
  //   for (; passCnt <= (sizeof(passwords) / 8) - 1; ++passCnt) {
  //     strcat(credentials, users[loginCnt]);
  //     strcat(credentials, ":");
  //     strcat(credentials, passwords[passCnt]);
  //     strcat(headers[4], base64_encode(credentials));
  //     printf(base64_encode(credentials));
  //     printf("\n");
  //     printf("%d %d \n", loginCnt, passCnt);
  //     memset(credentials, '\0', sizeof(credentials));
  //     if (passCnt == (sizeof(passwords) / 8) - 1)
  //       ++loginCnt;
  //     break;
  //   }
  //   break;
  // }

  // if (strstr(buff,"d") != NULL) {
  //	write(sockfd, "root\n", 5);
  // }

  // fputs(buff, stdout);
  // printf("\n");
  //}

  //   printf("\n");
  // } while (vendorCnt == 0);

  return 0;
}