CC = gcc
CFLAGS = -Wall -Wextra
OBJS = main.o input_buffer.o statement.o

db: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o db