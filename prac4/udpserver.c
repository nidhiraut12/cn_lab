
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 10055
#define BUF_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_in server, client;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(client);

    // Create UDP socket
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // Prepare server address
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    bind(server_fd, (struct sockaddr *)&server,
         sizeof(server));

    printf("UDP Echo Server listening on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUF_SIZE);

        // Receive message from client
        int bytes = recvfrom(server_fd, buffer,
                             BUF_SIZE - 1, 0,
                             (struct sockaddr *)&client,
                             &len);

        if (bytes < 0)
            break;

        buffer[bytes] = '\0';
        printf("Received: %s", buffer);

        // Echo message back to client
        sendto(server_fd, buffer, bytes, 0,
               (struct sockaddr *)&client, len);
    }

    close(server_fd);
    return 0;
}
