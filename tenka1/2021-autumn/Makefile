MAIN=marisa
DEBUG=1

ifneq ($(DEBUG),)
CXXFLAGS=-std=c++17 -Wall -Wextra -Wno-sign-compare -g -D_GLIBCXX_DEBUG
ifeq ($(shell uname),Linux)
CXXFLAGS+=-fsanitize=address
endif
else
CXXFLAGS=-std=c++17 -Wall -Wextra -Wno-sign-compare -O2
endif

all: $(MAIN)

clean:
	/usr/bin/find . -maxdepth 1 -type f -perm -111 -delete
	rm -f *.stackdump

run: $(MAIN)
	./$(MAIN)

dev: $(MAIN)
	GAME_SERVER=https://contest.2021-autumn.gbc.tenka1.klab.jp/staging python call_api.py ./$(MAIN)

prod: $(MAIN)
	GAME_SERVER=https://contest.2021-autumn.gbc.tenka1.klab.jp python call_api.py ./$(MAIN)
