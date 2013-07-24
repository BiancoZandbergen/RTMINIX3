# Build all tests

CC=exec cc
TESTS=test1 \
	  test2 \
	  test3 \
	  test4 \
	  test5 \
	  test6 \
	  test7 \
	  test8 \
	  test9 \
	  test10 \
	  test11 \
	  test12 \
	  test13 \
	  test14 \
	  test15 \
	  test16 \
	  test17 \
	  test18 \
	  test19

all: $(TESTS)

clean:
	find . -name "*[0-9]" -exec rm {} \;
	find . -name "*[0-9][0-9]" -exec rm {} \;

$(TESTS):
	$(CC) -o $@ $@.c -lsem



