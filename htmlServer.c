/*Required Headers*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

/*TCP-like server that listens on port 22000*/
int main() {
    // create buffer string and file descriptors for listen and communicate
    char str[100];
    int listen_fd, comm_fd;

    // create a internet socket address called serveraddr
    struct sockaddr_in serveraddr;

    // set the listen port to internet, TCP, normal
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    // clear the memory where the struct serrveraddr will be stored
    bzero( &serveraddr, sizeof(serveraddr));

    // set the family to Internet, accept all connection requests on port 22000
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    serveraddr.sin_port = htons(22000);

    /*bind the listen information to the internet socket address we made
    and change the sockaddr_in to just a regular sockaddr
    */
    bind(listen_fd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));

    // start listening!! if more then 10 computers try to connect bounce 11th and up
    listen(listen_fd, 10);

    //set comm_fd to read from the listened data
    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

    // clear string memory and read print and resend incoming data
    while(1){
        bzero(str, 100);

        read(comm_fd, str, 100);

        printf("Echoing back - %s", str);

        write(comm_fd, str, strlen(str) + 1);
    }
    return 0;
}
