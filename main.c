#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define SOCK_PORT 9090

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
  my_addr.sin_port = htons(SOCK_PORT);
  my_addr.sin_addr.s_addr= htonl(INADDR_ANY);

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

    // STEP 6: Send data to the client
    char *message = "Hello from the server!\n";
    send(client_fd, message, strlen(message), 0);
    printf("Message sent to client.\n");
    close(client_fd);
  }

  close(fd);
  close(server_fd);
  return 0;
}
