SRCS = buffer_user_sem.c test_user_sem.c buffer_sem.h
BIN = utest
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
