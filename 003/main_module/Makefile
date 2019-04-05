libmain_module.so:main_module.o
	$(CC) -shared -o $@ $^
	cp $@ ../libs

CFLAGS=-fPIC

clean:
	rm -rf *.o *.so
