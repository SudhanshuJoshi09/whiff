#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define SOCK_PORT 9091

int main() {

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr = {};

  addr.sin_family = AF_INET;
  addr.sin_port = htons(SOCK_PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  socklen_t sock_len = sizeof(addr);


  if(fd < 0) {
    printf("Failed to create file descriptor");
    return 0;
  }

  int conn = connect(fd, (struct sockaddr*) &addr, sizeof(addr));
  if(conn < 0) {
    printf("Failed to connnect to the socket..");
    return 0;
  }
  char *message = "Hello world\n\n";
  size_t _tmp = send(conn, message, strlen(message), 0);
  if (_tmp < 0) {
    printf("Failed to send message ..");
  }
  return 0;
}
