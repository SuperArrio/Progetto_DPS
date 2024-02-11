#include "K_poly.h"
#define n_feature 30
double K_poly(double v[n_feature],double y[n_feature],double gamma)
{

double r[n_feature];
double result=0;
double r_1=0;
double r_2=0;
double r_3=0;
double r_4=0;





LOOP_I: for (int i = 0; i < n_feature; ++i)
{
#pragma HLS UNROLL factor=30
  r[i]=v[i]*y[i];
}

r_1=    r[0]+r[1]+r[2]+r[3]+r[4]+r[5]+r[6]+r[7]+
		r[8]+r[9]+r[10]+r[11]+r[12]+r[13]+r[14]+r[15]+
		r[16]+r[17]+r[18]+r[19]+r[20]+r[21]+r[22]+r[23]+
		r[24]+r[25]+r[26]+r[27]+r[28]+r[29];

r_2=r_1*gamma;
r_3=r_2;
r_4=r_3;


result=r_2*r_3*r_4;

return result;
}



