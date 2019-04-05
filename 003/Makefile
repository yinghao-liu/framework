MAJOR = 0
MINOR = 0
REVISION = 0
NAME  = dynamic

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CFLAGS= -c -g
LDFLAGS= -Wl,-rpath='libs'
LDLIBS= -ldl -Llibs -lmain_module
#CC=g++
all:dependence main 

dependence:
	make -C external_module
	make -C module
	make -C main_module

main.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o 

clean:
	rm -rf *.o main
	make -C external_module clean
	make -C module clean
	make -C main_module clean
