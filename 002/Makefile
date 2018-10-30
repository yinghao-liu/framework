MAJOR = 0
MINOR = 0
REVISION = 0
NAME  = echo_server

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CPPFLAGS= -c -g -I. -Wl,-rpath='./'
LDFLAGS= -L. 
LDLIBS= -lrt -lpthread -luv
CC=g++
all:main 

main.o response.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o 
clean:
	rm -rf *.o main
