#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include "prodotto_scalare.h"

#define dim_w 30
#define n_test 171
#define n_feature 30


using namespace std;

int main()
{


 
  string line;
  double w[dim_w];
  double b;
  double X_test[n_test][n_feature];
  //int y_test[n_test];
  int y_pred_py[n_test];

  //acquisisco W e b ottenuti dall'addestramento python
  ifstream W_file;
  W_file.open("W.csv");
  int i=0;
  if (W_file.is_open())
  {
    while ( getline (W_file,line) )
    {
      sscanf(line.c_str(),"%lf",&w[i]);
      i++;
    }
    W_file.close();
  }
  else cout << "Unable to open file W"; 

  ifstream b_file;
  b_file.open("b.csv");
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

//acquisisco X_test y_pred_py
  ifstream X_test_file;
  X_test_file.open("X_test.csv");

  int j=0;
  i=0;
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


  ifstream y_pred_py_file;
  y_pred_py_file.open("y_pred_py.csv");
  i=0;
  if (y_pred_py_file.is_open())
  {
    while ( getline (y_pred_py_file,line) )
    {
      sscanf(line.c_str(),"%d",&y_pred_py[i]);
      i++;
    }
    y_pred_py_file.close();
  }
  else cout << "Unable to open file y_pred_py.csv"; 

 
//CALCOLO YPRED

double y_pred[n_test];

for ( i = 0; i < n_test; ++i)
{
  y_pred[i]=prodotto_scalare(X_test[i],w) + b;
  if (y_pred[i] >= 0) {
    y_pred[i]=1;
  }
  else { y_pred[i] = -1;}

}

//confronto con y_pred da python
for ( i = 0; i < n_test; ++i)
{
  if (y_pred[i] != y_pred_py[i])
  {
    cout << "ERRORE" << i << endl;
  }
}

return 0;
}






