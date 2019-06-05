CXXFLAGS=-g -std=c++17 -fsanitize=leak
CC=$(CXX)

LDFLAGS=-fsanitize=leak
LOADLIBS=
all: main
main:main.o

clean:
	@rm -rf *.o main main_nodynamic
