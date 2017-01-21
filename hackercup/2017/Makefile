MAIN=A

FILE=$(MAIN)-sample
#FILE=$(MAIN)-judge

CXXFLAGS=-std=c++14 -Wall -Wextra -Wno-sign-compare -Wno-unused-result -g -D_GLIBCXX_DEBUG
#CXXFLAGS=-std=c++14 -Wall -Wextra -Wno-sign-compare -Wno-unused-result -O2 -fopenmp

all: $(MAIN)

clean:
	/usr/bin/find . -maxdepth 1 -type f -perm -111 -delete
	rm -f *.stackdump

check: $(MAIN)
	./$< < $(MAIN)-sample.in | diff -sZ - $(MAIN)-sample.ans
run: $(MAIN)
	./$< < $(FILE).in
out: $(MAIN)
	./$< < $(FILE).in > $(FILE).out
