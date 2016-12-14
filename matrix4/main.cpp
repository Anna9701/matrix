#include "matrix.h"
#define SIZE 2
#include <time.h>
#include <cstdlib>


int main(){

    srand(time(NULL));

    double **y = new double*[SIZE];
    for(int i=0; i < SIZE; i++)
        y[i] = new double[SIZE];
    Matrix A(2, 2);
    for(int i = 0; i < SIZE; i++)
        for(int j=0; j < SIZE; j++){
            y[i][j] = rand() % 400 / 2.34;
            cout << y[i][j] << endl;
        }

   Matrix C(SIZE, SIZE, y);
   cout << A;
   cout << C;

   Matrix B = C;

   cout << B;
   A = C;
   cout << A;
   double x = A(0, 1);
   cout << x << endl;
   B(0, 1) = 5.34;
    cout << A;
    cout << B;
    for(int i=0; i < SIZE; i++)
        delete [] y[i];
    delete []y;
    return 0;
}
