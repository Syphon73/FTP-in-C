#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

int main() {
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    char str[100];
    time_t ticks;

    /* Create TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    /* Server address */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(10000);

    /* Bind and listen */
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);

    while (1) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

        ticks = time(NULL);

	FILE *fptr;
    	fptr = fopen("file.txt", "r");
    	char str[299];
    	if (fptr == NULL) {
        	printf("Error opening file!");
        	return 1;
    	}

    	while (fgets(str, sizeof(str), fptr) != NULL) {
        	printf("%s", str); // Print the line to the console
		//snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        	write(connfd, str, strlen(str));

    	}

        close(connfd);
    }
}

