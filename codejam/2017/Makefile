MAIN=A

FILE=$(MAIN)-sample
#FILE=$(MAIN)-small-attempt0
#FILE=$(MAIN)-large
#FILE=$(MAIN)-small-practice
#FILE=$(MAIN)-large-practice

CXXFLAGS=-std=c++14 -Wall -Wextra -Wno-sign-compare -Wno-unused-result -g -D_GLIBCXX_DEBUG
#CXXFLAGS=-std=c++14 -Wall -Wextra -Wno-sign-compare -Wno-unused-result -O2 -fopenmp

all: $(MAIN)
clean:
ifeq ($(OS),Windows_NT)
	rm -f *.exe *.stackdump
else
	find . -maxdepth 1 -type f -perm -111 -delete
endif

check: $(MAIN)
	./$< < $(MAIN)-sample.in | diff -sZ - $(MAIN)-sample.ans
run: $(MAIN)
	./$< < $(FILE).in
out: $(MAIN)
	./$< < $(FILE).in > $(FILE).out
