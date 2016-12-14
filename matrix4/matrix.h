#ifndef MATRIX_H
    #define MATRIX_H

    #include <iostream>
    #include <cmath>
    #include <fstream>
    #include <string>
    #define DEFAULT 5
    using namespace std;

    class Matrix{
        private:
            struct rcmatrix;
            rcmatrix* data;
        public:
            class Badsize{};
            class Cref;

            Matrix(int, int, double**);
            Matrix(const Matrix&);
            Matrix(const int, const int);
            ~Matrix();

            Matrix& operator= (const Matrix &);
           // Matrix& operator= (double**);

            Matrix operator+(const Matrix&)const;
            Matrix operator-(const Matrix&)const;
            Matrix operator*(const Matrix&)const;

            Matrix& operator+=(const Matrix&);
            Matrix& operator-=(const Matrix&);
            Matrix& operator*=(const Matrix&);

            bool operator== (const Matrix &) const;
            friend ostream& operator<< (ostream&, const Matrix &);

            Matrix& wczytaj(const string, int, int);

            double read (int, int) const;
            void write (int, int, double);

            double operator() (int, int) const;
            Cref operator()(int, int);

    };

    struct Matrix::rcmatrix{
        double** dane;
        int wiersze;
        int kolumny;
        int licznik;

        rcmatrix(int i, int j, double** m){
            wiersze =  i;
            kolumny = j;

            licznik = 1;
            dane = new double* [wiersze];
            for(int a=0; a < wiersze; a++)
                dane[a] = new double[kolumny];
            for(int x = 0; x < wiersze; x++)
                for(int y=0; y < kolumny; y++)
                    dane[x][y] = m[x][y];
        }
        rcmatrix(int i, int j){
            wiersze = i;
            kolumny = j;
            licznik = 1;
            dane = new double*[wiersze];
            for(int a=0; a < wiersze; a++)
                dane[a] = new double[kolumny];
            for(int x=0; x < wiersze; x++)
                for(int y=0; y < kolumny; y++)
                    dane[x][y] = 0;
        }

        ~rcmatrix(){
            for(int i=0; i < wiersze; i++)
                delete [] dane[i];
            delete [] dane;
        }

        rcmatrix* detach(){
            if(licznik==1)
                return this;
            rcmatrix* n = new rcmatrix(wiersze, kolumny, dane);
            licznik--;
            return n;
        }
        void assign(int i, int j, double** m){
            if(i != wiersze || j != kolumny){
                double** nm = new double*[wiersze];
                for(int a=0; a < wiersze; a++)
                    nm[a] = new double[kolumny];
                for(int x = 0; x < wiersze; x++)
                    for(int y=0; y < kolumny; y++)
                        nm[x][y] = m[x][y];
                for(int i=0; i < wiersze; i++)
                    delete [] dane[i];
                delete [] dane;
                dane = nm;
            }else{
                for(int x = 0; x < wiersze; x++)
                    for(int y=0; y < kolumny; y++)
                        dane[x][y] = m[x][y];
           }
        }
    private:
        rcmatrix(const rcmatrix&);
        rcmatrix& operator=(const rcmatrix&);
    };

    class Matrix::Cref{
        friend class Matrix;
        Matrix& m;
        int i, j;

        Cref(Matrix& mm, int ii, int jj) : m(mm), i(ii), j(jj) {};

    public:
        operator double() const { return m.read(i, j); }
        Matrix::Cref& operator= (double x){
            m.write(i, j, x);
            return *this;
        }
        Matrix::Cref& operator= (const Cref& ref) { return operator= ((double)ref); }
    };

   #endif
