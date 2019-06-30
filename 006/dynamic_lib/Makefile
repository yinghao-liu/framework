CC=$(CXX)

CASE?=4

ifeq ($(CASE), 4)
CXXFLAGS=-fPIC
LDFLAGS=-Wl,-rpath='.'
endif

ifeq ($(CASE), 5)
LDFLAGS=-Wl,-rpath='.' -fsanitize=address
CXXFLAGS=-fPIC -fsanitize=address
endif


libdynamic_lib.so:dynamic_lib.o
	$(CC) -shared $(LDFLAGS) -o $@ $<
	cp $@ ../


clean:
	rm -rf *.o *.so
