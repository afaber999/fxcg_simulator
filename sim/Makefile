SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libfxcg_sim.a

CFLAGS= -c -Wall -Wpedantic -g
INCLUDE_PATHS = -I../../SDL2-2.26.4/x86_64-w64-mingw32/include -I../

CC=$(TOOLCHAIN_PREFIX)g++
AR=$(TOOLCHAIN_PREFIX)ar

all: $(SOURCES) $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS) 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $< -o $@


clean:
	rm $(OBJECTS) $(LIBRARY)