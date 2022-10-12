objects = tipsy.o 

CFLAGS ?= -O3

default: collide_genga

collide_genga: collide_genga.o $(objects) -lm

all:	collide_genga

clean:
		rm $(objects)

