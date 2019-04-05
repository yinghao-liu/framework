libmodule.so:module.o
	cc -shared -fPIC -o $@ $< $(LDFLAGS) $(LDLIBS)
	cp $@ ../libs

CFLAGS=-I../include -fPIC
LDFLAGS=-L../libs
LDLIBS=-lexternal_module

clean:
	rm -rf *.o *.so
