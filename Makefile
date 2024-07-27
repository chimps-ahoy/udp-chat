.POSIX:
include config.mk

$(EXEC) : $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BINDIR)/$@

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	rm -f $(BINDIR)/* $(SRCDIR)/*.o
