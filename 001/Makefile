MAJOR = 0
MINOR = 0
REVISION = 0
NAME  = echo_server

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CPPFLAGS= -c -g -std=c++17 -g3 -gdwarf-2
LDFLAGS=
LOADLIBES=-lrt -lpthread
CC=g++
all:main client

main.o response.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o response.o log.o
client:client.o
clean:
	@rm -rf *.o *.so main client
