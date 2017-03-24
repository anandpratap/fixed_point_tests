#ifndef __FP_H
#define __FP_H

#ifndef SIZE_I
#define SIZE_I 2
#endif

#ifndef SIZE_F
#define SIZE_F 30
#endif

#if (SIZE_I + SIZE_F) == 8
typedef __int8_t datatype;
typedef __int16_t datatype_up;
#elif (SIZE_I + SIZE_F) == 16
typedef __int16_t datatype;
typedef __int32_t datatype_up;
#elif (SIZE_I + SIZE_F) == 32
typedef __int32_t datatype;
typedef __int64_t datatype_up;
#elif (SIZE_I + SIZE_F) == 64
typedef __int64_t datatype;
typedef __int128_t datatype_up;
#endif




struct fixed_point{
  datatype data;
};

void fp_set(struct fixed_point *fp, const float *rhs){
  fp->data = (datatype)(*rhs * ((datatype)1 << SIZE_F) + (*rhs>=0 ? 0.5: -0.5));
};

void fp_set_fp(struct fixed_point *fp, struct fixed_point *rhs){
	fp->data = rhs->data;
};

float fp_value(struct fixed_point *fp){
  return (float) fp->data / ((datatype)1 << SIZE_F);
};

double fp_value_d(struct fixed_point *fp){
	return (double) fp->data / ((datatype)1 << SIZE_F);
};

void fp_add(const struct fixed_point *a, const struct fixed_point *b, struct fixed_point *c){
  c->data = a->data + b->data;
}  

void fp_sub(const struct fixed_point *a, const struct fixed_point *b, struct fixed_point *c){
  c->data = a->data - b->data;
}  

void fp_mul(const struct fixed_point *a, const struct fixed_point *b, struct fixed_point *c){
  c->data = (datatype)(((datatype_up)a->data * (datatype_up)b->data) >> SIZE_F);
}  

void fp_div(const struct fixed_point *a, const struct fixed_point *b, struct fixed_point *c){
  c->data = (datatype)(((datatype_up)a->data << SIZE_F) / (datatype_up)b->data);
}  


typedef struct fixed_point fp;

#endif
