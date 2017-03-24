#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fp.h"
typedef fp ftype;
typedef int itype;

void initialize(itype n, ftype *x, ftype *u){
	float dxf = (float)1.0/(n-1);
	for(itype i = 0; i < n; i++){
		float xi = i*dxf;
		fp_set(&x[i], &xi);
		float ui = 0.0;
		fp_set(&u[i], &ui);
		if( fabs(xi - 0.5) < 0.1 ){
			ui = 1.0;
			fp_set(&u[i], &ui);
		}
	}
}

void step(itype n, ftype *x, ftype *u, ftype dt){
	ftype um;
	um = u[0];
	ftype ui;
	for(itype i = 1; i < n; i++){
		ui = u[i];
		ftype umm1, umm2, umm3;
		fp_sub(&ui, &um, &umm1);
		fp_mul(&umm1, &dt, &umm2);
		fp_sub(&ui, &umm2, &umm3);
		u[i] = umm3;
		um = ui;
	}
	u[0] = um;
}



void write_to_file(itype n, ftype *x, ftype *u_initial, ftype *u){
	FILE* fp;
	fp = fopen("solution_fp.dat", "w");
	for(itype i = 0; i < n; i++){
		double uf_i = fp_value_d(&u_initial[i]);
		double uf = fp_value_d(&u[i]);
		float xi = fp_value(&x[i]);
		fprintf(fp, "%.16f\t%.16f\t%.16f\n", xi, uf_i, uf);
	}
	fclose(fp);
}

float error(itype n, ftype *u1, ftype *u2){
	float sum = 0.0;
	for(itype i = 0; i < n; i++){
		float u1i = fp_value(&u1[i]);
		float u2i = fp_value(&u2[i]);
		sum += (u1i-u2i)*(u1i-u2i);
	}
	sum = sqrt(sum)/n;
	return sum;
};

int main(int argc, char **argv){
	itype n = atoi(argv[1]);
	itype cycle = atoi(argv[2]);
		
	ftype *x = malloc(n * sizeof(ftype));
	ftype *u_initial = malloc(n * sizeof(ftype));
	ftype *u = malloc(n * sizeof(ftype));
	initialize(n, x, u);
	initialize(n, x, u_initial);

	float dtf = 0.9;
	float dx = 1.0/(n-1);
	ftype dt;
	fp_set(&dt, &dtf);

	unsigned int long nsteps = (unsigned int long)cycle/dtf/dx;
	printf("nsteps: %lu\n", nsteps);

	clock_t start = clock();
	for(unsigned int long i=0; i<nsteps; i++){
		step(n, x, u, dt);
	}	
	clock_t diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d s %d ms\n", msec/1000, msec%1000);

	float er = error(n, u, u_initial);
	printf("l2norm: %.3e\n", er); 
	write_to_file(n, x, u_initial, u); 
	free(u);
	free(u_initial);
	free(x);
};
