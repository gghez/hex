CC=gcc

hex:
	$(CC) hex.c -o hex

install:
	cp hex /usr/local/bin/

clean:
	rm hex

uninstall:
	rm /usr/local/bin/hex

