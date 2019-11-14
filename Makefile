CC := gcc
CFLAGS=-Wall -Wextra -std=c11 -I ./include/
SRCROOT = .
SRCDIRS := $(shell find $(SRCROOT) -type d)
SRCS=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
OBJS=$(SRCS:.c=.o)
.PHONY: clean

release: $(OBJS)
	$(CC) -o infer $(OBJS) $(LDFLAGS)

clean:
	$(RM) src/*.o
