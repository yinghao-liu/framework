CXXFLAGS=-g -std=c++17 -DMODE=$(CASE)
CC=$(CXX)

CASE?=1
FSANITIZE=-fsanitize=address
ALL:=main

ifeq ($(CASE), 1)
CXXFLAGS+=$(FSANITIZE) 
LDFLAGS+=$(FSANITIZE)
endif

ifeq ($(CASE), 2)
ALL:=libshared_lib.so $(ALL)
main.o:CXXFLAGS+=$(FSANITIZE)
LDFLAGS+=-Wl,-rpath='.' $(FSANITIZE)
LOADLIBES=-L. -lshared_lib
shared_lib.o:CXXFLAGS+=-shared -fPIC
SHAREFLAGS:=-shared
endif

ifeq ($(CASE), 3)
ALL:=libshared_lib.so $(ALL)
LDFLAGS=-Wl,-rpath='.'
LOADLIBES=-L. -lshared_lib
shared_lib.o:CXXFLAGS+=-shared -fPIC $(FSANITIZE)
SHAREFLAGS=-shared $(FSANITIZE)
endif

ifeq ($(CASE), 4)
ALL+=dependence
CXXFLAGS+=$(FSANITIZE)
LDFLAGS+=$(FSANITIZE)
endif

ifeq ($(CASE), 5)
ALL+=dependence
endif

LDLIBS=




all: $(ALL)

main:main.o

libshared_lib.so:shared_lib.o
	$(CC) $(SHAREFLAGS) -o $@ $^

dependence:
	make -C dynamic_lib CASE=$(CASE)

help:
	@echo "make [CASE=1]"
	@echo "CASE can be 1,2,3,4,5 refer to <README.md>, default is 1"
clean:
	@rm -rf *.o *.so main 
	make -C dynamic_lib clean
