CC=cc
CFLAGS=-O0 -g
COBJS=ttc-log.o
TARGET_VERSION=0.1
TARGET_NAME=ttc-log.so
TARGET=$(TARGET_NAME).$(TARGET_VERSION)
TARGET_STATIC=ttc-log.a

DESTDIR=/usr/local

all: $(TARGET) $(TARGET_STATIC)

.c.o:
	@echo $(CC) $@
	@$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_STATIC): $(COBJS)
	@echo $(AR) $@
	@$(AR) -rcs $@ $(COBJS)

$(TARGET): $(COBJS)
	@echo $(CC) $@
	$(CC) $(CFLAGS) -shared -o $(TARGET) $(COBJS)

install: $(TARGET) $(TARGET_STATIC)
	install -m 755 $(TARGET) $(DESTDIR)/lib/lib$(TARGET)
	install -m 755 $(TARGET_STATIC) $(DESTDIR)/lib/lib$(TARGET_STATIC)
	ln -s $(DESTDIR)/lib/lib$(TARGET) $(DESTDIR)/lib/lib$(TARGET_NAME)
	install -m 644 ttc-log.h $(DESTDIR)/include/ttc-log.h

uninstall:
	rm $(DESTDIR)/lib/lib$(TARGET_NAME) $(DESTDIR)/lib/lib$(TARGET_STATIC) $(DESTDIR)/include/ttc-log.h $(DESTDIR)/lib/lib$(TARGET) 

clean:
	@echo cleaning directory...
	@rm $(COBJS) $(TARGET) $(TARGET_STATIC)
