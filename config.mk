EXEC    = pisscord
VERSION = 000

TOPDIR != pwd
SRCDIR ::= $(TOPDIR)/src
BINDIR ::= $(TOPDIR)/bin

SOURCES != find $(SRCDIR) -name "*.c"
OBJECTS != echo $(SOURCES) | sed -e 's,\.c,.o,g'
SOURCES != find $(SRCDIR) -name "*.h"

PREFIX    = /usr/local
MANPREFIX = $(PREFIX)/share/man

LIBS =

FLAGS =

CC     =/bin/cc
CFLAGS = -std=c2x -pedantic -Wall $(LIBS) -DVERSION=$(VERSION) \
		 -D_POSIX_C_SOURCE_200112L
