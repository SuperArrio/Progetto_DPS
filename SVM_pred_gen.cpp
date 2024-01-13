#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include "prodotto_scalare.h"
#include "K_poly.h"

//#define kernel_linear
#define kernel_poly

#define dim_w 30
#define n_test 171
#define n_feature 30

#ifdef kernel_linear 
#define n_sv 49
#endif

#ifdef kernel_poly
#define n_sv 106
#endif




using namespace std;

int main()
{
 
  string line;
  double b;
  double X_test[n_test][n_feature];
  double sv_x[n_sv][n_feature];
  double lambda[n_sv];
  int sv_y[n_sv];
  int y_pred_py[n_test];
  double y_pred[n_test];
  #ifdef kernel_poly
  int deg=3;
  double gamma=0;
  #endif
  

  //acquisisco gamma (kernel polynomial)
  #ifdef kernel_poly
  ifstream gamma_file;
  gamma_file.open("gamma_poly.txt");
  if (gamma_file.is_open())
    {gamma_file >> gamma;}
  else
    {cout << "Unable to open file gamma_file"; }
  //cout << "gamma: " << gamma << endl;
  #endif 

  //acquisisco b X_test sv_x lmabda sv_y y_pred_py

  ifstream X_test_file;
  #ifdef kernel_linear
  X_test_file.open("X_test.csv");
  #endif

  #ifdef kernel_poly
  X_test_file.open("X_test_poly.csv");
  #endif

  int j=0;
  int i=0;
  if (X_test_file.is_open())
  {
   while ( getline (X_test_file,line) )
    {
        istringstream iss(line);
        double value;
        j=0;
        while (iss >> value) {
          X_test[i][j]=value;
          j++;
        }
        i++;
    }
    X_test_file.close();
  }
  else cout << "Unable to open file X_test_file"; 


  ifstream b_file;
  #ifdef kernel_linear
  b_file.open("b.csv");
  #endif
  #ifdef kernel_poly
  b_file.open("b_poly.csv");
  #endif

  i=0;
  if (b_file.is_open())
  {
    while ( getline (b_file,line) )
    {
     sscanf(line.c_str(),"%lf",&b);
      i++;
    }
    b_file.close();
  }
  else cout << "Unable to open file b"; 


  ifstream sv_x_file;
  #ifdef kernel_linear
  sv_x_file.open("sv_x.csv");
  #endif
  #ifdef kernel_poly
  sv_x_file.open("sv_x_poly.csv");
  #endif

  j=0;
  i=0;
  if (sv_x_file.is_open())
  {
   while ( getline (sv_x_file,line) )
    {
        istringstream iss(line);
        double value;
        j=0;
        while (iss >> value) {
          sv_x[i][j]=value;
          j++;
        }
        i++;
    }
    sv_x_file.close();
  }
  else cout << "Unable to open file sv_x_file"; 

  ifstream lambda_file;
  #ifdef kernel_linear
  lambda_file.open("lambdas.csv");
  #endif
  #ifdef kernel_poly
  lambda_file.open("lambdas_poly.csv");
  #endif
  i=0;
  if (lambda_file.is_open())
  {
    while ( getline (lambda_file,line) )
    {
     sscanf(line.c_str(),"%lf",&(lambda[i]));
      i++;
    }
    lambda_file.close();
  }
  else cout << "Unable to open file lambda_file"; 

  ifstream sv_y_file;
  #ifdef kernel_linear
  sv_y_file.open("sv_y.csv");
  #endif
  #ifdef kernel_poly
  sv_y_file.open("sv_y_poly.csv");
  #endif

  i=0;
  if (sv_y_file.is_open())
  {
    while ( getline (sv_y_file,line) )
    {
     sscanf(line.c_str(),"%d",&(sv_y[i]));
      i++;

    }
    sv_y_file.close();
  }
  else cout << "Unable to open file sv_file"; 

  

  ifstream y_pred_py_file;
  #ifdef kernel_linear
  y_pred_py_file.open("y_pred_py.csv");
  #endif
  #ifdef kernel_poly
  y_pred_py_file.open("y_pred_py_poly.csv");
  #endif

  i=0;
  if (y_pred_py_file.is_open())
  {
    while ( getline (y_pred_py_file,line) )
    {
      sscanf(line.c_str(),"%d",&(y_pred_py[i]));
      i++;
    }
    y_pred_py_file.close();
  }
  else cout << "Unable to open file y_pred_py.csv"; 

#ifdef kernel_linear
double y_p=0;
//calcolo y_pred
for ( i = 0; i < n_sv; ++i)
{
  y_p=lambda[i]*sv_y[i]*prodotto_scalare(X_test[0],sv_x[i])+y_p; //al posto di "prodotto scalare" generico K(x,y)
}

y_p=y_p+b;  
if (y_p >= 0) {
    y_p=1;
  }
else { y_p = -1;}


for (i = 0; i < n_test; ++i)
{
  y_pred[i]=0;
  for ( j = 0; j < n_sv; ++j)
  {
    y_pred[i]=lambda[j]*sv_y[j]*prodotto_scalare(X_test[i],sv_x[j])+y_pred[i]; //al posto di "prodotto scalare" generico K(x,y)

  }
  y_pred[i]=y_pred[i]+b;
 

if (y_pred[i] >= 0) {
    y_pred[i]=1;
  }
else { y_pred[i] = -1;}

}
#endif


#ifdef kernel_poly
double y_p=0;
//calcolo y_pred
for ( i = 0; i < n_sv; ++i)
{
  y_p=lambda[i]*sv_y[i]*K_poly(X_test[0],sv_x[i],gamma,deg)+y_p; // Kernel polinomiale
}

y_p=y_p+b;  
if (y_p >= 0) {
    y_p=1;
  }
else { y_p = -1;}


for (i = 0; i < n_test; ++i)
{
  y_pred[i]=0;
  for ( j = 0; j < n_sv; ++j)
  {
    y_pred[i]=lambda[j]*sv_y[j]*K_poly(X_test[i],sv_x[j],gamma,deg)+y_pred[i]; //Kernel polinomiale
  
  }

 
  y_pred[i]=y_pred[i]+b; 

if (y_pred[i] >= 0) {
    y_pred[i]=1;
  }
else { y_pred[i] = -1;}
}
#endif



//confronto con y_pred da y_pred_python
for ( i = 0; i < n_test; ++i)
{
  if (y_pred[i] != y_pred_py[i])
  {
    cout << "ERRORE" << i << endl;
  }
}



return 0;
}
