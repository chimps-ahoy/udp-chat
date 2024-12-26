#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

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

	char name[20] = {0};
	printf("Identifier: ");
	fgets(name, 20, stdin);
	name[strcspn(name, "\n")] = 0;
	printf("\n");

	memcpy(msg.data, name, 20);
	union {
		unsigned short i;
		Byte b[2];
	} u = {
		.i = 20
	};
	msg.len[0] = u.b[0];
	msg.len[1] = u.b[1];
	sendto(fd, &msg, sizeof(msg), 0, (struct sockaddr*)&addr, sizeof(addr));

	close(fd);
	return EXIT_SUCCESS;
}
