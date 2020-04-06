CC	= gcc
CFLAGS	= -g -pg
TARGET	= reverser 
OBJS	= reverser.o stack.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) -pg $(OBJS) -lm

$(OBJS): stack.h

.PHONY: clean
clean:
	/bin/rm -f *.o *~$(TARGET)
