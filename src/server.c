#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "types.h"
#include "server.h"
#include "utils.h"

struct user {
	Byte id;
	struct sockaddr sa;
	char *name;
};
struct {
	size_t size;
	size_t count;
	struct user *users;
} userlist = {
	.size = 0,
	.count = 0,
	.users = NULL,
};

static Byte usrcnt = 0;

static void handshake(struct message *restrict const msg, int fd, struct sockaddr *sa,
		              size_t size)
{
	if (!msg->usr) { /* init user */
		union {
			unsigned short i;
			Byte b[2];
		} u = { .i = sizeof("Requesting identifier") };
		struct message reply = {
			.vers = VERSION,
			.comm = INIT,
			.usr  = ++usrcnt,
			.data = "Requesting identifier",
			.len[0] = u.b[0], 
			.len[1] = u.b[1]
		};
		sendto(fd, &reply, sizeof(reply), 0, sa, size);
		return;
	} else for (int i = 0; i < userlist.count; i++) {
		if (userlist.users[i].id == msg->usr)
			return; /* should not be sending INIT commands if in list */
	}
	if (userlist.count == userlist.size) {
		userlist.users = realloc(userlist.users, (++userlist.size)*sizeof(struct user));
	}
	userlist.users[userlist.count++] = (struct user) {
		.id   = msg->usr,
		.sa   = *sa,
		.name = strdup((char*)msg->data),
	};
	for (int i = 0; i < userlist.count; i++) {
		LOG("[%d] - user: %s<%d>\n", i, userlist.users[i].name, userlist.users[i].id);
	}
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
	return GOOD;
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
		status = handlemsg(&msg, fd, &cl, sl);
	}

	close(fd);
	return GOOD;
}
