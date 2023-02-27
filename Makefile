objects = tipsy.o 

# tirpc library (needed if glibc >= 2.32)
RPC_LIB = -ltirpc

LIBS ?= -lm $(RPC_LIB)

CFLAGS ?= -O3

default: collide_pos_vel

collide_pos_vel: collide_pos_vel.o $(objects) $(LIBS)

all:	collide_pos_vel

clean:
		rm $(objects)

