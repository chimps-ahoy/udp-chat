#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define USAGE_ERR 1
#define INIT_ERR 2

int usage(char *progname)
{
	fprintf(stderr, "USAGE: %s [-c][-s] IP [PORT]\n", progname);
	return USAGE_ERR;
}

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
	char buff[256] = {0};
	socklen_t size = sizeof(addr);
	recvfrom(fd, buff, 256, 0, (struct sockaddr*)&addr, &size);
	fprintf(stdout, "rec data: %s\n", buff);

	return EXIT_SUCCESS;
}

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

int (*method[2])(char*,int) = {client, server};

int main(int argc, char **argv)
{
	if (argc < 4 || (argv[1][1] != 's' && argv[1][1] != 'c'))
		return usage(argv[0]);
	return method[!strncmp(argv[1], "-s", 3)](argv[2], atoi(argv[3]));
}
