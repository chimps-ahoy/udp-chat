#include "utils.h"
#include "types.h"

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

int getfd(void)
{
	int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (fd < 0) {
		LOG("bad fd: %d\n", fd);
		fprintf(stderr, "bad fd\n");
		exit(INIT_ERR);
	}
	return fd;
}

void initaddr(struct sockaddr_in *restrict s, char const *restrict const ip, int port)
{
	s->sin_family = AF_INET;
	s->sin_port = htons(port);
	s->sin_addr.s_addr = inet_addr(ip);
}
