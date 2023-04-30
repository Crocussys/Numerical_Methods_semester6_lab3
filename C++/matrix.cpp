#include "matrix.h"

Matrix::Matrix(){
    n = 0;
    m = 0;
    arr = nullptr;
}
Matrix::Matrix(unsigned int n_, double* arr_){
    n = n_;
    m = 1;
    arr = new double*[n];
    for (int i = 0; i < n; i++){
        arr[i] = new double[1];
        arr[i][0] = arr_[i];
    }
}
Matrix::Matrix(unsigned int n_, unsigned int m_){
    n = n_;
    m = m_;
    arr = new double*[n];
    for (int i = 0; i < n; i++){
        arr[i] = new double[m];
        for (int j = 0; j < m; j++){
            arr[i][j] = 0;
        }
    }
}
Matrix::~Matrix(){}
void Matrix::del_arr(){
    for (int i = 0; i < n; i++){
        delete[] arr[i];
    }
    arr = nullptr;
}
unsigned int* Matrix::size(){
    unsigned int* ans = new unsigned int[2];
    ans[0] = n;
    ans[1] = m;
    return ans;
}
double Matrix::get_val(unsigned int i, unsigned int j){
    if (i < n and j < m){
        return arr[i][j];
    }else{
        throw;
    }
}
void Matrix::set_val(unsigned int i, unsigned int j, double val){
    if (i < n and j < m){
        arr[i][j] = val;
    }else{
        throw;
    }
}
void Matrix::transpose(){
    double** new_arr = new double*[m];
    for (int i = 0; i < m; i++){
        new_arr[i] = new double[n];
        for (int j = 0; j < n; j++){
            new_arr[i][j] = arr[j][i];
        }
    }
    del_arr();
    unsigned int temp = n;
    n = m;
    m = temp;
    arr = new_arr;
}
Matrix Matrix::copy(){
    Matrix new_mtrx(n, m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            new_mtrx.set_val(i, j, arr[i][j]);
        }
    }
    return new_mtrx;
}
Matrix& Matrix::operator=(const Matrix& other){
    del_arr();
    n = other.n;
    m = other.m;
    arr = new double*[n];
    for (int i = 0; i < n; i++){
        arr[i] = new double[m];
        for (int j = 0; j < m; j++){
            arr[i][j] = other.arr[i][j];
        }
    }
    return *this;
}
const Matrix Matrix::operator*(double num){
    Matrix ans(n, m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            ans.set_val(i, j, arr[i][j] * num);
        }
    }
    return ans;
}
const Matrix Matrix::operator/(double num){
    Matrix ans(n, m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            ans.set_val(i, j, arr[i][j] / num);
        }
    }
    return ans;
}
const Matrix Matrix::operator+(const Matrix& other){
    if (n != other.n or m != other.m){
        throw;
    }
    Matrix ans(n, m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            ans.set_val(i, j, arr[i][j] + other.arr[i][j]);
        }
    }
    return ans;
}
const Matrix Matrix::operator-(const Matrix& other){
    if (n != other.n or m != other.m){
        throw;
    }
    Matrix ans(n, m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            ans.set_val(i, j, arr[i][j] - other.arr[i][j]);
        }
    }
    return ans;
}
const Matrix Matrix::operator*(const Matrix& other){
    if (m != other.n){
        throw;
    }
    Matrix ans(n, other.m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < other.m; j++){
            double sum = 0;
            for (int k = 0; k < m; k++){
                sum += arr[i][k] * other.arr[k][j];
            }
            ans.set_val(i, j, sum);
        }
    }
    return ans;
}
ostream& operator<<(ostream& out, const Matrix& mtrx){
    out << '[';
    if (mtrx.m == 1){
        for (int i = 0; i < mtrx.n; i++){
            out << mtrx.arr[i][0];
            if (i != mtrx.n - 1){
                out << "; ";
            }
        }
    }else{
        for (int i = 0; i < mtrx.n; i++){
            out << '[';
            for (int j = 0; j < mtrx.m; j++){
                out << mtrx.arr[i][j];
                if (j != mtrx.m - 1){
                    out << "; ";
                }
            }
            out << ']';
            if (i != mtrx.n - 1){
                out << endl;
            }
        }
    }
    out << ']';
    return out;
}