MAIN=
TEST=

CXXFLAGS=-std=c++11 -Wall -Wextra -Wno-sign-compare -g -D_GLIBCXX_DEBUG
#CXXFLAGS=-std=c++11 -Wall -Wextra -Wno-sign-compare -O2

all: $(MAIN)

clean:
	/usr/bin/find . -maxdepth 1 -type f -perm -111 -delete
	rm -f *.stackdump
run: $(MAIN)
	./$(MAIN) $(TEST)
