CC=$(CXX)

CASE?=5

ifeq ($(CASE), 5)
CXXFLAGS=-fPIC
LDFLAGS=-Wl,-rpath='.'
endif

ifeq ($(CASE), 6)
LDFLAGS=-Wl,-rpath='.' -fsanitize=address
CXXFLAGS=-fPIC -fsanitize=address
endif

ifeq ($(CASE), 7)
LDFLAGS=-Wl,-rpath='.' -fsanitize=address
CXXFLAGS=-fPIC -fsanitize=address
endif

libdynamic_lib.so:dynamic_lib.o
	$(CC) -shared $(LDFLAGS) -o $@ $<
	cp $@ ../


clean:
	rm -rf *.o *.so
