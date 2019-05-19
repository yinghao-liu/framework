CXXFLAGS=-g
CC=$(CXX)
#This instructs the linker to add all symbols, not only used ones
LDFLAGS=-rdynamic
all: main main_nodynamic
main:main.o

main_nodynamic:main.o
	$(CC) $^ -o $@
clean:
	@rm -rf *.o main main_nodynamic
