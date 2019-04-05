MAJOR = 0
MINOR = 0
REVISION = 0
NAME  = dynamic

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CPPFLAGS= -c -g -Wl,-rpath='libs'
#LDFLAGS= -L. 
LDLIBS= -ldl
CC=g++
all:main 

main.o response.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o 
clean:
	rm -rf *.o main
