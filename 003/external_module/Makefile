libexternal_module.so:external_module.o
	$(CC) -shared -o $@ $<
	cp $@ ../libs

CFLAGS=-I../include -fPIC

clean:
	rm -rf *.o *.so
