#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "types.h"
#include "server.h"
#include "utils.h"


static Byte usrcnt = 0;

static void handshake(struct message *restrict const msg, int fd, struct sockaddr *sa,
		              size_t size)
{
	struct message reply = {
		.vers = VERSION,
		.comm = INIT,
		.usr = ++usrcnt,
		.data = "Requesting identifier",
	};
	union { 
		unsigned short i;
		Byte b[2];
	} u = { .i = sizeof("Requesting identifier") };
	memcpy(&reply.len, &u.b, FIELDSIZE(struct message, len));
	sendto(fd, &reply, sizeof(reply), 0, sa, size);
}

static Status handlemsg(struct message *restrict const msg, int fd, struct sockaddr *sa,
		                size_t size)
{
	static void (*const msghandler[MAXCOMM])(struct message *restrict const, int,
			                                 struct sockaddr*, size_t) = {
		[INIT] = handshake,
	};
	if (msg->vers != VERSION) {
		LOG("version mismatch. msgvers = %hhd, expected = %hhd\n", msg->vers, VERSION);
		return BAD_VERS;
	}
	msghandler[msg->comm](msg, fd, sa, size);
	return MAXERR;
}

Status server(char const *restrict ip, int port)
{
	fprintf(stdout, "opening server on %s::%d\n", ip, port);

	int fd = getfd();
	struct sockaddr_in addr = {0};
	initaddr(&addr, ip, port);

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		LOG("bad bind %s::%d\n", ip, port);
		close(fd);
		return INIT_ERR;
	}

	int status = GOOD;
	struct message msg;
	while (status == GOOD) {
		struct sockaddr cl;
		socklen_t sl = sizeof(cl);
		recvfrom(fd, &msg, sizeof(msg), 0, &cl, &sl);
		LOG("recieved data: %s\n", msg.data);
		status = handlemsg(&msg, fd, &cl, sl);
	}

	close(fd);
	return EXIT_SUCCESS;
}
