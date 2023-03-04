# here need your modification
MAJOR = 2
MINOR = 2
REVISION = 0

TARGET=main
INCLUDE_DIR=include
MODULE_DIR=moduleA moduleB

all:x64
DEBUG?=1
SRC_SUFFIX?=.cpp


# -std use the default one
CXXFLAGS=-MMD
LDFLAGS=-Llibs/$(PLATFORM)
ifeq ($(DEBUG),1)
FSANITIZE=-fsanitize=address #-fsanitize-recover=address
CXXFLAGS+=-g $(FSANITIZE)
LDFLAGS+=$(FSANITIZE)
endif
ifeq ($(SRC_SUFFIX),.c)
CFLAGS=$(CXXFLAGS)
endif

# main.o:CXXFLAGS+=`pkg-config --cflags opencv`
# LDLIBS=`pkg-config --libs opencv` -l3rdparty

# default compile rule is `$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c`
# default link rule is '$(CC) $(LDFLAGS) n.o $(LOADLIBES) $(LDLIBS)'
# It makes a difference where in the command you write this option;
# the linker searches and processes libraries and object files in the order they are
# specified.  Thus, foo.o -lz bar.o searches library z after file foo.o but before bar.o.
# If bar.o refers to functions in z, those functions may not be loaded.(man gcc)
#LOADLIBES=-l3rdparty

# supported platform 
arm:PLATFORM=arm
arm:CROSS_COMPILE=arm-linux-gnueabihf-
arm:$(TARGET)
	@echo "make arm"	

x64:PLATFORM=x64
x64:$(TARGET)
	@echo "make x64"	

help:
	@echo "make [x64|arm] [DEBUG=1|0] [SRC_SUFFIX=.cpp|.c], the first one is the default"
	@echo "make <help|clean|distclean>"


#*************************************************************
# there is no need modification below
#*************************************************************
SRC:=$(foreach mod,$(MODULE_DIR),$(wildcard $(mod)/*$(SRC_SUFFIX)))
OBJ:=$(patsubst %$(SRC_SUFFIX),%.o,$(SRC))
DEP:=$(patsubst %$(SRC_SUFFIX),%.d,$(SRC))
DEP+=$(TARGET).d
CXXFLAGS+=$(addprefix -I,$(INCLUDE_DIR) $(MODULE_DIR))

BUILD = $(shell date +%c)
VERSION = "$(TARGET) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)\n"
$(TARGET).o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(TARGET)"'

CC=$(CROSS_COMPILE)g++
CXX=$(CROSS_COMPILE)g++
AR=$(CROSS_COMPILE)ar

$(TARGET):$(TARGET).o $(OBJ)

# at the very beginning, there is no $(DEP), but all files would be compiled
# $(DEP) would be generated too, it will works then.
# but if you delete one .d file, and then edit related .h file, it can't works.
-include $(DEP)

distclean:clean
	rm -rf $(OBJ) $(DEP)
clean:
	rm -rf $(TARGET) *.o *.d

.PHONY:distclean clean
