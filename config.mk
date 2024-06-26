EXEC = pisscord
VERSION = 0.0.0

TOPDIR := $(shell pwd)
SRCDIR := $(TOPDIR)/src
BINDIR := $(TOPDIR)/bin
OBJDIR := $(TOPDIR)/obj
HDRDIR := $(TOPDIR)/lib

SOURCES := $(shell find $(SRCDIR) -name "*.c") 
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

INCS = -I$(HDRDIR)

CFLAGS = -std=c2x -pedantic -Wall $(INCS) -DVERSION=\"$(VERSION)\"
