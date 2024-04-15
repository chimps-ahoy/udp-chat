#include <client.h>
#include <errs.h>
#include <utils.h>

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int client(char *ip, int port)
{
	fprintf(stdout, "connecting to server on %s::%d\n", ip, port);

	int fd = getfd();
	struct sockaddr_in addr = {0};
	initaddr(&addr, ip, port);
	char buff[256] = {0};

	fgets(buff, 256, stdin);
	sendto(fd, buff, 256, 0, (struct sockaddr*)&addr, sizeof(addr));
	fprintf(stdout, "sent: %s\n", buff);

	close(fd);
	return EXIT_SUCCESS;
}
