CXXFLAGS=-g -std=c++17
CC=$(CXX)

LDFLAGS=-fsanitize=leak -Wl,-rpath='.'
LOADLIBES=-L. -lexternal
LDLIBS=

all: libexternal.so main
main.o:CXXFLAGS+=-fsanitize=leak
main:main.o


external.o:CXXFLAGS+=-shared -fPIC
libexternal.so:external.o
	$(CC) -shared -o $@ $^

clean:
	@rm -rf *.o *.so main 
