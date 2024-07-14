#ifndef STATUS
#define STATUS
typedef enum {
	GOOD = 0,
	INIT_ERR,
	USAGE_ERR,
	BAD_VERS,
	MAXERR /*This must go at the end*/
} Status;
#endif
