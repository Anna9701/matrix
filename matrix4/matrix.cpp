#include "matrix.h"

Matrix::Matrix(int i, int j, double** macierz){
    try{
      data = new rcmatrix(i, j, macierz);
    }catch(const ErMake *s){
      cout << "Blad tworzenia macierzy" << endl;
      delete data;
    }
}

Matrix::Matrix(const Matrix &macierz){
    macierz.data->licznik++;
    data = macierz.data;
}

Matrix::Matrix(const int i, const int j){
    try{
	data = new rcmatrix(i, j);
    }catch (const ErMake *s){
        cout << "Blad tworzenia macierzy" << endl;
	delete data;
}

Matrix::~Matrix(){
    if(--data->licznik == 0)
        delete data;
}

Matrix& Matrix::operator= (const Matrix& macierz){
	macierz.data->licznik++;
	if(--data->licznik == 0)
		delete data;
	data = macierz.data;
	
	return *this;
}

/*Matrix& Matrix::operator= (double** macierz){
    if(data->licznik == 1){
        rcmatrix *t = new rcmatrix(i, j, macierz);
		data = t; 
	}else{
        rcmatrix *t = new rcmatrix(macierz);
		data->licznik--;
		data = t;
	}
	return *this;	
}*/

Matrix Matrix::operator+(const Matrix& macierz) const{
	Matrix wynik(data->wiersze, data->kolumny);  
	if(data->wiersze == macierz.data->wiersze && data->kolumny == macierz.data->kolumny)
		for(int i=0; i < data->wiersze; i++)
			for(int j=0; j < data->kolumny; j++)
				wynik.data->dane[i][j] = data->dane[i][j] + macierz.data->dane[i][j];

	return wynik;
}

Matrix Matrix::operator-(const Matrix& macierz) const{
	Matrix wynik(data->wiersze, data->kolumny);
	if(data->wiersze == macierz.data->wiersze && data->kolumny == macierz.data->kolumny)
		for(int i=0; i < data->wiersze; i++)
			for(int j=0; j < data->kolumny; j++)
				wynik.data->dane[i][j] = data->dane[i][j] - macierz.data->dane[i][j];

	return wynik;
}

Matrix Matrix::operator*(const Matrix& macierz) const{
	Matrix wynik(data->wiersze, macierz.data->kolumny);

	if(data->kolumny == macierz.data->wiersze){
		for(int i=0; i < data->wiersze; i++)
			for(int j=0; j < macierz.data->kolumny; j++){
				wynik.data->dane[i][j] = 0;
				for(int r=0; r < data->kolumny; r++)
					wynik.data->dane[i][j] += data->dane[i][r]*macierz.data->dane[r][j];
			}
	}
	
	return wynik;
}


Matrix& Matrix::operator+=(const Matrix &macierz){
    int i = data->wiersze;
    int j = data->kolumny;

        if(i != macierz.data->wiersze || j != macierz.data->kolumny)
            ;//blad;
        rcmatrix *newdata = new rcmatrix(i, j, data->dane);
            for(int a = 0; a < i; a++)
                for(int b = 0; b < j; b++)
                   newdata->dane[i][j] += macierz.data->dane[i][j];


        if(--data->licznik == 0)
            delete data;
        data = newdata;

        return *this;

}

Matrix& Matrix::operator-=(const Matrix &macierz){
    int i = data->wiersze;
    int j = data->kolumny;

    if(i != macierz.data->wiersze || j != macierz.data->kolumny)
        ;//blad;
    rcmatrix *newdata = new rcmatrix(i, j, data->dane);
        for(int a = 0; a < i; a++)
            for(int b = 0; b < j; b++)
               newdata->dane[i][j] -= macierz.data->dane[i][j];


    if(--data->licznik == 0)
        delete data;
    data = newdata;

    return *this;
}

Matrix& Matrix::operator*=(const Matrix &macierz){
    int i = data->wiersze;
    int j = data->kolumny;

    if(j!=macierz.data->wiersze)
        ;//blad
    rcmatrix *newdata = new rcmatrix(i, macierz.data->kolumny);
        for(int a=0; a < i; a++)
                for(int b=0; b < macierz.data->kolumny; b++){
                    newdata->dane[a][b] = 0;
                    for(int r=0; r < j; r++)
                        newdata->dane[a][b] += data->dane[i][r]*macierz.data->dane[r][j];
                }

    if(--data->licznik == 0)
        delete data;

    data = newdata;

    return *this;
}

bool Matrix::operator== (const Matrix &macierz)const{
	if(data == macierz.data)
		return true;
	else
		return false;
}

ostream& operator<< (ostream& os, const Matrix& macierz){
    int w = macierz.data->wiersze;
    int k = macierz.data->kolumny;

    for(int i=0; i < w; i++){
        for(int j=0; j < k; j++){
            cout << macierz(i, j) << " ";
        }
        cout << endl;
    }

    return os;
}

double Matrix::operator ()(int i, int j)const{
    double x;

    x = data->dane[i][j];

    return x;
}

Matrix::Cref Matrix::operator ()(int i, int j){
    return Cref(*this, i, j);
}

Matrix& Matrix::wczytaj(const string s, int i, int j){
    ifstream plik;
    double **tab = new double* [i];
    for(int a=0; a < i; a++)
        tab[a] = new double [j];

    plik.open(s, ios::in);
       if( !plik.good() )
            ;//blad;

    for(int a=0; a < i; a++)
       for(int b=0; b < j; b++)
      //     fscanf (plik, "%lf", tab[i][j]);

    plik.close();

    rcmatrix *newdata = new rcmatrix(i, j, tab);

    if(--data->licznik == 0)
        delete data;

    data = newdata;

    return *this;
}

double Matrix::read(int i, int j)const{
    return data->dane[i][j];
}

void Matrix::write(int i, int j, double x){
    data = data->detach();
    data->dane[i][j] = x;
}
