CC = gcc
CFLAGS = -o

all: sysheader systime

sysheader: sysheader.c
	$(CC) -H sysheader.c $(CFLAGS) sysheader

systime: systime.c
	$(CC) systime.c $(CFLAGS) systime

clean:
	rm -f sysheader systime