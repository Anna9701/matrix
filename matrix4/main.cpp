#include "matrix.h"
#define SIZE 2
#include <time.h>
#include <cstdlib>


int main(){
   Matrix X(2, 2); 
   Matrix C(X), B(C); 
   
   C(1, 0) = 2.43; 
   X += C; 
   B += X + C;
   cout << "X\n" << X << "\nC\n" << C << "\nB\n" << B << endl;   


Matrix N(2, 2);
N.wczytaj("dane.txt", 2, 2);
cout << N;
Matrix test1 = N, test2 = N;
Matrix test3("dane.txt", 2, 2);
Matrix test4 = test1;
Matrix test5 = test1;
Matrix test6 = test2;

return 0;
}

