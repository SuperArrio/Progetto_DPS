#define n_feature 30

double prodotto_scalare(double v[n_feature],double y[n_feature])
{

double r=0;

for (int i = 0; i < n_feature; ++i)
{
  r=v[i]*y[i]+r;	
}


return r;
}
