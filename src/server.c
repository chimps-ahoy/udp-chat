#include "server.h"
#include "status.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

Status handlemsg(Byte const *restrict msg)
{
	if (*msg != VERSION) {
		LOG("version mismatch. msgvers = %d, expected = %d\n", *msg, VERSION);
		return BAD_VERS;
	}
	/* if id is zero, assign an ID and do handshake
	 * if id is nonzero, use COMM to index into function pointer arr
	 * etc
	 */
	return GOOD;
}

Status server(char const *restrict ip, int port)
{
	fprintf(stdout, "opening server on %s::%d\n", ip, port);

	int fd = getfd();
	struct sockaddr_in addr = {0};
	initaddr(&addr, ip, port);
	Byte buff[256] = {0};

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		LOG("bad bind %s::%d\n", ip, port);
		close(fd);
		return INIT_ERR;
	}

	int status = GOOD;
	while (status == GOOD) {
		recvfrom(fd, buff, 256, 0, NULL, NULL);
		LOG("recieved data: %s\n", buff);
		status = handlemsg(buff);
	}

	close(fd);
	return EXIT_SUCCESS;
}
