CFLAGS = -Wall -Wpedantic -Wextra  -Wno-unused-parameter -Wno-unused-function -Werror -std=gnu99
SRC_DIR = src

all:
	gcc -o hsg $(SRC_DIR)/*.c $(CFLAGS) -O3
	rm -f *.o

debug:
	gcc -g -o hsg $(SRC_DIR)/*.c $(CFLAGS)
	rm -f *.o

clean:
	rm -rf hsg hsg.dSYM