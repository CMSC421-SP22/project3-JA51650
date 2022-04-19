SRCS = buffer_mon.c test_mon.c
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
