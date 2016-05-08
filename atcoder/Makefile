MAIN=A

CXXFLAGS=-std=c++14 -Wall -Wextra -g -D_GLIBCXX_DEBUG
#CXXFLAGS=-std=c++14 -Wall -Wextra -O2

all: $(MAIN)

clean:
	/usr/bin/find . -maxdepth 1 -type f -perm -111 -delete
	rm -f *.stackdump
run: $(MAIN)
	./$(MAIN) < $(MAIN).in
