MUDUO_DIRECTORY ?= $(HOME)/shengkai/net/build/release-install-cpp11
#MUDUO_DIRECTORY ?= $(HOME)/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
SRC = .

CXXFLAGS = -g -O0 -Wall -Wextra -Werror \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -I$(MUDUO_INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt -lmuduo_http

all: rect
clean:
	rm -f rect core

rect : $(SRC)/HttpServer_test.cc
	g++ -std=c++11 $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean
