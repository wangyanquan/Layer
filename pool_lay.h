/*************************************************************************
	> File Name: pool_lay.h
	> Author: 
	> Mail: 
	> Created Time: 2018年05月29日 星期二 09时21分08秒
 ************************************************************************/

#ifndef _POOL_LAY_H
#define _POOL_LAY_H
#include "convolution_lay.h"
//#include "hanshu.h"
#include "lay.h"
#include <cstring>

class Conlayer;
//class Conlayer::out_num;

class Poollayer {
public:
    float ***out, ***o;
    int out_num, out_row, out_col;
    int row_div, col_div;
    Poollayer(int num, int row, int col, int div_r, int div_c) : out_num(num), out_row(row), out_col(col), row_div(div_r), col_div(div_c) {
        
        out = new float**[out_num];
        for (int i = 0; i < out_num; i++) {
            out[i] = new float*[out_row];
            for (int j = 0; j < out_row; j++) {
                out[i][j] = new float[out_col];
            }
        }

        o = new float**[out_num];
        for (int i = 0; i < out_num; i++) {
            o[i] = new float*[out_row];
            for (int j = 0; j < out_row; j++) {
                o[i][j] = new float[out_col];
            }
        }
    }
    ~Poollayer() {
        for (int i = 0; i < out_num; i++) {
            for (int j = 0; j < out_row; j++) {
                delete[] out[i][j];
            }
            delete[] out[i];
        }
        delete[] out;
    }
    void output_out() {
        for (int i = 0; i < this -> out_num; i++) {
            for (int j = 0; j < this -> out_row; j++) {
                for (int k = 0; k < this -> out_col; k++) {
                    printf ("%f ", this -> out[i][j][k]);
                }
                printf ("\n");
            }
        }
    }
    void output_o() {
        for (int i = 0; i < this -> out_num; i++) {
            for (int j = 0; j < this -> out_row; j++) {
                for (int k = 0; k < this -> out_col; k++) {
                    printf ("%f ", this -> o[i][j][k]);
                }
                printf ("\n");
            }
        }
        printf ("\n");
    }
};
int find_num(Poollayer& l, int num) {
    return (int)(num / (l.out_row * l.out_col));
}
int find_x(Poollayer& l, int num) {
    num -= (l.out_row * l.out_col * find_num(l, num));
    return (int)(num / l.out_col);
}
int find_y(Poollayer& l, int num) {
    num -= (l.out_row * l.out_col * find_num(l, num) + l.out_col * find_x(l, num));
    return (int)(num);
} 
Layer& operator > (Poollayer& l1, Layer& l2) {
    for (int i = 0; i < l2.row; i++) {
        float sum = 0;
        for (int j = 0; j < l2.col; j++) {
            int n = find_num(l1, j);
            int x = find_x(l1, j);
            int y = find_y(l1, j);
          //  printf ("l1.out[n][x][y] = %f, l2,w[i][j] = %f\n", l1.out[n][x][y], l2.w[i][j]);
            sum += (l1.out[n][x][y] * l2.w[i][j]);
        }
        sum += l2.b[i];
        l2.a[i] = s(sum);
    }
    return l2;
}
void count_layer2(Layer& l2, Layer& l3, Poollayer& l1) {
    for (int i = 0; i < l2.row; i++) {
        float sum = 0;
        for (int j = 0; j < l3.row; j++) {
            sum += (l3.w[j][i] * l3.b_[j]);
        }
     //   printf ("%f ", sum);
     //   printf ("%f ", l2.a[i]);
        l2.b_[i] = (sum * l2.a[i] * (1.0 - l2.a[i]));
        l2.b_sum[i] += l2.b_[i];
        for (int j = 0; j < l2.col; j++) {
            int n = find_num(l1, j);
            int x = find_x(l1, j);
            int y = find_y(l1, j);
            l2.w_[i][j] = (l1.out[n][x][y] * l2.b_[i]);
            l2.w_sum[i][j] += l2.w_[i][j];
      }
    }
    return;
}
#endif
