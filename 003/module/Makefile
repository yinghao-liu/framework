libmodule.so:module.o
	cc -shared -o $@ $< $(LDFLAGS) $(LDLIBS)
	cp $@ ../libs

CFLAGS=-I../external_module -fPIC
# here rpath is 
LDFLAGS=-L../libs -Wl,-rpath="libs"
LDLIBS=-lexternal_module

clean:
	rm -rf *.o *.so
