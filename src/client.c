#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "types.h"
#include "client.h"
#include "utils.h"

Status client(char *ip, int port)
{
	fprintf(stdout, "connecting to server on %s::%d\n", ip, port);

	int fd = getfd();
	struct sockaddr_in addr = {0};
	initaddr(&addr, ip, port);

	struct message msg = {
		.vers = VERSION,
		.comm = INIT,
		.usr  = 0,
		.data = "handshakey!!",
	};

	sendto(fd, &msg, sizeof(msg), 0, (struct sockaddr*)&addr, sizeof(addr));
	recvfrom(fd, &msg, sizeof(msg), 0, NULL, NULL);
	LOG("recieved data: %s\n", msg.data);

	close(fd);
	return EXIT_SUCCESS;
}
