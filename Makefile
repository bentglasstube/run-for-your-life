SOURCES=$(wildcard src/*.cc)
CONTENT=$(wildcard content/*)
BUILDDIR=build
OBJECTS=$(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))

CC=clang++
CFLAGS=-O2 -g --std=c++14
CFLAGS+=-Wall -Wextra
LDFLAGS=-static-libstdc++ -static-libgcc

LDLIBS=`sdl2-config --cflags --libs` -lSDL2_mixer -Wl,-Bstatic -lnoise

EXECUTABLE=$(BUILDDIR)/rfyl

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(BUILDDIR)/src
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(BUILDDIR)

rfyl.tgz: $(EXECUTABLE)
	mkdir rfyl
	cp $(EXECUTABLE) README.md rfyl
	cp -R content rfyl/content
	tar zcf $@ rfyl
	rm -rf rfyl

PHONY: all clean run
