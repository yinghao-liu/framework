MAJOR = 0
MINOR = 0
REVISION = 0
NAME  = uv_test

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CXXFLAGS=-g -I. -std=c++17
LDFLAGS= -L. -Wl,-rpath='.'
LDLIBS= -luv
CC=g++
all:main 

main.o response.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o 
clean:
	rm -rf *.o main
