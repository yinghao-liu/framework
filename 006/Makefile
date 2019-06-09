CXXFLAGS=-g -std=c++17
CC=$(CXX)

CASE?=1

ifeq ($(CASE), 3)
LDFLAGS=-Wl,-rpath='.'
else
LDFLAGS=-fsanitize=leak -Wl,-rpath='.'
endif
LOADLIBES=-L. -lexternal
LDLIBS=

all: libexternal.so main
ifneq ($(CASE), 3)
main.o:CXXFLAGS+=-fsanitize=leak
endif
main:main.o

ifeq ($(CASE), 3)
external.o:CXXFLAGS+=-shared -fPIC -fsanitize=leak
SHAREFLAGS=-fsanitize=leak -shared
else
external.o:CXXFLAGS+=-shared -fPIC
SHAREFLAGS:=-shared
endif
libexternal.so:external.o
	$(CC) $(SHAREFLAGS) -o $@ $^

help:
	@echo "make [CASE=1]"
	@echo "CASE can be 1,2,3 default is 1"
clean:
	@rm -rf *.o *.so main 
