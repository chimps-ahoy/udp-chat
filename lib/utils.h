#ifndef UTILS
#define UTILS
#include <netinet/in.h>
#ifdef DEBUG
#include <stdio.h>
#define LOG(x,...) fprintf(stderr,"in %s::%s() @ L%d:\n\t " x, __FILE__, __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#else
#define LOG(x,...) do {} while(0)
#endif

typedef unsigned char Byte;

int getfd(void);
void initaddr(struct sockaddr_in * restrict, char const *restrict const, int);

#endif
