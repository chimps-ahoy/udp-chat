#include "server.h"
#include "client.h"
#include "types.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc == 4 && !strncmp(argv[1], "-s", 3))
		return server(argv[2], atoi(argv[3]));
	if (argc == 4 && !strncmp(argv[1], "-c", 3))
		return client(argv[2], atoi(argv[3]));
	fprintf(stderr, "USAGE: %s [-c][-s] IP [PORT]\n", *argv);
	return USAGE_ERR;
}
