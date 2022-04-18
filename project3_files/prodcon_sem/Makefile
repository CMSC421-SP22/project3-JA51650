SRCS = buffer_user.c main.c buffer_sem.h
BIN = test
CFLAGS = -g -Wall -Wextra -pedantic -std=gnu11
LDFLAGS = -g -pthread

OBJS = $(SRCS:.c=.o)

all: $(BIN)

%.o: $.c
	$(CC) - c $< -o $@ $(CFLAGS)

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f $(OBJS)
	-rm -f $(BIN)
