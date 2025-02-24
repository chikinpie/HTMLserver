/* srv.c */
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8181
#define QUEUE 5

int main() {
    int serverfd, clientfd;
    socklen_t addrlen;
    struct sockaddr_in srv, cli;
    char buf[512];
    char *data;

    addrlen = 0;
    memset(&srv, 0, sizeof(srv));
    memset(&cli, 0, sizeof(cli));
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0) {
        printf("socket()\n");
        return -1;
    }

    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = 0;
    srv.sin_port = htons(PORT); 

    if (bind(serverfd, (struct sockaddr *)&srv, sizeof(srv)) != 0) {
        printf("bind()\n");
        close(serverfd);
        return -1;
    }

    if (listen(serverfd, QUEUE) != 0) {
        printf("listen()\n");
        close(serverfd);
        return -1;
    }

    printf("Listening on 0.0.0.0:%d\n", PORT);

    clientfd = accept(serverfd, (struct sockaddr *)&srv, &addrlen);
    if (clientfd < 0) {
        printf("accept()\n");
        close(serverfd);
        return -1;
    }

    printf("Client connected\n");

    read(clientfd, buf, 511);
    data = "http v1.0\n";
    write(clientfd, data, strlen(data));

    close(clientfd);
    close(serverfd);
    
    return 0;
}   
