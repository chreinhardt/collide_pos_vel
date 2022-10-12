objects = tipsy.o 

CFLAGS ?= -O3

default: collide_pos_vel

collide_pos_vel: collide_pos_vel.o $(objects) -lm

all:	collide_pos_vel

clean:
		rm $(objects)

