CC=cc
CFLAGS=-O0 -g
COBJS=ttc-log.o
TARGET_VERSION=0.1
TARGET=ttc-log.so.$(TARGET_VERSION)
TARGET_STATIC=ttc-log.a

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

clean:
	@echo cleaning directory...
	@rm $(COBJS) $(TARGET) $(TARGET_STATIC)
