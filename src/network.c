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
  int id;
  void (*write)(Socket *, char data[]);
  int (*connect)(Socket *self, char address[], int port);
};

void Socket_write(struct Socket *self, char data[]) {
  write(self->id, data, sizeof(data));
}

int Socket_connect(Socket *self, char address[], int port) {
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(address);
  return connect(self->id, (struct sockaddr *)&addr, sizeof(*address));
}

struct Socket newSocket() {
  struct Socket sock;
  sock.id = socket(AF_INET, SOCK_STREAM, 0);
  sock.write = Socket_write;
  sock.connect = Socket_connect;
  return sock;
}