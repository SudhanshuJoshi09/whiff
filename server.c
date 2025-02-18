#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include "utils.c"

#define SOCK_PORT 9091

int main() {

  int count = 0;

  struct sockaddr_in my_addr;

  // STEP - 01: Setting up file descriptor
  int fd = socket(PF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("Failed to create File Descriptor");
    close(fd);
    return -1;
  }

  // STEP - 02: Setting up socket address.
  // memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  // htons and htonl functions are used to convert to network byte order..
  // Learn about these byte orders.
  my_addr.sin_port = htons(SOCK_PORT);
  my_addr.sin_addr.s_addr= htonl(INADDR_ANY);


  // STEP - 02(b): Set up this option to reuse the same address after restart and not hog the address..
  int val = 1;
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));


  // STEP - 03: Setting up server_fd (this is for creating socket)
  int server_fd = bind(fd, (struct server_fdaddr *) &my_addr, sizeof(my_addr));
  if (server_fd < 0) {
    printf("Failed to connect to socket: %d \n", server_fd);
    close(fd);
    return -1;
  }

  // STEP - 04: Listen to the file descriptor
  if(listen(fd, 2) < 0) {
    perror("Accept failed");
    close(fd);
    close(server_fd);
    return -1;
  }


  // STEP - 05: Accept connections from the socket.
  socklen_t sock_len = sizeof(my_addr);

  while (1) {
    int client_fd = accept(fd, (struct sockaddr *) &my_addr, &sock_len);
    if (client_fd < 0) {
      perror("Accept failed");
      close(fd);
      close(server_fd);
      return -1;
    }

    // STEP 6: Get data from client.
    // size_t _mc = recv(client_fd, incoming_message, sizeof(incoming_message), 0);
    char incoming_message_size[33];
    incoming_message_size[32] = '\0';
    int bytes_read = 0; 
    while(bytes_read != 32) {
      // NOTE: this is considering char takes only 1 byte of space.
      size_t read_count = recv(client_fd, incoming_message_size + bytes_read, 32 - bytes_read, 0);
      bytes_read += read_count;
    }

    int message_size = parse_binary_count(incoming_message_size, 4)*8;
    char* incoming_message = (char*)malloc(message_size + 1);
    incoming_message[message_size] = '\0';
    bytes_read = 0; 
    while(bytes_read != message_size) {
      size_t read_count = recv(client_fd, incoming_message + bytes_read, message_size - bytes_read, 0);
      bytes_read += read_count;
    }

    char* final_message = parse_binary_message(incoming_message, 1);
    printf("This is the message recieved from the client :: %s\n", final_message);


    // STEP 7: Send message to the client.
    char outgoing_message[50];
    int _fs = sprintf(outgoing_message, "You are %d visiter", count);
    send(client_fd, outgoing_message, strlen(outgoing_message), 0);
    // printf("Message sent to server : %s\n", incoming_message);
    printf("Message sent to client : %s\n", outgoing_message);

    close(client_fd);
    count += 1;
  }

  close(fd);
  close(server_fd);
  return 0;
}
