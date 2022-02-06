MAIN=
DEBUG=1

ifneq ($(DEBUG),)
CPPFLAGS=-D_GLIBCXX_DEBUG
CXXFLAGS=-std=c++17 -Wall -Wextra -Wno-sign-compare -g -fsanitize=address,undefined
else
CXXFLAGS=-std=c++17 -Wall -Wextra -Wno-sign-compare -O2
endif

all: $(MAIN)

clean:
	/usr/bin/find . -maxdepth 1 -type f -perm -111 ! -name login ! -name submit -delete
	rm -f *.stackdump

run: $(MAIN)
	./$(MAIN) < $(MAIN).in
