 
############################# Makefile ##########################
CFLAGS= -W -Wall -Iinclude -Wextra -lm -ansi -O2 -D_GNU_SOURCE `pkg-config --cflags --libs glib-2.0`
DEBUG= -g

OBJECTS:=$(patsubst %.c,%.o,$(wildcard src/*.c))
INCD:=$(wildcard include/*.h)
EXECUTAVEL=SGV

$(EXECUTAVEL): $(OBJECTS)
	cc -o $(EXECUTAVEL) $(OBJECTS)  $(CFLAGS)

run:
	./$(EXECUTAVEL)

clean:
	rm -rf src/*.o $(EXECUTAVEL) $(DOC)

debug:
	cc -o $(EXECUTAVEL) -Iinclude -lm -g src/*.c `pkg-config --cflags --libs glib-2.0`
