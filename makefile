CC=gcc
CFLAGS=-Wall -O3

8080-as: *.c *.h
	$(CC) $(CFLAGS) *.c -o $@

clean:
	rm -rf *.out
	rm -rf 8080-as