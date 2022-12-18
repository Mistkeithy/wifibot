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

typedef struct Socket Socket;
struct Socket {
  short sockfd;
  short cursor;
  short error;
  char buff[4096];
  struct sockaddr_in osockaddr;
  void (*write)(Socket *, char data[]);
  void (*send)(Socket *);
  short (*read)(Socket *);
  void (*display)(Socket *);
  short (*connect)(Socket *this, char address[], int port);
};

void Socket_write(struct Socket *this, char data[]) {
  write(this->sockfd, data, sizeof(data));
}

short Socket_read(struct Socket *this) {
  this->buff[this->cursor] = 0;
  return this->cursor = read(this->sockfd, this->buff, sizeof(this->buff) - 1);
}

void Socket_display(struct Socket *this) {
  fputs(this->buff, stdout);
  printf("\n");
}

short Socket_connect(struct Socket *this, char address[], int port) {
  this->osockaddr.sin_family = AF_INET;
  this->osockaddr.sin_port = htons(port);
  this->osockaddr.sin_addr.s_addr = inet_addr(address);
  return connect(this->sockfd, (struct sockaddr *)&this->osockaddr,
                 sizeof(this->osockaddr));
}

struct Socket newSocket() {
  struct Socket sock;
  if ((sock.sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    sock.error = 1;
  sock.cursor = 0;
  memset(sock.buff, '\0', sizeof(sock.buff));
  sock.write = Socket_write;
  sock.connect = Socket_connect;
  return sock;
}