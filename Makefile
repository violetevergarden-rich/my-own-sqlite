CC = gcc
CFLAGS = -Wall -Wextra -flto
OBJS = main.o input_buffer.o statement.o row.o table.o pager.o metacommand.o cursor.o tree.o

.PHONY: db clean

db: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o db