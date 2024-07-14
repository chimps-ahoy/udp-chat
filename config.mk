EXEC    = pisscord
VERSION = 000

TOPDIR != pwd
SRCDIR ::= $(TOPDIR)/src
HDRDIR ::= $(TOPDIR)/lib
BINDIR ::= $(TOPDIR)/bin

SOURCES != find $(SRCDIR) -name "*.c"
OBJECTS != echo $(SOURCES) | sed -e 's,\.c,.o,g'
HDRS    != find $(HDRDIR) -name "*.h"

PREFIX    = /usr/local
MANPREFIX = $(PREFIX)/share/man

INCS = -I$(HDRDIR)

CC     =/bin/cc
CFLAGS = -std=c2x -pedantic -Wall $(INCS) -DVERSION=$(VERSION)
