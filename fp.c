#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "fp.h"

int main(void){
	double epsilon = 1.0/((datatype)1 << SIZE_F);
	float f = -11.1221312;
	float f1 = -2.13212312;
	fp p1, p2, p3;
	fp_set(&p1, &f);
	fp_set(&p2, &f1);

	fp_add(&p1, &p2, &p3);
	float value = fp_value(&p3);
	printf("%.15e\t~\t%.15e\n", f+f1, value);
	assert(fabs(f+f1 - value) <= epsilon);
  
	fp_sub(&p1, &p2, &p3);
	value = fp_value(&p3);
	printf("%.15e\t~\t%.15e\n", f-f1, value);
	assert(fabs(f-f1 - value) <= epsilon);

	fp_mul(&p1, &p2, &p3);
	value = fp_value(&p3);
	printf("%.15e\t~\t%.15e\n", f*f1, value);
	assert(fabs(f*f1 - value) <= epsilon);
 
	fp_div(&p1, &p2, &p3);
	value = fp_value(&p3);
	printf("%.15e\t~\t%.15e\n", f/f1, value);
	assert(fabs(f/f1 - value) <= epsilon);
	  
	printf("precision: %.10e\n", 1.0/((datatype)1 << SIZE_F));
	return 0;
};
