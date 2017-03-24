#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef float ftype;
typedef int itype;

void initialize(itype n, ftype *x, ftype *u){
	ftype dx = 1.0/(n-1);
	for(itype i = 0; i < n; i++){
		x[i] = i*dx;
		u[i] = 0.0;
		if( fabs(x[i] - 0.5) < 0.1 ){
			u[i] = 1.0;
		}
	}
}

void step(itype n, ftype *x, ftype *u, ftype dt){
	ftype um = u[0];
	ftype umm;
	for(itype i = 1; i < n; i++){
		umm = u[i];
		u[i] = u[i] - (u[i] - um)*dt;
		um = umm;
	}
	u[0] = um;
}



void write_to_file(itype n, ftype *x, ftype *u_initial, ftype *u){
	FILE* fp;
	fp = fopen("solution.dat", "w");
	for(itype i = 0; i < n; i++){
		fprintf(fp, "%.16f\t%.16f\t%.16f\n", x[i], u_initial[i], u[i]);
	}
	fclose(fp);
}

ftype error(itype n, ftype *u1, ftype *u2){
	ftype sum = 0.0;
	for(itype i = 0; i < n; i++){
		sum += (u1[i]-u2[i])*(u1[i]-u2[i]);
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

	ftype dt = 0.9;
	float dx = 1.0/(n-1);

	unsigned int long nsteps = (unsigned int long)cycle/dt/dx;
	printf("nsteps: %lu\n", nsteps);

	clock_t start = clock();
	for(unsigned int long i=0; i<nsteps; i++){
		step(n, x, u, dt);
	}	
	clock_t diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d s %d ms\n", msec/1000, msec%1000);

	
	ftype er = error(n, u, u_initial);
	printf("l2norm: %.3e\n", er);
	write_to_file(n, x, u_initial, u);
	free(u);
	free(u_initial);
	free(x);
};
