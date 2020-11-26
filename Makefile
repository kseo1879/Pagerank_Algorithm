CC=gcc
CFLAGS=-Wall -Werror -std=gnu11 -fsanitize=address -fopenmp
TARGET=pagerank
INPUTS = $(shell ls ./tests/*.in)
OUTPUTS = $(patsubst %.in, %.out, $(INPUTS))
TESTS = $(patsubst %.in, %.test, $(INPUTS))

.PHONY: clean test
all: $(TARGET)

pagerank: ./pagerank.c #pagerank.h
	$(CC) $(CFLAGS) $^ -o $@ -lpthread -lm -g

clean:
	rm -f *.o
	rm -f ./pagerank

test: $(TESTS)

%.test: %.in %.out $(TARGET)
	@./$(TARGET) < $*.in > $@;
	@if cmp -s $@ $*.out; then \
        echo "PASSED THE TEST: $*.in, AGAINST: $*.out"; \
    else \
        echo "FAILED THE TEST: $*"; \
    fi
	@rm $@
