#ifndef UTILS
#define UTILS
#include <netinet/in.h>
#ifdef DEBUG
#include <stdio.h>
#define LOG(x,...) fprintf(stderr,x, __VA_ARGS__)
#else
#define LOG(x,...) do {} while(0)
#endif

int getfd(void);
void initaddr(struct sockaddr_in * restrict, char *, int);
int vers(void);

#endif
