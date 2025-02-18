#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "utils.c"

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
  int message_size = strlen(message);
  char* message_size_bin = get_binary_value(message_size, 4);
  char* message_value_bin = get_binary_message(message);
  int outgoing_message_size = strlen(message_size_bin) + strlen(message_value_bin);
  char* outgoing_message = (char*)malloc(sizeof(char)*outgoing_message_size);

  if(sprintf(outgoing_message, "%s%s", message_size_bin, message_value_bin) < 0) {
    printf("Failed to format the string ..");
    return 0;
  }

  char* up_message_size = parse_binary_message(message_size_bin, 4);

  printf("This is the unparsed version of the message len: %s\n\n", up_message_size);

  printf("This is the outgoing_message : %s\n", outgoing_message);


  size_t _tmp = send(fd, outgoing_message, strlen(outgoing_message), 0);
  if (_tmp < 0) {
    printf("Failed to send message ..");
  }

  char incoming_message[50];

  size_t _newtmp = recv(fd, incoming_message, sizeof(incoming_message), 0);

  printf("Recieved from the server %s\n", incoming_message);

  return 0;
}
