#include <server.h>
#include <client.h>
#include <err.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int usage(char *progname)
{
	fprintf(stderr, "USAGE: %s [-c][-s] IP [PORT]\n", progname);
	return USAGE_ERR;
}

int (*method[2])(char*,int) = {client, server};

int main(int argc, char **argv)
{
	if (argc < 4 || (argv[1][1] != 's' && argv[1][1] != 'c'))
		return usage(argv[0]);
	return method[!strncmp(argv[1], "-s", 3)](argv[2], atoi(argv[3]));
}
