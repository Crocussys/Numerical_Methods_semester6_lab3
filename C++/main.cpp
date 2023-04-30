#include <iostream>
#include <cmath>
#include "matrix.h"

using namespace std;

Matrix f(Matrix* x){
    double x1 = x->get_val(0, 0);
    double x2 = x->get_val(1, 0);
    double temp[2] = {pow(x1, 3) - pow(x2, 2) - 1, x1 * pow(x2, 3) - x2 - 4};
    Matrix ans(2, temp);
    return ans;
}

Matrix jacobi_1(Matrix* x){
    double x1 = x->get_val(0, 0);
    double x2 = x->get_val(1, 0);
    double determ = 9 * pow(x1, 3) * pow(x2, 2) - 3 * pow(x1, 2) + 2 * pow(x2, 4);
    Matrix ans(2, 2);
    ans.set_val(0, 0, (3 * pow(x2, 2) * x1 - 1) / determ);
    ans.set_val(0, 1, 2 * x2 / determ);
    ans.set_val(1, 0, -pow(x2, 3) / determ);
    ans.set_val(1, 1, 3 * pow(x1, 2) / determ);
    return ans;
}

bool is_end(Matrix* x_prev, Matrix* x, Matrix* fx, double err1 = 1e-9, double err2 = 1e-9){
    double delta1 = 0;
    double delta2 = 0;
    for (int i = 0; i < fx->size()[0]; i++){
        double val = abs(fx->get_val(i ,0));
        if (val > delta1){
            delta1 = val;
        }
    }
    for (int i = 0; i < x->size()[0]; i++){
        double val;
        double elem = x->get_val(i, 0);
        if (abs(elem) < 1){
            val = abs(elem - x_prev->get_val(i, 0));
        }else{
            val = abs(1 - x_prev->get_val(i, 0) / elem);
        }
        if (val > delta2){
            delta2 = val;
        }
    }
    cout << "delta1 = " << delta1 << " delta2 = " << delta2 << endl;
    if (delta1 > err1){
        return false;
    }
    if (delta2 > err2){
        return false;
    }
    return true;
}

int main(){
    cout.precision(17);
    double x0[2] = {1.2, 1.3};
    Matrix x(2, x0);
    cout << "0: " << x << endl;
    int i = 1;
    Matrix fx = f(&x);
    Matrix x_next = x - jacobi_1(&x) * fx;
    cout << "1: " << x_next << " ";
    while (!is_end(&x, &x_next, &fx) and i <= 1000){
        x = x_next;
        fx = f(&x);
        x_next = x - jacobi_1(&x) * fx;
        i++;
        cout << i << ": " << x_next << " ";
    }
    cout << "Answer " << x_next << endl;
    return 0;
}