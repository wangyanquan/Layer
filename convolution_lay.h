/*************************************************************************
	> File Name: convolution_lay.h
	> Author: 
	> Mail: 
	> Created Time: 2018年05月28日 星期一 11时04分47秒
 ************************************************************************/

#ifndef _CONVOLUTION_LAY_H
#define _CONVOLUTION_LAY_H

#pragma once

#include "hanshu.h"
#include "pool_lay.h"
#include <cstring>

float juanji(float** out, float** w, int row, int col, int i1, int j1);
float relu(float);
float relu_(float);
void set_o(float**, float**, int, int, int, int);
void set_w(float**, float**, int, int);
float** alloc(int, int);
void mem(float**m, int, int);
void del(float**, int, int);
class Conlayer {
public:
    float ***out, ***o, ***mark;
    int out_num, out_row, out_col;

    float ****w;
    int w_num, w_row, w_col;

    float *b;

    float ****w_, ****w_sum;
    float *b_, *b_sum;

    Conlayer (int num, int row, int col) : out_num(num), out_row(row), out_col(col) {
        out = nullptr;
        o = nullptr;
        mark = nullptr;
        w = nullptr;
        w_num = 0;
        w_row = 0;
        w_col = 0;
        b = nullptr;
        w_ = nullptr;
        w_sum = nullptr;
        b_ = nullptr;
        b_sum = nullptr;
        
        out = new float**[out_num];
        for (int i = 0; i < out_num; i++) {
            out[i] = new float*[out_row];
            for (int j = 0; j < out_row; j++) {
                out[i][j] = new float[out_col];
            }
        }
    }
    Conlayer (int num1, int row1, int col1, int num2, int row2, int col2) {
        out_num = num1;
        w_num = num2;
        out_row = row1;
        out_col = col1;
        w_row = row2;
        w_col = col2;
        
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

        mark = new float**[out_num];
        for (int i = 0; i < out_num; i++) {
            mark[i] = new float*[out_row];
            for (int j = 0; j < out_row; j++) {
                mark[i][j] = new float[out_col];
            }
        }

        w = new float***[out_num];
        for (int i = 0; i < out_num; i++) {
            w[i] = new float**[w_num];
            for (int j = 0; j < w_num; j++) {
                w[i][j] = new float*[w_row];
                for (int k = 0; k < w_row; k++) {
                    w[i][j][k] = new float[w_col];
                }
            }
        }
        w_ = new float***[out_num];
        for (int i = 0; i < out_num; i++) {
            w_[i] = new float**[w_num];
            for (int j = 0; j < w_num; j++) {
                w_[i][j] = new float*[w_row];
                for (int k = 0; k < w_row; k++) {
                    w_[i][j][k] = new float[w_col];
                }
            }
        }
        w_sum = new float***[out_num];
        for (int i = 0; i < out_num; i++) {
            w_sum[i] = new float**[w_num];
            for (int j = 0; j < w_num; j++) {
                w_sum[i][j] = new float*[w_row];
                for (int k = 0; k < w_row; k++) {
                    w_sum[i][j][k] = new float[w_col];
                }
            }
        }
        
        b = new float[out_num];
        b_ = new float[out_num];
        b_sum = new float[out_num];

    }
    ~Conlayer() {
        if (this -> w_num == 0) {
            for (int i = 0; i < out_num; i++) {
                for (int j = 0; j < out_row; j++) {
                    delete[] out[i][j];
                }
                delete[] out[i];
            }
            delete[] out;
        }else {
            for (int i = 0; i < out_num; i++) {
                for (int j = 0; j < out_row; j++) {
                    delete[] out[i][j];
                    delete[] o[i][j];
                    delete[] mark[i][j];
                }
                delete[] out[i];
                delete[] o[i];
                delete[] mark[i];
            }
            delete[] out;
            delete[] o;
            delete[] mark;
            
            for (int i = 0; i < out_num; i++) {
                for (int j = 0; j < w_num; j++) {
                    for (int k = 0; k < w_row; k++) {
                        delete[] w[i][j][k];
                        delete[] w_[i][j][k];
                        delete[] w_sum[i][j][k];
                    }
                    delete[] w[i][j];
                    delete[] w_[i][j];
                    delete[] w_sum[i][j];
                } 
                delete[] w[i];
                delete[] w_[i];
                delete[] w_sum[i];
            }
            delete[] w;
            delete[] w_;
            delete[] w_sum;
            
            delete[] b;
            delete[] b_;
            delete[] b_sum;
        }
    }  
    void init() {
        srand((unsigned)time(NULL)); 
        if (this -> w_num == 0) {
            return;
        }else {
            for (int i = 0; i < out_num; i++) {
                b[i] = rand() / float(RAND_MAX) - 0.5;
                b_[i] = 0;
                b_sum[i] = 0;
                for (int j = 0; j < w_num; j++) {
                    for (int k = 0; k < w_row; k++) {
                        for (int l = 0; l < w_col; l++) {
                            w[i][j][k][l] = rand() / float(RAND_MAX) - 0.5;
                            w_[i][j][k][l] = 0;
                            w_sum[i][j][k][l] = 0; 
                        }
                    }
                }
            }
        }
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
    void output_mark() {
        for (int i = 0; i < this -> out_num; i++) {
            for (int j = 0; j < this -> out_row; j++) {
                for (int k = 0; k < this -> out_col; k++) {
                    printf ("%d ", (int)this -> mark[i][j][k]);
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
void read_con(FILE *f, Conlayer& l) {
    int x, y, zu;
    for (int i = 0; i < 2500; i++) {
        zu = i / 2500;
        x = i / 50;
        y = i - zu * 2500 - x * 50;
        fscanf(f, "%f", &l.out[zu][x][y]);
    }
}
//在卷积传递到池化中找范围内的最大值，使用最大传播法
float find_max(Conlayer& l, int n, int x, int y, int row_div, int col_div) {
    float temp = l.out[n][x][y];
    int i_mark = x, j_mark = y;
    for (int i = x; i < x + row_div; i++) {
        for (int j = y; j < y + col_div; j++) {
            if (l.out[n][i][j] > temp) {
                i_mark = i;
                j_mark = j;
                temp = l.out[n][i][j];
            }
        }
    }
    l.mark[n][i_mark][j_mark] = 1;
    return temp;
}
//卷积到池化层
Poollayer& operator >(Conlayer& l1, Poollayer& l2) {
    for (int i = 0; i < l1.out_num; i++) {
        for (int j = 0; j < l1.out_row; j++) {
            memset(l1.mark[i][j], 0, sizeof(float) * l1.out_col);
        }
    }
  //  printf ("l1.num = %d, l1.out_row = %d, l1.out_col = %d\n", l1.out_num, l1.out_row, l1.out_col);
  //  printf ("sizeof(l1.mark) = %d\n", sizeof(l1.mark));
    int x, y;
    for (int i = 0; i < l2.out_num; i++) {
        for (int j = 0; j < l2.out_row; j++) {
            for (int k = 0; k < l2.out_col; k++) {
                x = j * l2.row_div;
                y = k * l2.col_div;
                l2.out[i][j][k] = find_max(l1, i, x, y, l2.row_div, l2.col_div);
            }
        }
    }
    return l2;
} 
//输入到卷积
Conlayer& operator > (Conlayer& l1, Conlayer& l2) {
    for (int i = 0; i < l2.out_num; i++) {
        for (int j = 0; j < l2.out_row; j++) {
            for (int k = 0; k < l2.out_col; k++) {
                float sum = 0;
                for (int x = 0; x < l2.w_num; x++) {
                    sum += juanji(l1.out[x], l2.w[i][x], l2.w_row, l2.w_col, j, k);
                }
                sum += l2.b[i];
                l2.out[i][j][k] = relu(sum);
            }
        } 
    }
    return l2;
}
//池化到卷积
Conlayer& operator > (Poollayer& l1, Conlayer& l2) {
    for (int i = 0; i < l2.out_num; i++) {
        for (int j = 0; j < l2.out_row; j++) {
            for (int k = 0; k < l2.out_col; k++) {
                float sum = 0;
                for (int x = 0; x < l2.w_num; x++) {
                    sum += juanji(l1.out[x], l2.w[i][x], l2.w_row, l2.w_col, j, k);
                }
                sum += l2.b[i];
                l2.out[i][j][k] = relu(sum);
            }
        } 
    }
    return l2;
}
void count_conlayer_pool(Conlayer& l1, Poollayer& l2) {
    int x, y;
    for (int i = 0; i < l2.out_num; i++) {
        for (int j = 0; j < l2.out_row; j++) {
            for (int k = 0; k < l2.out_col; k++) {
             //   printf ("%f ", l2.o[i][j][k]);
                x = j * l2.row_div;
                y = k * l2.col_div;
               // printf ("i == %d\n", i);
               // printf ("%d %d\n", x, y);
                for (int m = 0; m < l2.row_div; m++) {
                    for (int n = 0; n < l2.col_div; n++) {
                        l1.o[i][x + m][y + n] = l2.o[i][j][k];
                    }
                }
            }
           // printf("\n");
        }
    }
    for (int i = 0; i < l1.out_num; i++) {
        for (int j = 0; j < l1.out_row; j++) {
            for (int k = 0; k < l1.out_col; k++) {
                l1.o[i][j][k] = l1.o[i][j][k] * l1.mark[i][j][k] * relu_(l1.out[i][j][k]);
              //  printf("%d ", (int)l1.o[i][j][k]);
            }
           // printf ("\n");
        }
    }
}  
void count_wb(Conlayer& l1, Conlayer& l2) {
    for (int i = 0; i < l1.out_num; i++) {
        for (int j = 0; j < l1.w_num; j++) {
            for (int k = 0; k < l1.w_row; k++) {
                for (int l = 0; l < l1.w_col; l++){ 
                    l1.w_sum[i][j][k][l] += juanji(l2.out[j], l1.o[i], l1.out_row, l1.out_col, k, l);
                }
            }
        }
        for (int j = 0; j < l1.out_row; j++) {
            for (int k = 0; k < l1.out_col; k++) {
                l1.b_sum[i] += l1.o[i][j][k];
            }
        }
    }
}  
void count_wb(Conlayer& l1, Poollayer& l2) {
    for (int i = 0; i < l1.out_num; i++) {
        for (int j = 0; j < l1.w_num; j++) {
            for (int k = 0; k < l1.w_row; k++) {
                for (int l = 0; l < l1.w_col; l++){ 
                    l1.w_sum[i][j][k][l] += juanji(l2.out[j], l1.o[i], l1.out_row, l1.out_col, k, l);
                }
            }
        }
        for (int j = 0; j < l1.out_row; j++) {
            for (int k = 0; k < l1.out_col; k++) {
                l1.b_sum[i] += l1.o[i][j][k];
            }
        }
    }
}  
void update_wb(Conlayer &l1) {
    for (int i = 0; i < l1.out_num; i++) {
        for (int j = 0; j < l1.w_num; j++) {
            for (int k = 0; k < l1.w_row; k++) {
                for (int l = 0; l < l1.w_col; l++) {
                    l1.w[i][j][k][l] -= rate / M * l1.w_sum[i][j][k][l];
                }
            }
        }
        l1.b[i] -= rate / M * l1.b_sum[i];
    }
    for (int i = 0; i < l1.out_num; i++) {
        for (int j = 0; j < l1.w_num; j++) {
            mem(l1.w_sum[i][j], l1.w_row, l1.w_col);
        }
        
    }
    memset(l1.b_sum, 0, sizeof(float) * l1.out_num);
} 
void count_pool_layer(Poollayer& l1, Layer& l2) {
    for (int i = 0; i < l1.out_num; i++) {
        for (int j = 0; j < l1.out_row; j++) {
            for (int k = 0; k < l1.out_col; k++) {
                float sum = 0;
                int n = i * l1.out_row * l1.out_col + j * l1.out_col + k;
              //  printf ("n = %d\n", n);
                for (int l = 0; l < l2.row; l++) {
                    sum += (l2.w[l][n] * l2.b_[l]);
                }
                l1.o[i][j][k] = sum;
            }
        }
    }
}
void count_pool_con(Poollayer& l1, Conlayer& l2) {
    for (int i = 0; i < l1.out_num; i++) {
        for (int j = 0; j < l1.out_row; j++) {
            for (int k = 0; k < l1.out_col; k++) {
                float sum = 0;
                for (int l = 0; l < l2.out_num; l++) {
                    int x = l2.out_row + 2 * l2.w_row - 2;
                    int y = l2.out_col + 2 * l2.w_col - 2;
                    float **o = alloc(x, y);
                    float **w = alloc(l2.w_row, l2.w_col);
                    set_o(l2.o[l], o, l2.out_row, l2.out_col, l2.w_row, l2.w_col);
                    set_w(l2.w[l][i], w, l2.w_row, l2.w_col);
                    sum += juanji(o, w, l2.w_row, l2.w_col, j, k);
                    del(o, x, y);
                    del(w, l2.w_row, l2.w_col);
                }
                l1.o[i][j][k] = sum;
            }
        }
    }
} 
#endif
