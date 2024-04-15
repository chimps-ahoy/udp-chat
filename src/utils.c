#include <errs.h>
#include <utils.h>

#include <stdlib.h>
#include <arpa/inet.h>

int getfd(void)
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		LOG("bad fd: %d\n", fd);
		fprintf(stderr, "bad fd\n");
		exit(INIT_ERR);
	}
	return fd;
}

void initaddr(struct sockaddr_in *restrict s, char *ip, int port)
{
	s->sin_family = AF_INET;
	s->sin_port = htons(port);
	s->sin_addr.s_addr = inet_addr(ip);
}

int vers(void)
{
	char *v = VERSION;
	char *_v2 = calloc(sizeof(VERSION) - 2, 1);
	char *v2 = _v2;
	while (*v) {
		if (*v != '.')
			*v2++ = *v;
		v++;
	}
	int vers = strtol(_v2, NULL, 10);
	free(_v2);
	return vers;
}
