/*************************************************************************
	> File Name: lay.h
	> Author: 
	> Mail: 
	> Created Time: 2018年05月12日 星期六 14时22分43秒
 ************************************************************************/

#ifndef _LAY_H
#define _LAY_H
#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include "hanshu.h"
class Poollayer;
class Layer {
public:
    int row, col;
    float *a;
    float **w, *b, **w_, *b_, **w_sum, *b_sum;
    Layer(int row) : row(row), col(0), w(nullptr), b(nullptr), w_(nullptr), b_(nullptr), w_sum(nullptr), b_sum(nullptr){
        a = new float[row];
    }

    Layer(int row, int col): row(row), col(col) {
        a = new float[row];
        w = new float *[row];
        for (int i = 0; i < row; i++) {
            w[i] = new float[col];
        }
        w_ = new float *[row];
        for (int i = 0; i < row; i++) {
            w_[i] = new float[col];
        }
        w_sum = new float *[row];
        for (int i = 0; i < row; i++) {
            w_sum[i] = new float[col];
        }
        b = new float[row];
        b_ = new float[row];
        b_sum = new float[row];
       // printf("ok\n");
    }
    ~Layer() {
        if (this -> col == 0) {
            delete [] a;
            return;
        }
        else {
            delete [] a;
            delete [] b;
            delete [] b_;
            delete [] b_sum;
            for (int i = 0; i < row; i++) {
                delete[] w[i];
                delete[] w_[i];
                delete [] w_sum[i];
            }
            delete[] w;
            delete[] w_;
            delete[] w_sum;
        }
    }
    void init() {
        srand((unsigned)time(NULL));
        if (this -> col == 0) {
            return ;
        }
        else {
            for (int i = 0; i < row; i++) {
                b[i] = rand() / float(RAND_MAX) - 0.5;
              //  b[i] = rand() / float(RAND_MAX);
                b_[i] = 0;
                b_sum[i] = 0;
                for (int j = 0; j < col; j++) {
                    w[i][j] = rand() / float(RAND_MAX) - 0.5;
                //    w[i][j] = rand() % 10;
                    w_[i][j] = 0;
                    w_sum[i][j] = 0;
                }
            }
        }
        
    }
    void output() {
        printf("w = \n");
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                printf ("%f ", w[i][j]);
            }
            printf ("\n");
        }
        printf("\nw_ = \n");
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                printf ("%f ", w_[i][j]);
            }
            printf ("\n");
        }
        printf ("\nb = \n");
        for (int i = 0; i < row; i++) {
            printf ("%f ", b[i]); 
        }
        printf ("\nb_ = \n"); 
        for (int i = 0; i < row; i++) {
            printf ("%f ", b_[i]);
        }
        printf ("\na = \n");
        for (int i = 0; i < row; i++) {
            printf ("%f ", a[i]);
        }
        printf ("\n");
    }
    void output_a() {
        for (int i = 0; i < row; i++) {
            printf ("%f ", this -> a[i]);
        }
        printf ("\n");
    }
    void output_b_() {
        for (int i = 0; i < row; i++) {
            printf ("%f ", this -> b_[i]);
        }
        printf ("\n");
    }
};

Layer& operator >> (Layer &l1, Layer &l2) {
    for (int i = 0; i < l2.row; i++) {
        float sum = 0;
        for (int j = 0; j < l2.col; j++) {
            sum += l1.a[j] * l2.w[i][j];
        }
        float temp = sum + l2.b[i];
        l2.a[i] = s(temp);
    }
    return l2;
}
Layer& operator > (Layer &l1, Layer &l2) {
    float e_sum = 0;
    for (int i = 0; i < l2.row; i++) {
        float sum = 0;
        for (int j = 0; j < l2.col; j++) {
            sum += l1.a[j] * l2.w[i][j];
        }
        float temp = sum + l2.b[i];
     //   printf ("temp = %f\n", temp);
        l2.a[i] = pow(e, temp);
        e_sum += l2.a[i];
    //    printf ("l2.a[%d] = %f\n", i, l2.a[i]);
    }
  //  int a;
  //  scanf("%d", &a);
    for (int i = 0; i < l2.row; i++) {
        l2.a[i] /= e_sum;
       // printf ("%f\n", e_sum);
      //  printf ("%f ", l2.a[i]);
    }
    
    return l2;
}
/*Layer& operator > (Layer &l1, Layer &l2) {
    for (int i = 0; i < l2.row; i++) {
        float sum = 0;
        for (int j = 0; j < l2.col; j++) {
            sum += l1.a[j] * l2.w[i][j];
        }
        l2.a[i] = sum + l2.b[i];
    }
    return l2;
}*/
void count_layer3(Layer &l2, Layer &l1, float* y) {
    float sum_w = 0;
    for (int i = 0; i < l2.row; i++) {
        for (int j = 0; j < l2.col; j++) {
            sum_w += l2.w[i][j];
        }
    }
    for (int i = 0; i < l2.row; i++) {
        l2.b_[i] = (l2.a[i] - y[i]);
        l2.b_sum[i] += l2.b_[i];
        for (int j = 0; j < l2.col; j++) {
            l2.w_[i][j] = (l1.a[j] * (l2.b_[i]) + R * sum_w);
            l2.w_sum[i][j] += l2.w_[i][j];
        }
    }
    return;
}  
/*void count_layer3(Layer &l2, Layer &l1, float* y) {
    for (int i = 0; i < l2.row; i++) {
        l2.b_[i] = 2 * (l2.a[i] - y[i]);
        l2.b_sum[i] += l2.b_[i];
        for (int j = 0; j < l2.col; j++) {
            l2.w_[i][j] = (l1.a[j] * 2 * (l2.a[i] - y[i]) + R * l2.w[i][j]);
            l2.w_sum[i][j] += l2.w_[i][j];
        }
    }
    return;
} */

void count_layer2(Layer& l2, Layer& l3, Layer& l1) {
    for (int i = 0; i < l2.row; i++) {
        float sum = 0;
        for (int j = 0; j < l3.row; j++) {
            sum += (l3.w[j][i] * l3.b_[j]);
        }
        l2.b_[i] = (sum * l2.a[i] * (1.0 - l2.a[i]));
        l2.b_sum[i] += l2.b_[i];
        for (int j = 0; j < l2.col; j++) {
            l2.w_[i][j] = (l1.a[j] * l2.b_[i]);
            l2.w_sum[i][j] += l2.w_[i][j];
        }
    }
    return;
}
void update(Layer& l) {
    for (int i = 0; i < l.row; i++) {
        l.b[i] -= (rate / M * l.b_sum[i]);
        l.b_sum[i] = 0;
        for (int j = 0; j < l.col; j++) {
            l.w[i][j] -= (rate / M * l.w_sum[i][j]);
            l.w_sum[i][j] = 0;
        }
    }
    return;
}
void set_zero(Layer& l) {
    for (int i = 0; i < l.row; i++) {
        l.b_sum[i] = 0;
        for (int j = 0; j < l.col; j++) {
            l.w_sum[i][j] = 0;
        }
    }
    return;
}  
#endif
