CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=c99 -I../c_impl
LDFLAGS = -lm

TARGET  = benchmark_c
SRCS    = benchmark.c ../c_impl/poisson_sampler.c
OBJS    = benchmark.o poisson_sampler.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

benchmark.o: benchmark.c
	$(CC) $(CFLAGS) -c -o $@ $<

poisson_sampler.o: ../c_impl/poisson_sampler.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
