CC = gcc
CFLAGS = -O3 -Wall -DSIZE_I=2 -DSIZE_F=30 -march=native -ffast-math

all:
	$(CC) fp.c -o fp $(CFLAGS)
	$(CC) advection_fp.c -o advection_fp $(CFLAGS)
	$(CC) advection.c -o advection $(CFLAGS)

clean:
	rm advection advection_fp fp
