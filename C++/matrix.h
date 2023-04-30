#include <iostream>

using namespace std;

class Matrix{
private:
    unsigned int n;
    unsigned int m;
    double** arr;

    void del_arr();

public:
    Matrix();
    Matrix(unsigned int n_, double* arr_);
    Matrix(unsigned int n_, unsigned int m_);
    ~Matrix();

    unsigned int* size();
    double get_val(unsigned int i, unsigned int j);
    void set_val(unsigned int i, unsigned int j, double val);
    void transpose();
    Matrix copy();

    Matrix& operator=(const Matrix& other);
    const Matrix operator*(double num);
    const Matrix operator/(double num);
    const Matrix operator+(const Matrix& other);
    const Matrix operator-(const Matrix& other);
    const Matrix operator*(const Matrix& other);
    friend ostream& operator<<(ostream& out, const Matrix&);
};