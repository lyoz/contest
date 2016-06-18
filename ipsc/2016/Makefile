MAIN=a

CXXFLAGS=-std=c++14 -Wall -Wextra -g -D_GLIBCXX_DEBUG
#CXXFLAGS=-std=c++14 -Wall -Wextra -O2

FILE=$(MAIN)-sample
#FILE=$(MAIN)1
#FILE=$(MAIN)2

all: $(MAIN)

clean:
	/usr/bin/find . -maxdepth 1 -type f -perm -111 -delete
	rm -f *.stackdump
run: $(MAIN)
	./$(MAIN) < $(FILE).in
out: $(MAIN)
	./$(MAIN) <$(FILE).in >$(FILE).out
