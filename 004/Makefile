config_file:=config.proto
protobuf_path:=protobuf

protobuf_out:=$(protobuf_path)/$(basename $(config_file)).pb.cc 
protobuf_out+=$(protobuf_path)/$(basename $(config_file)).pb.h

all: $(protobuf_out) main

CC=g++
CXXFLAGS=-g -std=c++11
LDLIBS=-lprotobuf
$(protobuf_out):$(config_file)
	protoc --cpp_out=$(protobuf_path) $^

main:main.o protobuf/$(basename $(config_file)).pb.o

clean:
	rm -rf *.o protobuf/*.o main
