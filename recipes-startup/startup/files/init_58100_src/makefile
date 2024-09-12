PROG1 = init_58100
SRCS1 = init_58100.cpp

CLEANFILES = $(PROG1)

CROSS_COMPILE ?= aarch64-linux-gnu-
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)ld

CFLAGS = -Wall -O -g
CXXFLAGS = -Wall -O -g

all: $(PROG1)

$(PROG1): $(SRCS1)
	$(CXX) -o $@ $^ $(CXXFLAGS) 


clean:
	rm -f $(PROG1) $(patsubst %.c, %.o, $(SRCS1))
