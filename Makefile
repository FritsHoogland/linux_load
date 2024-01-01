CC=gcc
OBJ=uninterruptible.c

%.o: %.c
	$(CC) -c -o $@ $<

uninterruptible: $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f *o
