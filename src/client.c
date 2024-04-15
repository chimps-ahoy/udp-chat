#include <client.h>
#include <err.h>

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int client(char *ip, int port)
{
	fprintf(stdout, "connecting to server on %s@%d\n", ip, port);

	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		fprintf(stderr, "bad fd\n");
		return INIT_ERR;
	}

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	char buff[256] = {0};
	fgets(buff, 256, stdin);
	sendto(fd, buff, 256, 0, (struct sockaddr*)&addr, sizeof(addr));
	fprintf(stdout, "sent: %s\n", buff);

	return EXIT_SUCCESS;
}
