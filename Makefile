CC=gcc
CFLAGS=-Wall -Werror -std=gnu11 -fsanitize=address -fopenmp
TARGET=pagerank
INPUTS = $(shell ls ./tests/*.in)
OUTPUTS = $(patsubst %.in, %.out, $(INPUTS))
TESTS = $(patsubst %.in, %.test, $(INPUTS))

.PHONY: clean test
all: $(TARGET)

pagerank: ./pagerank.c pagerank.h
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
        echo "FAILED THE TEST: $*.in"; \
    fi
	@rm $@

# got the idea of testing from
# https://stackoverflow.com/questions/23020191/how-to-use-in-and-out-files-for-testing-in-a-unix-environment
