/* Requires netinet/in.h */
#ifndef UTILS
#define UTILS
#ifdef DEBUG
#include <stdio.h>
#define LOG(x,...) fprintf(stderr,"in %s::%s() @ L%d:\n\t " x, __FILE__, __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#else
#define LOG(x,...) do {} while(0)
#endif
#define FIELDSIZE(t,f) (sizeof(((t*)0)->f))

#define recvfrom(fd,buf,size,flags,from,fromlen) do {\
recvfrom(fd, buf, size, flags, from, fromlen);\
LOG("recieved: %s\n", (char*)buf.data);\
} while (0);

int getfd(void);
void initaddr(struct sockaddr_in * restrict, char const *restrict const, int);

#endif
