#ifndef TYPES
#define TYPES

typedef unsigned char Byte;

struct message {
	Byte vers;
	Byte comm;
	Byte usr;
	Byte len[2];
	Byte data[251];
};

typedef enum {
	GOOD = 0,
	INIT_ERR,
	USAGE_ERR,
	BAD_VERS,
	MAXERR /*This must go at the end*/
} Status;

typedef enum {
	INIT = 0,
	MAXCOMM /*This must go at the end*/
} Command;

#endif
