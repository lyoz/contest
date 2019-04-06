MAIN=
DEBUG=1

ifneq ($(DEBUG),)
CXXFLAGS=-std=c++14 -Wall -Wextra -Wno-sign-compare -g -D_GLIBCXX_DEBUG
ifeq ($(shell uname),Linux)
CXXFLAGS+=-fsanitize=address
endif
else
CXXFLAGS=-std=c++14 -Wall -Wextra -Wno-sign-compare -O2
endif

all: $(MAIN)

clean:
	/usr/bin/find . -maxdepth 1 -type f -perm -111 -delete
	rm -f *.stackdump
run: $(MAIN)
	./$(MAIN) < $(MAIN).in
