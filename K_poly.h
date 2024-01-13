#define n_feature 30

double K_poly(double v[n_feature],double y[n_feature],double gamma, int deg)
{

double r=0;
double b=1;

for (int i = 0; i < n_feature; ++i)
{
  r=v[i]*y[i]+r;	
}

r=r*gamma;

for (int i=0;i<deg;i++)
{
  b=b*r;
}


return b;
}
