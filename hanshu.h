/*************************************************************************
	> File Name: hanshu.h
	> Author: 
	> Mail: 
	> Created Time: 2018年05月13日 星期日 19时46分06秒
 ************************************************************************/

#ifndef _HANSHU_H
#define _HANSHU_H
//class Conlayer;
//class Poollayer;
//class Layer;
#define e 2.71828
#define s(x) (1.0 / (1 + pow(e, -(x))))
#define R 0.1     //过拟合参数
#define M 3      //小规模数据
#define rate 0.05  //学习速率

#pragma once

#include "convolution_lay.h"
#include "lay.h"
#include "pool_lay.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdlib>

float relu(float x) {
    if (x < 0) return 0;
    else return x;
}
float relu_(float x) {
    if (x == 0) return 0;
    else return 1;
}
void read_in(FILE *f, Layer& l) {
    for (int i = 0; i < 100; i++) {
        fscanf (f, "%f", &l.a[i]);
      //  printf ("%f ", l.a[i]);
    }
}  

float juanji(float** out, float**w, int row, int col, int i1, int j1) {
    float sum = 0;
    for (int i = i1; i < i1 + row; i++) {
        for (int j = j1; j < j1 + col; j++) {
            sum += (out[i][j] * w[i - i1][j - j1]);
           // printf ("i = %d ", i - i1);
          //  printf ("i = %d ", i - i1);
         //   printf ("i = %d\n", i);
         //   printf ("j = %d\n", j);
           // printf ("out[%d][%d] = %f", i, j, out[i][j]);
        }
    }
    return sum;
}
float ** alloc(int row, int col) {
    float **p = new float* [row];
    for (int i = 0; i < row; i++) {
        p[i] = new float[col];
        memset(p[i], 0, sizeof(float) * col);
    }
    return p;
}
void mem(float **p, int row, int col) {
    for (int i = 0; i < row; i++) {
        memset(p[i], 0, sizeof(float) * col);
    }    
}
void del (float **p, int row, int col) {
    for (int i = 0; i < row; i++)  {
        delete[] p[i];
    }
    delete p;
}
void set_o(float **original, float **now, int original_row, int original_col, int w_row, int w_col) {
    int now_row = original_row + 2 * w_row - 2;
    int now_col = original_col + 2 * w_col - 2;
    for (int i = 0; i < original_row; i++) {
        for (int j = 0; j < original_col; j++) {
            now[w_row - 1 + i][w_col - 1 + j] = original[i][j];
        }
    }
}
void set_w(float** original, float **now, int w_row, int w_col) {
    //memset(now, 0, sizeof(float) * w_row * w_col);
    for (int i = 0; i < w_row; i++) {
        for (int j = 0; j < w_col; j++) {
            now[i][j] = original[w_row - 1 - i][w_col - 1 - j];
        }
    }
}
void train(Layer& l1, Layer& l2, Layer& l3, float *y_zhan, float *y_wo, float *y_zhi) {
    FILE *wo = fopen("./wo.txt", "r");
    FILE *zhan = fopen("./zhan.txt", "r");
    FILE *zhi = fopen("./zhi.txt", "r");
    for (int i = 0; i < 100; i++) {
        printf ("begin----------------------------\n");
        read_in(zhan, l1);
        l1 >> l2 >> l3;
        count_layer3(l3, l2, y_zhan);
        count_layer2(l2, l3, l1);
        l3.output_a();
    
        read_in(wo, l1);
        l1 >> l2 >> l3;
        count_layer3(l3, l2, y_wo);
        count_layer2(l2, l3, l1);
        l3.output_a();
        
        read_in(zhi, l1);
        l1 >> l2 >> l3;
        count_layer3(l3, l2, y_zhi);
        count_layer2(l2, l3, l1);
        l3.output_a();
        printf ("end----------------------------\n");     
        update(l2);
        update(l3);
    } 
    fclose(zhan);
    fclose(wo);
    fclose(zhi);
}
void train(Layer& l1, Layer& l2, Layer& l3, float *y_zhan, float *y_wo) {
    FILE *wo = fopen("./wo.txt", "r");
    FILE *zhan = fopen("./zhan.txt", "r");
    for (int i = 0; i < 100; i++) {
        printf ("begin----------------------------\n");
        read_in(zhan, l1);
        l1 >> l2 > l3;
        count_layer3(l3, l2, y_zhan);
        count_layer2(l2, l3, l1);
        l3.output_a();
    
        read_in(wo, l1);
        l1 >> l2 > l3;
        count_layer3(l3, l2, y_wo);
        count_layer2(l2, l3, l1);
        l3.output_a();
        
        printf ("end----------------------------\n");     
        update(l2);
        update(l3);
    } 
    fclose(zhan);
    fclose(wo);
}
void train(Layer& l1, Layer& l2, Layer& l3, Layer& l4, float *y_zhan, float *y_wo) {
    FILE *wo = fopen("./wo.txt", "r");
    FILE *zhan = fopen("./zhan.txt", "r");
    for (int i = 0; i < 100; i++) {
        read_in(zhan, l1);
        l1 >> l2 >> l3 >> l4;
        count_layer3(l4, l3, y_zhan);
        count_layer2(l3, l4, l2);
        count_layer2(l2, l3, l1);
        
        read_in(wo, l1);
        l1 >> l2 >> l3 >> l4;
        count_layer3(l4, l3, y_wo);
        count_layer2(l3, l4, l2);
        count_layer2(l2, l3, l1);
    }  
    update(l2);
    update(l3);
    update(l4);
    printf ("test_zhan -----------------------------\n");
    read_in(zhan, l1);
    l1 >> l2 >> l3 >> l4;
    l4.output_a();
    printf ("test_wo -------------------------------\n");
    read_in(wo, l1);
    l1 >> l2 >> l3 >> l4;
    l4.output_a();
    fclose(zhan);
    fclose(wo);
}
void train(Layer& l1, Layer& l2, Layer& l3, Layer& l4, float *y_wo) {
    FILE *wo = fopen("./wo.txt", "r");
    for (int i = 0; i < 100; i++) {
        printf ("begin----------------------------\n");
        read_in(wo, l1);
        l1 >> l2 >> l3 >> l4;
        count_layer3(l4, l3, y_wo);
        count_layer2(l3, l4, l2);
        count_layer2(l2, l3, l1);
        l4.output_a();
        
        printf ("end----------------------------\n");     
        update(l2);
        update(l3);
        update(l4);
    } 
    fclose(wo);
} 
#endif
