.POSIX:
include config.mk

CFLAGS += -DDEBUG

$(EXEC) : $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BINDIR)/$@

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	rm -f $(BINDIR)/* $(SRCDIR)/*.o
