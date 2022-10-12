/*
 ** This program that moves the initial conditions for a collision (COM)
 ** to a given position.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include "tipsy.h"

/*
** We use:
** struct dark_particle: float mass, float pos[3], float vel[3], float eps, float phi
**
** 1 AU = 1.496e13gcm = 23455.16064 RE
** 1 MSun = 1.989e33 g = 20803880.7804 code units
*/
void main(int argc, char **argv) {
		// Tipsy library
		TCTX in1, in2,out;
		int type, N1,N2;
		double dSoft;
		struct base_particle *p;
		struct gas_particle *g;
		struct dark_particle sun;
		double time1,time2;
		double x1,y1,z1,vx1,vy1,vz1;
		double x2,y2,z2,vx2,vy2,vz2;
        int i;

		// Check command line arguments
		if (argc != 15) {
			fprintf(stderr,"Usage: collide_genga <file1.std> <x1> <y1> <z1> <vx1> <vy1> <vz1> <file2.std> <x2> <y2> <z2> <vx2> <vy2> <vz2> > output.std\n");
			exit(1);
		}
		
		// file1 = atof(argv[1]);
		x1 = atof(argv[2]);
		y1 = atof(argv[3]);
		z1 = atof(argv[4]);

		vx1 = atof(argv[5]);
		vy1 = atof(argv[6]);
		vz1 = atof(argv[7]);

		// file2 = atof(argv[8]);
		x2 = atof(argv[9]);
		y2 = atof(argv[10]);
		z2 = atof(argv[11]);

		vx2 = atof(argv[12]);
		vy2 = atof(argv[13]);
		vz2 = atof(argv[14]);

		// Initialize tipsy library
		TipsyInitialize(&in1,0,argv[1]);
		TipsyInitialize(&in2,0,argv[8]);
		TipsyInitialize(&out,0,NULL);

		N1 = iTipsyNumParticles(in1);
		time1 = dTipsyTime(in1);
		fprintf(stderr,"Reading file 1: N=%i, t=%g\n",N1,time1);

		// Read all particles from the input file 1
        for (i = 0; i < N1; i++)
        {
                p = pTipsyRead(in1,&type,&dSoft);
                assert(type == TIPSY_TYPE_GAS);

                if (type == TIPSY_TYPE_GAS)
				{
					// Move the gas particle
					g = (struct gas_particle *)p;
					g->pos[0] += x1;
					g->pos[1] += y1;
					g->pos[2] += z1;
					
					g->vel[0] += vx1;
					g->vel[1] += vy1;
					g->vel[2] += vz1;
					TipsyAddGas(out,g);
				} else {
					fprintf(stderr,"Particle %i is not a gas particle\n",i);
				}
		}

		N2 = iTipsyNumParticles(in2);
		time2 = dTipsyTime(in2);
		fprintf(stderr,"Reading file 2: N=%i, t=%g\n",N2,time2);

		// Read all particles from the input file 2
        for (i = 0; i < N2; i++)
        {
                p = pTipsyRead(in2,&type,&dSoft);
                assert(type == TIPSY_TYPE_GAS);

                if (type == TIPSY_TYPE_GAS)
				{
					// Move the gas particle
					g = (struct gas_particle *)p;
					g->pos[0] += x2;
					g->pos[1] += y2;
					g->pos[2] += z2;
					
					g->vel[0] = vx2;
					g->vel[1] = vy2;
					g->vel[2] = vz2;
					TipsyAddGas(out,g);
				} else {
					fprintf(stderr,"Particle %i is not a gas particle\n",i);
				}
		}
		
		
//		fprintf(stderr,"Reading file 2: N=%i, t=%g\n",N2,time2);
		// Write to stdout
        TipsyWriteAll(out,0,NULL);

		TipsyFinish(in1);
		TipsyFinish(in2);
		TipsyFinish(out);
}



