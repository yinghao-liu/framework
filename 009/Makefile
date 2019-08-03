export PKG_CONFIG_PATH=/home/francis/ssl/lib/pkgconfig
CFLAGS=-g
#CFLAGS+=`pkg-config --cflags libcrypto`
#LDLIBS=`pkg-config --libs libcrypto`
LDLIBS=-lcrypto
main:main.o

clean:
	rm -rf *.o main
