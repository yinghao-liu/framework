libexternal_module.so:external_module.o
	$(CXX) -shared -o $@ $<
	cp $@ ../libs

CXXFLAGS=-I../include -fPIC

clean:
	rm -rf *.o *.so
