#include <server.h>
#include <err.h>

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int server(char *ip, int port)
{
	fprintf(stdout, "opening server on %s@%d\n", ip, port);

	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		fprintf(stderr, "bad fd\n");
		return INIT_ERR;
	}

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		fprintf(stderr, "bad bind\n");
		return INIT_ERR;
	}
	for (int i = 0; i < 2; i++) {
		char buff[256] = {0};
		socklen_t size = sizeof(addr);
		recvfrom(fd, buff, 256, 0, (struct sockaddr*)&addr, &size);
		fprintf(stdout, "rec data: %s\n", buff);
		fprintf(stdout, "%d\n", htons(addr.sin_addr.s_addr));
	}

	return EXIT_SUCCESS;
}
